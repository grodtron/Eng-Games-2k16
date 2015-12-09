#include "Point.h"
#include "Controller.h"
Controller controller(13,8,7,12);

#include <Wire.h>
#include <Adafruit_MotorShield.h>
Adafruit_MotorShield AFMS;
Adafruit_DCMotor *leftMotor  = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

#include <math.h>

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");

  controller.init();

  AFMS.begin();

  Serial.println("Done!");

}

void loop() {

  if(controller.read()){
  
    Point left = controller.get_left();
  
    //left.print_self("left");

    float magnitude = left.magnitude();

    //Serial.print(magnitude);
    //left.print_self(" left");
    
    if(magnitude > 75){
      float angle = atan2(left.x, left.y) * 180 / PI;
      Serial.print("Running at: ");
      Serial.println(angle);

      const int cutoff_angle = 70;

      int fast = 255;
      
      int slow;
      if(abs(angle) <= cutoff_angle){
        slow = map(angle,0, cutoff_angle, 255, 128);
      }else{
        slow = 0;
      }

      if(angle < 0){
        leftMotor->setSpeed(slow);
        rightMotor->setSpeed(fast);        
      }else{
        leftMotor->setSpeed(fast);
        rightMotor->setSpeed(slow);
      }

      leftMotor->run(FORWARD);
      rightMotor->run(FORWARD);

    }else{
      rightMotor->run(RELEASE);
      leftMotor->run(RELEASE);      
    }
  }
}
