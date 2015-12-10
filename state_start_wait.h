void state_bumrush();

void state_start_wait(){
  // Exit this state if any of the normal buttons are pressed

  Serial.println("Waiting");
  
  if(controller.Button(PSB_BLUE)){
    current_state = state_bumrush;
  }
}

