#ifndef CONTROLS_H_
#define CONTROLS_H_

namespace control {

  /**
   * Switches to the given state if Triangle was pressed
   */
  inline void next_state(state_func next_state){
    // We want to only switch if triangle was released and then
    // pressed, so we keep this static boolean to keep track of
    // that.
    static boolean wasPressed = false;

    // If it was pressed before
    if(wasPressed){
      // And now it's not pressed
      if( ! global::controller.Button(PSB_TRIANGLE)){
        // Then we just update our boolean
        wasPressed = false;
      }
    // Otherwise it was not pressed before
    }else{
      // But it's pressed now
      if(global::controller.Button(PSB_TRIANGLE)){
        // So we update to the requested new state
        current_state = next_state;
        // And again keep our flag up to date
        wasPressed  = true;
        Debug.println("Switching state!");
      }      
    }    
  }
  
  // Toggle brushless on and off with X
  inline void brushless(){
    static boolean wasPressed = false;
    static boolean isOn       = false;

    // If it was pressed before
    if(wasPressed){
      // And now it's not pressed
      if( ! global::controller.Button(PSB_CROSS)){
        // Then we just update our boolean
        wasPressed = false;
      }
    // Otherwise it was not pressed before
    }else{
      // But it's pressed now
      if(global::controller.Button(PSB_CROSS)){
        // So we toggle it on or off
        if(isOn){
          global::brushless.setThrottle(0);
        }else{
          global::brushless.setThrottle(150);
        }
        isOn = ! isOn;
        // And again keep our flag up to date
        wasPressed  = true;
      }
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

  /**
   * Take a speed value, constrain it to the range [-255,255], and then
   * map the positive side of the range to [0, fwdMax] and the negative
   * side of the range to [bakMax, 0]. This allows us to independantly
   * set the speed scales for forward and reverse.
   */
  int16_t constrainSpeed(int16_t v, int16_t bakMax, int16_t fwdMax){
    v = constrain(v, -255, 255);
    if(v < 0){
      return map(v, -255,0,   bakMax,0);
    }else{
      return map(v,  0,255,   0,fwdMax);
    }
  }

  /**
   * Rami's double joystick based control idea.
   */
  void rami_stick(){
    // Do spin in places for L1 and R1
    if(global::controller.Button(PSB_L1)){
      global::motors.setTargetSpeed(-200, 200);
    }else if(global::controller.Button(PSB_R1)){
      global::motors.setTargetSpeed(200, -200);    
    }else{

      // Otherwise R stick Y axis controls throttle, and L stick X axis controls steering

      // Controller axis ranges from [-127,127], so we multiply by 2 to get [-255,255]
      int speed = 2 * global::controller.right.y;
      int16_t left  = speed;
      int16_t right = speed;
      Debug.println(speed);
      
      int ratio = global::controller.left.x;
      
      bool dirIsLeft = ratio > 0;
      ratio = abs(ratio);

      // We add and subtract from the speed on both sides based on the direction and value of
      // the stick. The side we're steering away from we increase, multiplying the value of
      // `ratio` by (PLUS_MULTIPLIER/PLUS_DIVIDER), the the side we are steering towards, we
      // slow down by `ratio` times (MINUS_MULTIPLIER/MINUS_DIVIDER).
   
      const int PLUS_MULTIPLIER = 2;
      //    multiplier    =     -----
      const int PLUS_DIVIDER    = 1;
      
      const int MINUS_MULTIPLIER = 1;
      //    multiplier    =      -----
      const int MINUS_DIVIDER    = 2;
      
      // Depending on the direction we're steering, offset the speeds of the two wheels
      if(dirIsLeft){
        left  += (PLUS_MULTIPLIER  * ratio) / PLUS_DIVIDER;
        right -= (MINUS_MULTIPLIER * ratio) / MINUS_DIVIDER;
      }else{
        right += (PLUS_MULTIPLIER  * ratio) / PLUS_DIVIDER;
        left  -= (MINUS_MULTIPLIER * ratio) / MINUS_DIVIDER;
      }

      // Make sure that we didn't push the values out of the acceptable range, and then map
      // them to their respective maximums
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
