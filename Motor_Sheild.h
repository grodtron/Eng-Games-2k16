/*
 * Auther: Ryan Cooke
 * Subject: Concordia Eng Games Machine Motor header
 * save date:12/04/2015
 * I2C Motor shield 
 */
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor_P = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor_S = AFMS.getMotor(2);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);


const int N_MOTORS = 2;

const int PORT_PWM  = 5;
const int STARBOARD_PWM = 6;


const int PORT_DIR  = 3;// PWM PIN BUT NOT NEEDED TO BE
const int STARBOARD_DIR = 4;

#define MOVE_WHEEL_FWD(SIDE, AMOUNT) do { \
  if(SIDE=="PORT")\
  {\
    myMotor_P->run(FORWARD);\
    myMotor_P->setSpeed(AMOUNT);\  
  }\
  if(SIDE=="STARBOARD")\
  {\
    myMotor_S->run(FORWARD);\
    myMotor_S->setSpeed(AMOUNT);\ 
  }\
} while(0)

#define MOVE_WHEEL_BAK(SIDE, AMOUNT) do { \
  if(SIDE==PORT)\
  {\
    myMotor_P->run(BACKWARD);\
    myMotor_P->run(BACKWARD);\
  }\
  if(SIDE==STARBOARD)\
  {\
    myMotor_S->run(BACKWARD);\
    myMotor_S->setSpeed(AMOUNT); \
  }\
} while(0)


#define SPIN_PS(AMOUNT) do {  \
  MOVE_WHEEL_BAK("PORT", AMOUNT); \
  MOVE_WHEEL_FWD("STARBOARD", AMOUNT);  \
} while(0)


#define SPIN_SB(AMOUNT) do {  \
  MOVE_WHEEL_FWD("PORT", AMOUNT); \
  MOVE_WHEEL_BAK("STARBOARD", AMOUNT);  \
} while(0)

#define FWD(AMOUNT) do {  \
  MOVE_WHEEL_FWD("PORT", AMOUNT); \
  MOVE_WHEEL_FWD("STARBOARD", AMOUNT);  \
} while(0)

#define BAK(AMOUNT) do {  \
  MOVE_WHEEL_BAK("PORT", AMOUNT); \
  MOVE_WHEEL_BAK("STARBOARD", AMOUNT);  \
} while(0)

#define TURN_PS(AMOUNT) do {  \
  MOVE_WHEEL_FWD("PORT", 0); \
  MOVE_WHEEL_FWD("STARBOARD", AMOUNT);  \
} while(0

#define TURN_SB(AMOUNT) do {  \
  MOVE_WHEEL_FWD("PORT", AMOUNT); \
  MOVE_WHEEL_FWD("STARBOARD", 0); \
} while(0)


