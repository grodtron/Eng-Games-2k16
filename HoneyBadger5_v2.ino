#include <PS2X_lib.h>
#include "Point.h"
PS2X controller;

int controller_error;

void init_controller(){
  do{
    controller_error = controller.config_gamepad(13,8,7,12,
      true/*analog*/,
      false/*rumble*/);
  
    if(controller_error){
      Serial.print("Controller Error: ");
      Serial.println(controller_error);
    }
  }while(controller_error);
  Serial.println("Controller connected");
}

void read_controller(){
  static int error_count = 0;
  if(controller.read_gamepad()){
    ++error_count;
  }else{
    error_count = 0;
  }

  if(error_count > 10){
    error_count = 0;
    init_controller();
  }

}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");

  init_controller();

  Serial.println("Done!");
  Serial.parseInt();
}

void loop() {

  read_controller();
  
  Point left(
    controller.Analog(PSS_LX),
    controller.Analog(PSS_LY));
  
  Point right(
    controller.Analog(PSS_RX),
    controller.Analog(PSS_RY));

  //right.print_self("right");
  left.print_self("left");
  
  // put your main code here, to run repeatedly:

}
