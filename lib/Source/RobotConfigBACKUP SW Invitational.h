//precision values
#define microsteps 64
#define spr microsteps*200  //steps per revolution
#define dowelOffset 32.5f
#define wheelSeparationTurn 147.240f
#define wheelSeparationRotate 146.147f
#define wheelCircumference 189.71f  //ideal 189.517, slightly larger than expected due to wheels being angled
#define curveCompensation 1.00f  //multiplier for left wheel to compensate for curving during movements

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
#define motorRunCurrent 60
#define motorPWMOffset 128
#define motorPWMGradient 32
#define brakingMode TMC2209::STRONG_BRAKING

#define maxMoves 50 