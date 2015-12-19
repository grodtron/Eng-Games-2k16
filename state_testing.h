#include "controls.h"

void state_analog_graph(){
  Serial.print(controller.Analog(PSS_RY));
  Serial.print(',');
  Serial.println(micros());
}



void peripheral_control(){
  //// Brushless ||||
  if(controller.Button(PSB_BLUE)){
    brushless.setThrottle(80); // out of 255
  }
  if(controller.Button(PSB_RED)){
    brushless.setThrottle(0);
  }

  //// Flipper ||||
  if(controller.Button(PSB_R1)){
    flipperMotor->setSpeed(255);
    flipperMotor->run(FORWARD);
  }
  if(controller.Button(PSB_L1)){
    flipperMotor->run(RELEASE);
  }
}

void state_testing(){
  rami_stick_control();
  //dpad_basic_control();
  peripheral_control();
}
