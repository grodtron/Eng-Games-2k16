#ifndef CONTROLS_H_
#define CONTROLS_H_

namespace control {

  inline void next_state(state_func next_state){
    if(global::controller.ButtonPressed(PSB_TRIANGLE)){ // TODO
      current_state = next_state;
    }
  }
  
  inline void handbrake(){
    if(global::controller.Button(PSB_L3) && global::controller.Button(PSB_R3)){
      global::motors.setSpeedImmediate(0,0);
    }
  }

  // Toggle brushless on and off with R1
  inline void brushless(){
    if(global::controller.Button(PSB_CROSS)){
        global::brushless.setThrottle(150);
    }else{
        global::brushless.setThrottle(0);      
    }
  }

  // Toggle on and off flipper
  inline void flipper(){
    if(global::controller.Button(PSB_CIRCLE)){
      Debug.println("Flipper on");
      FLIPPER_ON();
    }
    if(global::controller.Button(PSB_SQUARE)){
      Debug.println("Flipper off");
      FLIPPER_OFF();
    }
    
  }

  void rami_stick(){
    if(global::controller.Button(PSB_L2)){
      global::motors.setTargetSpeed(-255, 255);
    }else if(global::controller.Button(PSB_R2)){
      global::motors.setTargetSpeed(255, -255);    
    }else{
      const int PLUS_DIVIDER  = 2;
      const int MINUS_DIVIDER = 4;
  
      static int last_speed = 0;
      int speed = 2 * (127 - global::controller.Analog(PSS_RY)); // Up   is Positive
      int ratio = global::controller.Analog(PSS_LX) - 127; // Left is Positive (I think)
      bool dirIsLeft = ratio > 0;
      ratio = abs(ratio);
    
      int left  = speed;
      int right = speed;
    
      Debug.println(speed);
    
      if(dirIsLeft){
        left  += ratio / PLUS_DIVIDER;
        right -= ratio / MINUS_DIVIDER;
      }else{
        right += ratio / PLUS_DIVIDER;
        left  -= ratio / MINUS_DIVIDER;    
      }
    
      left  = constrain(left,  -255, 255);
      right = constrain(right, -255, 255);
    
      global::motors.setTargetSpeed(left, right);
    }
  }


  void dpad_basic(){
    int speed = global::controller.Button(PSB_R2) ? 255 : 180;
    //// Spinning
    if(global::controller.Button(PSB_PAD_UP)){
      global::motors.setTargetSpeed(speed, speed);
    }else if(global::controller.Button(PSB_PAD_RIGHT)){
      global::motors.setTargetSpeed(speed, -speed);
    }else if(global::controller.Button(PSB_PAD_LEFT)){
      global::motors.setTargetSpeed(-speed, speed);
    }else if(global::controller.Button(PSB_PAD_DOWN)){
      global::motors.setTargetSpeed(-speed, -speed);
    }else{
      global::motors.setTargetSpeed(0, 0);
    }
  }


  

}

#endif
