#include "Controller.h"
#include "Brushless.h"
#include "LimitSwitch.h"
#include "Motors.h"

namespace global {
  Controller controller(13,8,7,12);
  Brushless brushless(9);
  LimitSwitch limit(2);
  Motors motors;
}

// Define state_func type and declare global state variable
typedef void (*state_func)(void);
state_func current_state;

//#include "state_bumrush.h"
//#include "state_start_wait.h"
//#include "state_normal.h"
#include "state_testing.h"

#include <math.h>

void turnOffFlipperMotor(){
  FLIPPER_OFF();
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");

  global::brushless.init();

  global::limit.setCallback(turnOffFlipperMotor);

  global::motors.setSpeedImmediate(0,0);

  global::controller.init();

  FLIPPER_OFF();

  current_state = state_testing;

  
  Serial.println("Done!");

}

void loop() {
  if(global::controller.read()){
    current_state();
  }
  global::motors.update();
}
