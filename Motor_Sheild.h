/*
 * Auther: Ryan Cooke
 * Subject: Concordia Eng Games Machine Motor header
 * save date:12/05/2015
 * I2C Motor shield 
 */
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

class Motor {
private:

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor_0 = AFMS.getMotor(1);// 
Adafruit_DCMotor *myMotor_1 = AFMS.getMotor(2);// 
Adafruit_DCMotor *myMotor_2 = AFMS.getMotor(3);// 

const int PT=0;
const int SB=1;

void MOVE_WHEEL_FWD(bool SIDE, int  AMOUNT) { 
  if(SIDE==0) 
  { 
    myMotor_0->run(FORWARD); 
    myMotor_0->setSpeed(AMOUNT);  
  } 
  if(SIDE==1)
  { 
    myMotor_1->run(FORWARD); 
    myMotor_1->setSpeed(AMOUNT); 
  } 
} 

void MOVE_WHEEL_BAK(bool SIDE,int AMOUNT){ 
  if(SIDE==0) 
  { 
    myMotor_0->run(BACKWARD); 
    myMotor_0->setSpeed(AMOUNT); 
  } 
  if(SIDE==1) 
  { 
    myMotor_1->run(BACKWARD); 
    myMotor_1->setSpeed(AMOUNT); 
  } 
} 





public:

const int N_MOTORS = 2;

const int PORT_PWM  = 5;
const int STARBOARD_PWM = 6;


const int PORT_DIR  = 3;// PWM PIN BUT NOT NEEDED TO BE
const int STARBOARD_DIR = 4;

void setup(){
  Serial.println("BAD SETUP MOTOR");
  AFMS.begin();  // create with the default frequency 1.6KHz
   // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor_0->setSpeed(150);
  myMotor_0->run(FORWARD);
  // turn on motor
  myMotor_0->run(RELEASE);
  
  myMotor_1->setSpeed(150);
  myMotor_1->run(FORWARD);
  // turn on motor
  myMotor_1->run(RELEASE);

  
  myMotor_2->setSpeed(255);
  myMotor_2->run(FORWARD);
  // turn on motor
  myMotor_2->run(RELEASE);
}

void flipper_on()
{
  myMotor_2->run(FORWARD);  
}

void flipper_off()
{
  myMotor_2->run(RELEASE);  
}

void set_PWM(int zero, int one)// 0 is left and 1 is right wheel
{
  myMotor_0->setSpeed(zero);
  myMotor_1->setSpeed(one);
}


void SPIN_LEFT(int AMOUNT) {  
  MOVE_WHEEL_BAK(PT, AMOUNT); 
  MOVE_WHEEL_FWD(SB, AMOUNT);  
} 


void SPIN_RIGHT(int AMOUNT)  {  
  MOVE_WHEEL_FWD(PT, AMOUNT); 
  MOVE_WHEEL_BAK(SB, AMOUNT); 
} 

void FWD(int AMOUNT) {  
  MOVE_WHEEL_FWD(PT, AMOUNT); 
  MOVE_WHEEL_FWD(SB, AMOUNT); 
} 

void BAK(int AMOUNT) {  
  MOVE_WHEEL_BAK(PT, AMOUNT); 
  MOVE_WHEEL_BAK(SB, AMOUNT);  
} 

void TURN_LEFT(int AMOUNT) {  
  MOVE_WHEEL_FWD(PT, 0); 
  MOVE_WHEEL_FWD(SB, AMOUNT);  
} 

void TURN_RIGHT(int AMOUNT) {  
  MOVE_WHEEL_FWD(PT, AMOUNT); 
  MOVE_WHEEL_FWD(SB, 0); 
} 

void  STOP() {
  MOVE_WHEEL_FWD(PT, 0); 
  MOVE_WHEEL_FWD(SB, 0);
  
  myMotor_0->run(RELEASE);
  myMotor_1->run(RELEASE);
  
}


};

