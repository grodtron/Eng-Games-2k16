#include <PS2X_lib.h>

#include "Point.h"

class Controller : public PS2X{
  private:
    const int param1;
    const int param2;
    const int param3;
    const int param4;

    int error_count;

    Point left;
    Point right;
  private:
    void update_analog_sticks(){
      left.x *= 9;
      left.x += Analog(PSS_RX);
      left.x /= 10;

      left.y *= 9;
      left.y += Analog(PSS_RY);
      left.y /= 10;

      //TODO
    }

  public:
  Controller(int p1, int p2, int p3, int p4)
    : param1(p1), param2(p2), param3(p3), param4(p4)
    , error_count(0)
  {}

  void init(){
    int error;
    do{
      error = this->config_gamepad(param1,param2,param3,param4,
        true/*analog*/,
        false/*rumble*/);
    
      if(error){
        Serial.print("Controller Error: ");
        Serial.println(error);
      }
    }while(error);
    Serial.println("Controller connected");
  }

  /**
   * Try to read the game pad taking into account the number of successive errors.
   * 
   * After 10 errors in a row, try to re-initialize the pad.
   */
  bool read(){
    if(this->read_gamepad()){
      ++error_count;
      
      if(error_count > 10){
        error_count = 0;
        this->init();
      }
      
      return false;
    }else{
      error_count = 0;
      update_analog_sticks();
      return true;
    }
  }

  Point get_left(){
    return left;
  }

};

