#include <Source/Source.h>

const long SERIAL_BAUD_RATE = 115200;
HardwareSerial & serial_stream = Serial2;

TMC2209 stepper_driverX;
TMC2209 stepper_driverY;

FastAccelStepperEngine engine = FastAccelStepperEngine();
FastAccelStepper *stepperL = NULL;
FastAccelStepper *stepperR = NULL;

void Robot::init() {
	Serial.begin(SERIAL_BAUD_RATE);
	
	//basic setup of drivers
	stepper_driverX.setup(Serial2, SERIAL_BAUD_RATE, TMC2209::SERIAL_ADDRESS_0);
	stepper_driverY.setup(Serial2, SERIAL_BAUD_RATE, TMC2209::SERIAL_ADDRESS_2);
	
  	stepper_driverX.setMicrostepsPerStep(microsteps);
	stepper_driverX.setReplyDelay(4);

	stepper_driverY.setMicrostepsPerStep(microsteps);
	stepper_driverY.setReplyDelay(4);
	
	//configure current settings
	stepper_driverX.setPwmOffset(motorPWMOffset);
	stepper_driverX.setPwmGradient(motorPWMGradient);
	stepper_driverX.setRunCurrent(motorRunCurrent);
	stepper_driverX.setHoldCurrent(motorHoldCurrent);
	stepper_driverX.setStandstillMode(brakingMode);
	stepper_driverX.enableCoolStep();
	stepper_driverX.enable();

	stepper_driverY.setPwmOffset(motorPWMOffset);
	stepper_driverY.setPwmGradient(motorPWMGradient);
	stepper_driverY.setRunCurrent(motorRunCurrent);
	stepper_driverY.setHoldCurrent(motorHoldCurrent);
	stepper_driverY.setStandstillMode(brakingMode);
	stepper_driverY.enableCoolStep();
	stepper_driverY.enable();

	//configure FastAccelStepper library
	engine.init();
	stepperL = engine.stepperConnectToPin(stepPinL);
	stepperR = engine.stepperConnectToPin(stepPinR);
	stepperL->setDirectionPin(dirPinL);
	stepperR->setDirectionPin(dirPinR);
	pinMode(enablePinL, OUTPUT);
	pinMode(enablePinR, OUTPUT);

	//backup speed and accel values
	stepperL->setAcceleration(10 * spr);
	stepperL->setSpeedInHz(2 * spr);
	stepperR->setAcceleration(10 * spr);
	stepperR->setSpeedInHz(2 * spr);
	stepperR->setLinearAcceleration(0);
	stepperL->setLinearAcceleration(0);

	//robot config stuff
	pinMode(triggerPin, INPUT_PULLDOWN);
	moveCounter = 0;
};

//MOVEMENT
void Robot::move(double dist){
	//no math needed beyond what's in addMove()
	addMove(dist, dist);
}

void Robot::rotate(double degrees){
	//πd * Θ/360
	double mm = (PI * wheelSeparationRotate * degrees)/(360 * rotateSpeedMult);
	addMove(mm, -mm);
}

void Robot::turnCW(double degrees, double radius){
	//2π * (radius ± wheel separation) * Θ/360
	double mmL = (2 * PI * (radius + wheelSeparationTurn/2) * degrees)/(360 * turnSpeedMult);
	double mmR = (2 * PI * (radius - wheelSeparationTurn/2) * degrees)/(360 * turnSpeedMult);
	addMove(mmL, mmR);
}

void Robot::turnCCW(double degrees, double radius){
	//2π * (radius ± wheel separation) * Θ/360
	//mirror of turnCW
	double mmR = (2 * PI * (radius + wheelSeparationTurn/2) * degrees)/(360 * turnSpeedMult);
	double mmL = (2 * PI * (radius - wheelSeparationTurn/2) * degrees)/(360 * turnSpeedMult);
	addMove(mmL, mmR);
}

//CALCULATIONS
void Robot::addMove(double mmL, double mmR){
	long stepsL = distToSteps(mmL);  //could be in movement code but saves code to put it here
	long stepsR = distToSteps(mmR);

	//schedule the move
	instructionsL[moveCounter] = stepsL;
	instructionsR[moveCounter] = stepsR;
	moveCounter++;
	
	//add to max distance for time calculation
	maxDist += max(abs(stepsL), abs(stepsR));
}

void Robot::preCalc(int targetTime, float accelTime){
	//run the instructions
	instructions();

	//s = d/(t-an)
	//s = speed, t = target time, a = accel time, n - move count
	maxSpeed = maxDist/(targetTime - (accelTime * moveCounter));
	accel = maxSpeed/accelTime;
}

int32_t distToSteps(double dist){
	return (long)((float)(dist * spr) / wheelCircumference);
};

//EXECUTION
void Robot::run(){
	for(int i = 0; i < moveCounter; i++){
		long stepsL = instructionsL[i];
		long stepsR = instructionsR[i];

		float ratio = (float)abs(stepsL) / (float)abs(stepsR);
		float mult = 1;
		
		if(ratio != 1){
			mult = turnSpeedMult;
		}else if(stepsL == -stepsR){
			mult = rotateSpeedMult;
		}

		stepperL->setSpeedInHz(mult * constrain(maxSpeed * ratio, -maxSpeed, maxSpeed));
		stepperR->setSpeedInHz(mult * constrain(maxSpeed / ratio, -maxSpeed, maxSpeed));

		stepperL->setAcceleration(mult * constrain(accel * ratio, 0, accel));
		stepperR->setAcceleration(mult * constrain(accel / ratio, 0, accel));

		stepsL*=-1;//L inverted in hardware
		stepperL->move(mult * stepsL);
		stepperR->move(mult * stepsR);
		while(stepperL->isRunning() || stepperR->isRunning()){}
	}
}