void state_analog_graph(){
  Serial.print(controller.Analog(PSS_RY));
  Serial.print(',');
  Serial.println(micros());
}

void rami_stick_control(){

  if(controller.Button(PSB_L2)){
    motors.setTargetSpeed(-255, 255);
  }else if(controller.Button(PSB_R2)){
    motors.setTargetSpeed(255, -255);    
  }else{
    const int PLUS_DIVIDER  = 2;
    const int MINUS_DIVIDER = 4;

    static int last_speed = 0
    int speed = 2 * (127 - controller.Analog(PSS_RY)); // Up   is Positive
    int ratio = controller.Analog(PSS_LX) - 127; // Left is Positive (I think)
    bool dirIsLeft = ratio > 0;
    ratio = abs(ratio);
  
    int left  = speed;
    int right = speed;
  
    Serial.println(speed);
  
    if(dirIsLeft){
      left  += ratio / PLUS_DIVIDER;
      right -= ratio / MINUS_DIVIDER;
    }else{
      right += ratio / PLUS_DIVIDER;
      left  -= ratio / MINUS_DIVIDER;    
    }
  
    left  = constrain(left,  -255, 255);
    right = constrain(right, -255, 255);
  
    motors.setTargetSpeed(left, right);
  }
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

void dpad_basic_control(){
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


void state_testing(){
  rami_stick_control();
  peripheral_control();
}
