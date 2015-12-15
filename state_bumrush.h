// N.B. should be included after global declarations in main cpp file

void state_normal();

void state_bumrush(){

  const int L_SPEED = 250;
  const int R_SPEED = 255;
  
  static int l_speed = L_SPEED;
  static int r_speed = R_SPEED;

  // Angle slightly more left
  if(controller.Button(PSB_PAD_LEFT)){
    if(r_speed == 255){
      l_speed = constrain(l_speed - 1, 0, 255);
    }else{
      r_speed = constrain(r_speed + 1, 0, 255);
    }
  }
  
  // Angle slightly more right
  if(controller.Button(PSB_PAD_RIGHT)){
    if(l_speed == 255){
      r_speed = constrain(r_speed - 1, 0, 255);
    }else{
      l_speed = constrain(l_speed + 1, 0, 255);
    }
  }

  // Slow down with back on the D-pad
  if(controller.Button(PSB_PAD_DOWN)){
    l_speed = constrain(l_speed - 1, 0, 255);
    r_speed = constrain(r_speed - 1, 0, 255);
  }

  // Speed up with forward on the D-pad
  if(controller.Button(PSB_PAD_UP)){
    l_speed = constrain(l_speed + 1, 0, 255);
    r_speed = constrain(r_speed + 1, 0, 255);
  }

  motorLEFT->setSpeed(l_speed);
  motorRIGHT->setSpeed(r_speed);

  motorLEFT->run(FORWARD);
  motorRIGHT->run(FORWARD);

  // Exit this state if any of the normal buttons are pressed
  if(controller.Button(PSB_RED)){
    current_state = state_normal; // TODO - go back into the waiting state for testing
  }
}

