#ifndef CONTROLS_H_
#define CONTROLS_H_

namespace control {

  inline void next_state(state_func next_state){
    static boolean wasPressed = false;

    if(wasPressed){
      if( ! global::controller.Button(PSB_TRIANGLE)){
        wasPressed = false;
      }      
    }else{
      if(global::controller.Button(PSB_TRIANGLE)){
        current_state = next_state;
        wasPressed  = true;
        Debug.println("Switching state!");
      }      
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

  int16_t constrainSpeed(int16_t v, int16_t bakMax, int16_t fwdMax){
    v = constrain(v, -255, 255);
    if(v < 0){
      return map(v, -255,      0,   bakMax, 0);
    }else{
      return map(v, 0, 255,    0,      fwdMax);
    }
  }

  void rami_stick(){
    if(global::controller.Button(PSB_L1)){
      global::motors.setTargetSpeed(-200, 200);
    }else if(global::controller.Button(PSB_R1)){
      global::motors.setTargetSpeed(200, -200);    
    }else{
      const int PLUS_DIVIDER  = 1;
      const int MINUS_DIVIDER = 2;
  
      int speed = 2 * global::controller.right.y;  // Up   is Positive
      int ratio = global::controller.left.x;       // Left is Positive (I think)
      
      bool dirIsLeft = ratio > 0;
      ratio = abs(ratio);
    
      int16_t left  = speed;
      int16_t right = speed;
    
      Debug.println(speed);
    
      if(dirIsLeft){
        left  += ratio / PLUS_DIVIDER;
        right -= ratio / MINUS_DIVIDER;
      }else{
        right += ratio / PLUS_DIVIDER;
        left  -= ratio / MINUS_DIVIDER;    
      }
    
      left  = constrainSpeed(left,  -200, 255);
      right = constrainSpeed(right, -200, 255);
    
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
