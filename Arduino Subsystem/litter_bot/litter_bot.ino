#include <SoftwareSerial.h>
#include <Servo.h>

//Servo Limits
////////////////////////////////////
#define J1SERVO_MIN 0
#define J1SERVO_MAX 160
#define J2SERVO_MIN 70
#define J2SERVO_MAX 160
////////////////////////////////////

//Arm Servo Objects
Servo joint1servo;         //range is 0 to 160. midpoint is 90
Servo joint2servo;         // range is 70 to 160
Servo gripperservo;       //range is 15 to 85? open is 85, close is 15

//Drive Motor Pins
int driveLPin = 5; // PWM for left motor
int driveRPin = 11;  // PWM for right motor
int dirLPin = 12;   //direction for left motor  
int dirRPin = 13;   //direction for right motor
char keyboard_input = 0;

// int current_angleJ1 = 90;
// int current_angleJ2 = 115;
// int current_angleG = 50;

int current_angleJ1 = joint1servo.read();
int current_angleJ2 = joint2servo.read();
int current_angleG = gripperservo.read();

void drive_forward()
{
  //Set wheel directions to move forward
  digitalWrite(dirLPin,0);
  digitalWrite(dirRPin,1);
  //Drive forward for t time in ms and stop.
  analogWrite(driveLPin,80);
  analogWrite(driveRPin,80);
  delay(20);
}

void drive_backward()
{
    //Set wheel directions to move backward
  digitalWrite(dirLPin,1);
  digitalWrite(dirRPin,0);
  //Drive forward for t time in ms and stop.
  analogWrite(driveLPin,80);
  analogWrite(driveRPin,80);
  delay(20);
}

void turn_left()
{
    //Set wheel directions to move forward
  digitalWrite(dirLPin,0);
  digitalWrite(dirRPin,1);
  //Turn left
  analogWrite(driveLPin,20);
  analogWrite(driveRPin,120);
  delay(20);
}

void turn_right()
{
    //Set wheel directions to move forward
  digitalWrite(dirLPin,0);
  digitalWrite(dirRPin,1);
  //Turn left
  analogWrite(driveLPin,120);
  analogWrite(driveRPin,20);
  delay(20);
}

void arm_stow(){
  //Stow position
joint1servo.write(140);
delay(1000);
joint2servo.write(0);
//gripperservo.write(50);
}

void arm_deploy(){
// straight out
joint1servo.write(18);
delay(1000);
joint2servo.write(75);
}

//////////////////////////////////////////////////////////////////////////////////////////

void arm_up()
{
  //Serial.println(current_angleJ1);
  if (current_angleJ1<J1SERVO_MAX)
    {
      current_angleJ1+= 5;
      joint1servo.write(current_angleJ1);
    }
  else
    Serial.println("Max position reached");
  delay(20);
}

void arm_down()
{
  if (current_angleJ1>J1SERVO_MIN)
    {
      current_angleJ1-= 5;
      joint1servo.write(current_angleJ1);
    }
  else
    Serial.println("Min position reached");
  delay(20);
}


void arm_right()
{
  if (current_angleJ2<J2SERVO_MAX)
    {
      current_angleJ2+= 5;
      joint2servo.write(current_angleJ2);
    }
  else
    Serial.println("Max position reached");
  delay(20);
}

void arm_left()
{
  if (current_angleJ2>J2SERVO_MIN)
    {
      current_angleJ2-= 5;
      joint2servo.write(current_angleJ2);
    }
  else
    Serial.println("Max position reached");
  delay(20);
}

void gripper_close(){
  gripperservo.write(85);
  delay(20);
}

void gripper_open(){
  gripperservo.write(15);
  delay(20);
}


/////////////////////////////////////////////////////////////////////////////////////////
// Setup 
////////////////////////////////////////////////////////////////////////////////////////

void setup() {
// Serial Setup
Serial.begin(9600); 
Serial.println("Use AWSD keys to drive, IJKL keys to command arm:");

// Attach servos
joint1servo.attach(9);
joint2servo.attach(6);
gripperservo.attach(3);

// Set pinmodes
pinMode(driveLPin, OUTPUT);
pinMode(driveRPin, OUTPUT);


}

void loop() {
// Check for serial input. Call function based on input string. 

if(Serial.available()>0){
  keyboard_input = Serial.read();

  switch(keyboard_input)
{
  case 'w':
    Serial.println("drive forward");
    drive_forward();
    break;
  case 's':
    Serial.println("drive backward");
    drive_backward();
    break;
  case 'a':  
    Serial.println("left");
    turn_left();
    break;
  case 'd':
    Serial.println("right");
    turn_right();
    break;
  case 'n':
    Serial.println("stow position");
    arm_stow();
    break;
  case 'm':
    Serial.println("straight out");
    arm_deploy();
    break;
  case 'j':
    Serial.println("arm left");
    arm_left();
    break;
  case 'k':
    Serial.println("arm down");
    arm_down();
    break;
  case 'l':
    Serial.println("arm right");
    arm_right();
    break;
  case 'i':
    Serial.println("arm up");
    arm_up();
    break;
  case 'o':
    Serial.println("gripper open");
    gripper_open();
    break;
  case 'c':
    Serial.println("gripper close");
    gripper_close();
    break;

}
  }

  digitalWrite(driveLPin,LOW);
  digitalWrite(driveRPin,LOW);

  
}
