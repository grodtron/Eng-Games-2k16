#include "Point.h"
#include "Controller.h"
Controller controller(13,8,7,12);

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");

  controller.init();

  Serial.println("Done!");
  Serial.parseInt();
}

void loop() {

  controller.read();
  
  Point left(
    controller.Analog(PSS_LX),
    controller.Analog(PSS_LY));
  
  Point right(
    controller.Analog(PSS_RX),
    controller.Analog(PSS_RY));

  //right.print_self("right");
  left.print_self("left");
  
  // put your main code here, to run repeatedly:

}
