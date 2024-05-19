#include <SoftwareSerial.h>
#include <Servo.h>
#include <Wire.h>

//Servo Limits
////////////////////////////////////
#define J1SERVO_MIN 0
#define J1SERVO_MAX 160
#define J2SERVO_MIN 70
#define J2SERVO_MAX 160
////////////////////////////////////

//PING Sensor Constants
const int SigPin = 2;
float ping_invcmCosnt = (2*1000000)/(100*344.8); //cmDist=rawTime/invcmCosnt

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

// Variables to block other actions
char throw_away = 0;
bool stop = 0;



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
current_angleJ1 = 140;
delay(1000);
joint2servo.write(80);
current_angleJ2 = 80;
//gripperservo.write(50);
}

void arm_stow_right(){
  //Stow position
joint1servo.write(120);
current_angleJ1 = 120;
delay(1000);
joint2servo.write(160);
current_angleJ2 = 160;
//gripperservo.write(50);
}

void arm_deploy(){
// straight out
joint2servo.write(75);
current_angleJ2 = 75;
delay(1000);
joint1servo.write(8);
current_angleJ1 = 8;

}

//////////////////////////////////////////////////////////////////////////////////////////

void arm_up()
{
  // Increase the angle of the servo to move the gripper up
  if (current_angleJ1<J1SERVO_MAX)
    {
      current_angleJ1+= 5;
      joint1servo.write(current_angleJ1);
    }
  //else
    //Serial.println("Max position reached");
  delay(20);
}

void arm_down()
{
  // Decrease the angle of the servo to move the gripper down
  if (current_angleJ1>J1SERVO_MIN)
    {
      current_angleJ1-= 5;
      joint1servo.write(current_angleJ1);
    }
  //else
    //Serial.println("Min position reached");
  delay(20);
}


void arm_right()
{
  // Increase the angle of the servo to move the gripper right
  if (current_angleJ2<J2SERVO_MAX)
    {
      current_angleJ2+= 5;
      joint2servo.write(current_angleJ2);
    }
  //else
   // Serial.println("Max position reached");
  delay(20);
}

void arm_left()
{
  // Decrease the angle of the servo to move the gripper left
  if (current_angleJ2>J2SERVO_MIN)
    {
      current_angleJ2-= 5;
      joint2servo.write(current_angleJ2);
    }
  //else
   // Serial.println("Max position reached");
  delay(20);
}

void gripper_close()
{
  // Close configuration angle
  gripperservo.write(5);
  delay(20);
}

void gripper_open()
{
  // Open Configuration angle
  gripperservo.write(75);
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

gripper_open();

}

void loop() {
// Check for serial input. Call function based on input string. 

if(Serial.available()>0){
  keyboard_input = Serial.read();

  switch(keyboard_input)
{
  case 'z':
    stop = 0;
    break;
  case 'w':
    //Serial.println("drive forward");
    if (stop == 0){
      drive_forward();
    }
    break;
  case 's':
    //Serial.println("drive backward");
    if (stop == 0){
      drive_backward();
    }
    break;
  case 'a':  
    //Serial.println("left");
    if (stop == 0){
      turn_left();
    }
    break;
  case 'd':
    //Serial.println("right");
    if (stop == 0){
      turn_right();
    }
    break;
  case 'n':
    //Serial.println("stow position");
    arm_stow();
    break;
  case 'b':
    //Serial.println("straight out");
    arm_stow_right();
    break;
  case 'm':
    //Serial.println("straight out");
    arm_deploy();
    break;
  case 'j':
    //Serial.println("arm left");
    arm_left();
    break;
  case 'k':
    //Serial.println("arm down");
    arm_down();
    break;
  case 'l':
    //Serial.println("arm right");
    arm_right();
    break;
  case 'i':
    //Serial.println("arm up");
    arm_up();
    break;
  case 'o':
    //Serial.println("gripper open");
    gripper_open();
    break;
  case 'c':
    //Serial.println("gripper close");
    gripper_close();
    break;

}
  }
  // Bring the drive pins back to low at the end
  digitalWrite(driveLPin,LOW);
  digitalWrite(driveRPin,LOW);

  // PING Sensor Reading
  float rawTime;
  float cmDist; //declare variables
  pinMode(SigPin, OUTPUT);
  digitalWrite(SigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(SigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(SigPin, LOW);
  /* Now same Sign pin is to be used to monitor if the return echo has been received. Essentially, 
  Sig pin remains HIGH until a return echo is received and at that time it goes LOW. So measure
  the time duration for HIGH at the Sig pin */
  pinMode(SigPin, INPUT);
  rawTime = pulseIn(SigPin, HIGH); //measured in u-seconds
  cmDist = rawTime/ping_invcmCosnt;
  //Serial.println(cmDist);
  if (cmDist<16 && cmDist>0 && stop==0) {
    stop = 1;
    Serial.println(cmDist);
  }
  

}
