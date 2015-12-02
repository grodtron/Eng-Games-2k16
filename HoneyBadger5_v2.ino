/*
 * Auther: Ryan Cooke
 * Subject: Concordia Eng Games Machine Honey Badger 5 Main machine code
 * save date:11/29/2015
 */
#include <PS2X_lib.h>  //for v1.6
#include <XBee.h>
#include <math.h>
#include "Gyro.h"
#include "Motor.h"
PS2X ps2x; // create PS2 Controller Class

#include <SoftwareSerial.h>// We'll use SoftwareSerial to communicate with the XBee:
// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial ss1(2, 3); // RX, TX

//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you conect the controller, 
//or call config_gamepad(pins) again after connecting the controller.
int error = 0; 
byte type = 0;
byte vibrate = 0;
int LX,LY,RX,RY;
float angle;// Heading asked by the controller
float delta_angle;// Delta between requested heading and actual heading updated in the locate() funtions
float heading;// Heading Measured by Gyro
void xbee_check();


Gyro gyro;
/*
XBee xbee = XBee();
XBeeResponse response1 = XBeeResponse();

// create reusable response objects for responses we expect to handle 
ZBRxResponse rx = ZBRxResponse();
ModemStatusResponse msr = ModemStatusResponse();


// allocate two bytes for to hold a 10-bit analog reading
uint8_t payload[] = { 0,0 };// size 

// with Series 1 you can use either 16-bit or 64-bit addressing

// 16-bit addressing: Enter address of remote XBee, typically the coordinator
Tx16Request tx = Tx16Request(0xBBAD, payload, sizeof(payload));
TxStatusResponse txStatus = TxStatusResponse();

int locate(int x_axis, int y_axis, int heading);
*/
void setup(){
  // Start Serial and Software Serial
  Serial.begin(9600);
 // ss1.begin(9600);
  Serial.print("START");
  error = ps2x.config_gamepad(13,8,7,12, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  Serial.println("START");
      gyro.callibrate();
}


//****************************************************************************START LOOP
void loop(){
   /* You must Read Gamepad to get new values
   Read GamePad and set vibration values
   ps2x.read_gamepad(small motor on/off, larger motor strenght from 0-255)
   if you don't enable the rumble, use ps2x.read_gamepad(); with no values
   
   you should call this at least once a second
   */
    gyro.update(); 
 if(error == 1) //skip loop if no controller found
  return; 
  
 else { //DualShock Controller
  
    ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
    
   // if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
     /*   Button labels: PSB_START, PSB_SELECT, PSB_PAD_UP,PSB_PAD_RIGHT,PSB_PAD_LEFT,PSB_PAD_DOWN,
      *    Call button state -> ps2x.Button(LABEL)
      *    Function call: 
      *    NewButtonState() will be true if any button changes state
      *    ButtonPressed(LABEL); Will be true if button was just pressed
      *    ButtonREleased(LABEL); Will be true if button was just released
      *    NewButtonState(LABEL); will be true if button was just pressed or released
      *    
      *    JoyStick LABEL: PSS_LY,PSS_LX,PSS_RY,PSS_RX
      *    Analog position call
      *    ps2x.Analog(JS LABEL); return value of that axis 
         */
   
    
 LX=ps2x.Analog(PSS_LX);
 LY=ps2x.Analog(PSS_LY);
 RX=ps2x.Analog(PSS_RX);
 RY=ps2x.Analog(PSS_RY);
 
 if(ps2x.Button(PSB_L1)|| ps2x.Button(PSB_R1)){

          locate(LX,LY);
       
            }
    
 }
    
}

int locate(signed int xaxis,signed int yaxis)
{

  /*
   * r^2=(x-127)^2 + (y-127)^2
   */
  heading=gyro.value(); // Still testing with value.cor()
  //heading=0;// simulate heading of Zero Degrees
  xaxis=xaxis-128;
  yaxis=yaxis-128;
  
  Serial.print("X,Y: ");
  Serial.print(xaxis);
  Serial.print(",");
  Serial.println(yaxis);
  angle= atan2(yaxis,xaxis);
  
  angle=angle*57.2958;// radian to degrees
  Serial.print("ATan2 function output: ");
  Serial.println(angle);

  Serial.print("Gyro output :");
  Serial.println(heading);
  delta_angle=(angle-heading);
  if(delta_angle>0)
  {
   //SPIN_PS(delta_angle);
  }
  else 
  {
   // SPIN_SB(-delta_angle);
  }
  delay(500);
  return 1;
}



















