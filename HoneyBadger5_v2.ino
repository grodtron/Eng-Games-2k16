#include "Point.h"
#include "Controller.h"
Controller controller(13,8,7,12);

#include <Wire.h>
#include <Adafruit_MotorShield.h>
Adafruit_MotorShield AFMS;
Adafruit_DCMotor *leftMotor  = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

// Define state_func type and declare global state variable
typedef void (*state_func)(void);
state_func current_state;

#include "state_bumrush.h"
#include "state_start_wait.h"
#include "state_normal.h"

#include <math.h>

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");

  controller.init();

  AFMS.begin();
  leftMotor->run(RELEASE);
  rightMotor->run(RELEASE);

  current_state = state_start_wait;

  Serial.println("Done!");

}

void loop() {

  if(controller.read()){
    current_state();
  }
}
