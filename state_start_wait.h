void state_bumrush();

void state_start_wait(){
  Serial.println("Waiting state");
  
  if(controller.ButtonPressed(PSB_R3)){
    current_state = state_bumrush;
  }
}

