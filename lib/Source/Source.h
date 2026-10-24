#include "RobotConfig.h"
#include <FastAccelStepper.h>
#include <TMC2209.h>

class Robot {
    public:
    //USER INPUT INSTRUCTIONS
    void instructions();

    //MOVEMENT

    //Moves the robot by the given distance in mm
    void move(double dist);

    //Rotates the robot around its center by a given angle
    //
    //positive angle is clockwise,
    //negative angle is counterclockwise
    void rotate(double degrees);

    //Turns the robot in a circular motion clockwse and forwards
    //(counterclockwise and backwards if angle is -) around an 
    //imaginary point a given distance away by a given angle.
    //
    //The radius defaults to 250mm, but can be specified to change it
    void turnCW(double degrees, double radius = 250); 

    //Turns the robot in a circular motion counterclockwse and forwards
    //(clockwise and backwards if angle is -) around an imaginary point  
    //a given distance away by a given angle.
    //
    //The radius defaults to 250mm, but can be specified to change it
    void turnCCW(double degrees, double radius = 250);
    
    //OTHER PUBLIC FUNCTIONS

    //Initializes the motors
    void init();

    //calculates desired speed so it finishes in the desired amount of time
    void preCalc(int targetTime, float accelTime);

    //runs the robot
    void run();

    //This is a list of useful stuff
    //
    //FUNCTIONS:
    //- move(dist);
    //- rotate(angle);
    //- turnCW(angle, optional radius);
    //- turnCCW(angle, optional radius);
    //
    //CONSTANTS:
    //- dowelOffset: distance from robots center of movement to pencil point
    //
    //OTHER USEFUL INFO
    //- The robot's center is the midpoint between the wheels centers  
    //- 1 grid square is 500mm
    void help(){};

    //Test runs for practice purposes

    //SW2024-2025
    void practice1(){
        turnCW(90);
        turnCCW(90);
        move(1000);
        turnCCW(90);
        move(500); 
        turnCCW(90);
        turnCW(180);
        turnCCW(180);
        move(1000);
        turnCCW(180);
        turnCW(180);
        turnCCW(90);
        turnCW(90);
        rotate(180);
    }

    //Modified States2025
    void practice2(){
        move(500+dowelOffset);
        turnCW(90);
        move(750);
        move(-1250);
        turnCW(-90);
        turnCCW(-90);
        move(-250);
        move(250);
        turnCCW(180);
        turnCW(180);
        move(1000);
        turnCCW(270);
        turnCW(180);
        turnCCW(90);
        move(250-dowelOffset);
    }

    //SW2025-2026
    void practice3(){
        turnCW(90);
        turnCCW(90);
        move(500 + dowelOffset);
        turnCW(180);
        move(500);
        turnCCW(180);
        move(750);
        move(-500);
        rotate(-90);
        move(250);
        turnCW(90);
        move(500);
        turnCW(90);
        move(250);
        move(-500);
        rotate(180);
        move(750);
        turnCW(180);
        move(250);
        rotate(-90);
        move(-1250 - dowelOffset);
    }

    private:
    //TIME CALCULATION STUFF
    float maxSpeed = 0;
    float accel = 0;
    long maxDist = 0;

    //MOVE SCHEDULING STUFF
    long instructionsL[maxMoves];
    long instructionsR[maxMoves];
    int moveCounter = 0;

    //INTERNALLY USED FUNCTIONS
    void addMove(double mmL, double mmR);
};

int32_t distToSteps(double dist);