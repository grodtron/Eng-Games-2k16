#include "Point.h"
#include "Controller.h"
Controller controller(13,8,7,12);

#include "Brushless.h"
Brushless brushless(9);

#include "LimitSwitch.h"
LimitSwitch limit(2);

#include <Wire.h>
#include <Adafruit_MotorShield.h>
Adafruit_MotorShield AFMS;
Adafruit_DCMotor *motorLEFT  = AFMS.getMotor(1);
Adafruit_DCMotor *motorRIGHT = AFMS.getMotor(2);

Adafruit_DCMotor *flipperMotor = AFMS.getMotor(4);

#include "Motors.h"
Motors motors;

// Define state_func type and declare global state variable
typedef void (*state_func)(void);
state_func current_state;

#include "state_bumrush.h"
#include "state_start_wait.h"
#include "state_normal.h"
#include "state_testing.h"

#include <math.h>

bool turnOffFlipper = false;
void turnOffFlipperMotor(){
  turnOffFlipper = true;
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");

  brushless.init();

  controller.init();

  limit.setCallback(turnOffFlipperMotor);

  AFMS.begin();
  motorLEFT->run(RELEASE);
  motorRIGHT->run(RELEASE);

  current_state = state_testing;//state_start_wait;

  Serial.println("Done!");

}

void loop() {

  if(turnOffFlipper){
    flipperMotor->setSpeed(0);
    flipperMotor->run(RELEASE);
    turnOffFlipper = false;
  }

  if(controller.read()){
    current_state();
  }
  motors.update();
}
