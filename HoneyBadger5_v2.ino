

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
//double angle;// Potential to be more accurate then the float. ******************************To be tested
float delta_angle;// Delta between requested heading and actual heading updated in the locate() funtions
float heading;// Heading Measured by Gyro
void xbee_check();


Gyro gyro;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Create the motor shield object with the default I2C address 0x61
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
// Select which 'port' M1, M2, M3 or M4. In this case, M1


void setup(){
  // Start Serial and Software Serial
  Serial.begin(9600);
  //ss1.begin(9600);
  Serial.print("START");
  error = ps2x.config_gamepad(13,8,7,12, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  Serial.print(error);
  
  AFMS.begin();  // create with the default frequency 1.6KHz
   // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(150);
  myMotor->run(FORWARD);
  // turn on motor
  myMotor->run(RELEASE);
  
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
 
    error = ps2x.config_gamepad(13,8,7,12, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error

   if(error == 1) //skip loop if no controller found
  return; // Future implementation if the controller is not found mid round automatic function can jump on spining firing the weapon.
  
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
          /*
          Serial.print("LX, LY ");
          ss1.print(LX);
          ss1.print(" , " );
          ss1.println(LY);
          */
            }
    myMotor->setSpeed(RX); 
 }
    
}

int locate(signed int xaxis,signed int yaxis)
{

  /*
   * r^2=(x-127)^2 + (y-127)^2
   */
  heading=gyro.value(); // Still testing with value.cor()
  //heading=0;// simulate heading of Zero Degrees
  xaxis=xaxis-128;// Center the X axis of the joystick
  yaxis=yaxis-128;// Center the Y axis of the joystick
  angle= atan2(yaxis,xaxis);// Calculate the angle form the coordinates 
  angle=angle*57.2958;// radian to degrees
  delta_angle=(angle-heading);
  
  if((delta_angle<5) &&(delta_angle>(-5)))
  {
    Serial.println("Exit Recursion");
    return 1;
  }
  
  //********************************* Printing used for testing
  Serial.print("X,Y: ");
  Serial.print(xaxis);
  Serial.print(",");
  Serial.println(yaxis);
  
  Serial.print("ATan2 function output: ");
  Serial.println(angle);

  Serial.print("Gyro output :");
  Serial.println(heading);

  //**********************************
  
  if(delta_angle>0)
  {// Spin Port side
   //SPIN_PS(200);
  // locate(xaxis, yaxis);
  }
  else 
  {// Spin Starboard side
   // SPIN_SB(200);
  // locate(xaxis, yaxis);
  }
  delay(500);
  /*
   * Ryan comment:
   * Delay was implemented because during testing the remote would disconnect 
   * Disconnection seems to be because we are sampling the data very fast
   * Without the delay the connection between the remote and the receiver would be lost 
   */
}



















