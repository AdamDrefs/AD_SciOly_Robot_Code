//precision values
//calibrated
#define dowelOffset 32.8f
#define wheelCircumference 190.4016f  //ideal 189.517, inversely proportional to distance traveled

//uncalibrated
#define wheelSeparationTurn 147.900f
#define wheelSeparationRotate 147.8194066561166f

//speed multipliers
#define turnSpeedMult 1.2f
#define rotateSpeedMult 0.75f

//hardware values
#define triggerPin 27   //TH0 port
#define RX_Pin 9U
#define TX_Pin 8U
#define microsteps 128
#define spr microsteps*200  //steps per revolution

//X port
#define dirPinL 10
#define stepPinL 11
#define enablePinL 12

//Y port
#define dirPinR 5
#define stepPinR 6
#define enablePinR 7

//power settings
#define motorHoldCurrent 15     //measured as a %
#define motorRunCurrent 80
#define motorPWMOffset 196
#define motorPWMGradient 64
#define brakingMode TMC2209::STRONG_BRAKING

#define maxMoves 100 