#include <Arduino.h>
#include <Source/Source.h>

Robot robot;

#define targetTime 60 //could be from 55-75 seconds
#define accelTime 0.333f 

void Robot::instructions(){
	//! max length 50 moves
	help(); //hover over me for help

	practice2();
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