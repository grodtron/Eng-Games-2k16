// N.B. should be included after global declarations in main cpp file

void state_normal();


void state_bumrush(){
  Serial.println("Rush State");

  const int L_SPEED = 170;
  const int R_SPEED = 255;
  
  static int l_speed = L_SPEED;
  static int r_speed = R_SPEED;

  // Angle slightly more left
  if(controller.Button(PSB_PAD_LEFT)){
      l_speed = 100;
      r_speed = 254;
    }
  // Angle slightly more right
  else if(controller.Button(PSB_PAD_RIGHT)){
      l_speed = 200;
      r_speed = 200;
  }
  // Slow down with back on the D-pad
  else if(controller.Button(PSB_PAD_DOWN)){
    l_speed = constrain(l_speed - 1, 0, 255);
    r_speed = constrain(r_speed - 1, 0, 255);
  }
  // Speed up with forward on the D-pad
  else if(controller.Button(PSB_PAD_UP)){
    l_speed = constrain(l_speed + 1, 0, 255);
    r_speed = constrain(r_speed + 1, 0, 255);
    brushless.setThrottle(150);
  }
  else {
    l_speed = constrain(L_SPEED, 0, 255);
    r_speed = constrain(R_SPEED, 0, 255);
  }

 
    motors.setTargetSpeed(l_speed, r_speed);


  //// Flipper ||||
  if(controller.Button(PSB_R1)){
    flipperMotor->setSpeed(255);
    flipperMotor->run(FORWARD);
  }
  if(controller.Button(PSB_L1)){
    flipperMotor->run(RELEASE);
  }
  if(controller.Button(PSB_L2)){
    brushless.setThrottle(150);
  }
  else{
    brushless.setThrottle(0);
  }

  // Exit this state if any of the normal buttons are pressed
  if(controller.Button(PSB_PINK)){
    current_state = state_normal; // TODO - go back into the waiting state for testing
  }

}

