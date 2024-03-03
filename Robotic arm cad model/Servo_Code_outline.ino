#include <Servo.h>

Servo joint1servo;         //range is 0 to 160 nom is 90
Servo joint2servo;         // range is 70 to 160
Servo gripperservo;       //range is 10 to 50? open is 50 closed is 10

int current_angleJ1 = 90;
int current_angleJ2 = 115;
int current_angleG = 50;

void setup() {
  // put your setup code here, to run once:
joint1servo.attach(9);
joint2servo.attach(6);
gripperservo.attach(3);  
joint1servo.write(90);
joint2servo.write(115);
gripperservo.write(50);


}

void loop() {
  // put your main code here, to run repeatedly:


}

void movejoint1(int angle){     //range is 0 to 160 nom is 90
  if(angle>=0 && angle <=160){
  joint1servo.write(angle);
  delay(20);
  }
}
void movejoint2(int angle){     // range is 70 to 160
  if(angle>=70 && angle <=160){
  joint2servo.write(angle);
  delay(20);
  }
}
void movegripper(int angle){    //range is 10 to 50? open is 50 closed is 10
  if(angle>=10 && angle <=50){
  gripperservo.write(angle);
  delay(20);
  }
}
