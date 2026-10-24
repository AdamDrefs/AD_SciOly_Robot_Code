//precision values
//calibrated
#define microsteps 128
#define spr microsteps*200  //steps per revolution
#define dowelOffset 32.8f
#define wheelCircumference 190.4016f  //ideal 189.517, inversely proportional to distance traveled

//uncalibrated
#define wheelSeparationTurn 147.900f
#define wheelSeparationRotate 147.8194066561166f

//hardware values
#define triggerPin 27   //TH0 port
#define RX_Pin 9U
#define TX_Pin 8U

//X port
#define dirPinL 10
#define stepPinL 11
#define enablePinL 12

//Y port
#define dirPinR 5
#define stepPinR 6
#define enablePinR 7

//power settings
#define motorHoldCurrent 33     //measured as a %
#define motorRunCurrent 50
#define motorPWMOffset 223
#define motorPWMGradient 16
#define brakingMode TMC2209::STRONG_BRAKING

#define maxMoves 100 