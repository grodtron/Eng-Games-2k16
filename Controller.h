
#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <PS2X_lib.h>

#include "Point.h"
#include "MedianFilter.h"

class Controller : public PS2X{
  private:
    const int param1;
    const int param2;
    const int param3;
    const int param4;

    int error_count;

    MedianFilter<5> lxFilter;
    MedianFilter<5> lyFilter;
    MedianFilter<5> rxFilter;
    MedianFilter<5> ryFilter;

  public:
    Point left;
    Point right;
  private:
    void update_analog_sticks(){
      // TODO - once controls are finalized, remove any of these that are unused
//      left.x = lxFilter.update(Analog(PSS_LX) - 128);
//      left.y = lyFilter.update(128 - Analog(PSS_LY));
//
//      right.x = rxFilter.update(Analog(PSS_RX) - 128);
//      right.y = ryFilter.update(128 - Analog(PSS_RY));

      left.x = Analog(PSS_LX) - 128;
      left.y = 128 - Analog(PSS_LY);

      right.x = Analog(PSS_RX) - 128;
      right.y = 128 - Analog(PSS_RY);
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
        Debug.print("CE");
        Debug.println(error);
      }
    }while(error);
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
};

#endif
