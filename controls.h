#ifndef CONTROLS_H_
#define CONTROLS_H_

namespace control {

  inline void next_state(state_func next_state){
    if(controller.ButtonPressed(PSB_TRIANGLE)){
      current_state = next_state;
    }
  }
  
  inline void handbrake(){
    if(controller.Button(PSB_L3) && controller.Button(PSB_R3)){
      motors.setSpeedImmediate(0,0);
    }
  }

  // Toggle brushless on and off with R1
  inline void brushless(){
    if(controller.ButtonPressed(PSB_BLUE)){
      if(brushless.isOn()){
        brushless.setThrottle(0);
      }else{
        brushless.setThrottle(150);
      }
    }
  }

  // Toggle on and off flipper
  inline void flipper(){
    static int isOn = false;
    if(isOn){
      flipperMotor->run(RELEASE);
    }else{
      flipperMotor->setSpeed(255);
      flipperMotor->run(FORWARD);
    }
    isOn = ! isOn;
  }

  void rami_stick(){
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


  

}

#endif
