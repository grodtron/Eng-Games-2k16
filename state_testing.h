#include "controls.h"

void state_analog_graph(){
  Debug.print(global::controller.Analog(PSS_RY));
  Debug.print(',');
  Debug.println(micros());
}


void state_testing(){
  //control::rami_stick();
  //control::handbrake();
  control::dpad_basic();
  control::brushless();
  control::flipper();
}
