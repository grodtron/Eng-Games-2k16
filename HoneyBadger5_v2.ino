/*
* Auther: Ryan Cooke
* Subject: Concordia Eng Games Machine Honey Badger 5 Main machine code
* save date:11/29/2015
*/
#include <PS2X_lib.h>  //for v1.6
#include <XBee.h>
#include <Adafruit_MotorShield.h>// for I2C Motor sheild NOT FOR COMP
#include "utility/Adafruit_PWMServoDriver.h"// for I2C Motor sheild NOT FOR COMP
#include <math.h>
#include "Gyro.h"
//#include "Motor.h"
#include "Motor_Sheild.h"
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
//double angle;// Potential to be more accurate then the float. ******************************To be tested
void xbee_check();
bool forward=0;// 
int left_off=0;
int right_off=0;
int PWM;
int count;
int sample_x=0;
int sample_y=0;
const int loops=10;
int sample_array[loops][1];
int x=0;
int y=0;
Gyro gyro;


Motor badger;// This is the object for the 2x Motor setup


void setup(){
  // Start Serial and Software Serial
  Serial.begin(9600);
  //ss1.begin(9600);
  Serial.print("START");
  error = ps2x.config_gamepad(13,8,7,12, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  Serial.print(error);
  gyro.callibrate();

   badger.setup();
  PWM=0;
  count=0;// count the number of loops for sampling
}


//****************************************************************************START LOOP
void loop(){
  //Serial.println(PWM);
  if(count>loops)
  {
    count=0;
      x=x/(loops+1);
      y=y/(loops+1);
      LX=0;
      LY=0;
      for(int i=0; i<loops;i++)
      {
      
        if((sample_array[i][0]-x)>10)
        {
          sample_array[i][0]=x;
        }
        if((sample_array[i][1]-y)>10)
        {
          sample_array[i][1]=y;
        }
        LX=LX+sample_array[i][0];
        LY=LY+sample_array[i][1];
/*
      Serial.print(sample_array[i][0]);
      Serial.print(" , ");
      Serial.println(sample_array[i][1]);
*/
      }
       // Serial.println("LOOP");

      LX=LX/(loops);
      LY=LY/(loops);
      /*
      Serial.print("CORRECTED AV ");
      Serial.print(LX);
      Serial.print(" , ");
      Serial.println(LY);
      */
  }
  else
  {
    LX=ps2x.Analog(PSS_LX);
    LY=ps2x.Analog(PSS_LY);
    //RX=ps2x.Analog(PSS_RX);
    //RY=ps2x.Analog(PSS_RY);
    
    x=x+LX;
    y=y+LY;
    sample_array[count][0]=LX;
    sample_array[count][1]=LY;
    count++;
  }
  /* You must Read Gamepad to get new values
  Read GamePad and set vibration values
  ps2x.read_gamepad(small motor on/off, larger motor strenght from 0-255)
  if you don't enable the rumble, use ps2x.read_gamepad(); with no values
  
  you should call this at least once a second
  */
  gyro.update();
  error = ps2x.config_gamepad(13,8,7,12, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  
  if(error == 1) //skip loop if no controller found
  return; // Future implementation if the controller is not found mid round automatic function can jump on spining firing the weapon.
  
  else { //DualShock Controller
    
     ps2x.read_gamepad(false, vibrate);      //read controller and set large motor to spin at 'vibrate' speed

    
    // if(ps2x.Button(PSB_START))           //will be TRUE as long as button is pressed
    /*   Button labels: PSB_START, PSB_SELECT, PSB_PAD_UP,PSB_PAD_RIGHT,PSB_PAD_LEFT,PSB_PAD_DOWN,
    *  Call button state -> ps2x.Button(LABEL)
    *  Function call:
    *  NewButtonState() will be true if any button changes state
    *  ButtonPressed(LABEL); Will be true if button was just pressed
    *  ButtonREleased(LABEL); Will be true if button was just released
    *  NewButtonState(LABEL); will be true if button was just pressed or released
    *
    *  JoyStick LABEL: PSS_LY,PSS_LX,PSS_RY,PSS_RX
    *  Analog position call
    *  ps2x.Analog(JS LABEL); return value of that axis
    */
    
   
    if( ps2x.Button(PSB_R1)){
      forward=1;
      if(PWM<150)
      {
        PWM=150;
      }
      if(PWM!=255)
      {
      PWM++;
      }
    }

    if( ps2x.Button(PSB_L1)){
      forward=0;
      if(PWM<150)
      {
        PWM=150;
      }
      if(PWM!=255)
      {
      PWM++;
      }
      badger.BAK(PWM);
    }
    
     if(ps2x.Button(PSB_PINK))
     {
      PWM=0;
      forward=0;
      badger.STOP();
      return;
     }
     if(ps2x.Button(PSB_GREEN))
     {
      PWM=255;
      forward=1;
      badger.FWD(PWM);
      return;
     }
     if(ps2x.Button(PSB_RED))
     {
      PWM=255;
      forward=0;
      badger.BAK(PWM);
      count=0;
     }
   
     if(ps2x.Button(PSB_BLUE))
     {
     badger.flipper_on();
     }
     else
     {
     badger.flipper_off();
     }
     /*
     if(ps2x.Button(PSB_PAD_LEFT))
     {
      forward=0;
      if(PWM<150)
      { 
        PWM=150;
      }
      badger.TURN_LEFT(PWM);
      count=0;
    }



    if(ps2x.Button(PSB_PAD_RIGHT))
    {
      forward=0;
      if(PWM<150)
      {
        PWM=150;
      }
      badger.TURN_RIGHT(PWM);
      count=0;
    }
    
    if(ps2x.Button(PSB_PAD_UP))
    {
      forward=1;
      if(PWM<150)
      {
        PWM=150;
      }
     badger.FWD(PWM);

    }
    */
     Serial.println(LX);
     if(PWM>150)
     {
      if((LX<50)&&(forward))
      {
        badger.TURN_LEFT(PWM);
      }
      else if((LX>55)&&(LX<200)&&(forward))
      {
        badger.FWD(PWM);
      }
      else if((LX>205)&&(forward))
      {
       // Serial.println(x);
        badger.TURN_RIGHT(PWM);
      }
     }
     //** END OF LOOP
  }
  
}















