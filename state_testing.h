
void state_testing_brushless(){
  if(controller.Button(PSB_BLUE)){
    brushless.setThrottle(75); // out of 255
  }
  if(controller.Button(PSB_RED)){
    brushless.setThrottle(0);
  }
  if(controller.Button(PSB_R1)){
    flipperMotor->setSpeed(255);
    flipperMotor->run(FORWARD);
  }
  if(controller.Button(PSB_L1)){
    flipperMotor->run(RELEASE);
  }
}

