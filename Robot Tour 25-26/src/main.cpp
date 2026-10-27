#include <Arduino.h>
#include <Source/Source.h>

Robot robot;

#define targetTime 60 //could be from 55-75 seconds
#define accelTime 0.333f 

void Robot::instructions(){
	//! max length 50 moves
	help(); //hover over me for help

	move(dowelOffset);
	turnCW(90);
	move(1250);
	move(-750);
	rotate(180);
	turnCW(90);
	turnCCW(90);
	move(250);
	rotate(-90);
	move(-500);
	rotate(-90);
	move(1000);
	rotate(-90);
	move(-250);
	rotate(180);
	turnCCW(180);
	move(1250);
	move(-500);
	rotate(-90);
	move(1250);
	turnCW(90);
	move(250);
	move(-250);
	rotate(-180);
	turnCCW(90);
	move(500);
	turnCCW(90);
	move(250-dowelOffset);
};

void setup() {
	//*setup the robot
	robot.init();
	robot.preCalc(targetTime, accelTime);

	//*wait for button press
	while(digitalRead(triggerPin) == HIGH){}
	while(digitalRead(triggerPin) == LOW){}

	//*start execution
	robot.run();
}

void loop() {}