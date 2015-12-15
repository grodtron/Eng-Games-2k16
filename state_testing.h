void state_analog_graph(){

  Serial.print(controller.Analog(PSS_RY));
  Serial.print(',');
  Serial.println(micros());
  
}

void state_testing_brushless(){
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

  int speed = controller.Button(PSB_R2) ? 255 : 180;
  //// Spinning
  if(controller.Button(PSB_PAD_UP)){
    motors.setTargetSpeed(speed, speed);
  }else if(controller.Button(PSB_PAD_RIGHT)){
    motors.setTargetSpeed(speed, -speed);
  }else if(controller.Button(PSB_PAD_LEFT)){
    motors.setTargetSpeed(-speed, speed);
  }else if(controller.Button(PSB_PAD_DOWN)){
    motors.setTargetSpeed(-speed, -speed);
  }else{
    motors.setTargetSpeed(0, 0);
  }
  
}

