#include "controls.h"

void state_analog_graph(){
  Debug.print(micros());
  Debug.print(',');
  Debug.print(global::controller.Analog(PSS_LX));
  Debug.print(',');
  Debug.print(global::controller.Analog(PSS_LY));
  Debug.print(',');
  Debug.print(global::controller.Analog(PSS_RX));
  Debug.print(',');
  Debug.print(global::controller.Analog(PSS_RY));
  Debug.print(',');

  Debug.print(global::controller.left.x);
  Debug.print(',');
  Debug.print(global::controller.left.y);
  Debug.print(',');
  Debug.print(global::controller.right.x);
  Debug.print(',');
  Debug.print(global::controller.right.y);
  Debug.print('\n');

}


void state_testing(){
  control::rami_stick();
  control::handbrake();
  //control::dpad_basic();
  control::brushless();
  control::flipper();
}
