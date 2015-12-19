//#define MOTOR_TWEENER_DEBUG 1

#define MOVE_SIDE_FWD(side, speed) do{ \
  motor ## side  ->run(RELEASE);     \
  motor ## side  ->setSpeed(speed);  \
  motor ## side  ->run(FORWARD);     \
}while(0)

#define MOVE_SIDE_BAK(side, speed) do{ \
  motor ## side  ->run(RELEASE);     \
  motor ## side  ->setSpeed(speed);  \
  motor ## side  ->run(BACKWARD);     \
}while(0)

int sign(int x){
  return x >= 0 ? 1 : -1;
}

class Motors {
  public:
    static const int DELAY_TIME = 3;
    static const int MIN_SPEED  = 100;

  private:
    static void updateValue(int & current, int & target){
      if(current != target){
        // First if we are going into the range [-MIN_SPEED, MIN_SPEED], we skip either across it or to zero
        if(abs(target) > MIN_SPEED && abs(current) < MIN_SPEED){
          // Are we going from fwd to backward or vice versa?
          bool switchDirections = ( 
               (target >= 0 && current >= 0)
            || (target <= 0 && current <= 0))
            ? 1   // If we are not switching directions
            : -1; // If we are switching directions
          
          current = sign(target) * switchDirections * MIN_SPEED;
        }else if(abs(target) < MIN_SPEED && abs(current) < MIN_SPEED){
          current = 0;
          target = 0;
        }else{
          int delta = target - current;
          int dir   = sign(delta);
          delta     = abs(delta);
          
          current += dir * min(2, delta);  
        }

        #ifdef MOTOR_TWEENER_DEBUG
          Serial.print("Update : "); Serial.println(current);
        #endif
      }
    }
  
  public:  
    Motors() : 
    left(0), leftTarget(0),
    right(0), rightTarget(0),
    lastUpdateTime(millis() - DELAY_TIME)
    {}

    void setSpeedImmediate(int newLeft, int newRight){
      leftTarget  = left  = newLeft;
      rightTarget = right = newRight;
      update();
    }
  
    void setTargetSpeed(int newLeftTarget, int newRightTarget){
      if(leftTarget != newLeftTarget && rightTarget != newRightTarget){
        leftTarget  = newLeftTarget;
        rightTarget = newRightTarget;
        #ifdef MOTOR_TWEENER_DEBUG
          Serial.println("New Target: ");
          Serial.print("    Left : "); Serial.println(leftTarget);
          Serial.print("    Right: "); Serial.println(rightTarget);
        #endif
      }
    }
    
    void update(){
      long now = millis();
      if(now - DELAY_TIME > lastUpdateTime){
        lastUpdateTime = now;
        
        updateValue(left,  leftTarget);
        updateValue(right, rightTarget);
       
        if(left > 0){
          MOVE_SIDE_FWD(LEFT, left);
        }else{
          MOVE_SIDE_BAK(LEFT, abs(left));
        }
        if(right > 0){
          MOVE_SIDE_FWD(RIGHT, right);
        }else{
          MOVE_SIDE_BAK(RIGHT, abs(right));
        }
      }
    }
  private:
    int left,  leftTarget;
    int right, rightTarget;
    long lastUpdateTime;
  
};
