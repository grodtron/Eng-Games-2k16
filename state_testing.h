#include "controls.h"

void state_analog_graph(){
  Serial.print(global::controller.Analog(PSS_RY));
  Serial.print(',');
  Serial.println(micros());
}


void state_testing(){
  //control::rami_stick();
  //control::handbrake();
  control::dpad_basic();
  control::brushless();
  control::flipper();
}
