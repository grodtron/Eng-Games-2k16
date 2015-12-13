
void state_testing_brushless(){
  if(controller.Button(PSB_BLUE)){
    brushless.setThrottle(50); // out of 255
  }
  if(controller.Button(PSB_RED)){
    brushless.setThrottle(0);
  }
}

