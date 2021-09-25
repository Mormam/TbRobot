//Arduino Human Following Robot
// Created By DIY Builder
// You have to Install the AFMotor and NewPing library Before Uploading the sketch//
// To install the libraries ( first download the AF Motor driver, NewPing and Servo Library zip file //
// then Go to Skecth >> Include Library >> Add .Zip Library >> Select The downloaded zip file >> Done) //
// Contact me on instagram for any question(Insta Id : DIY.Builder)


#include<NewPing.h>
#include<Servo.h>
#include<AFMotor.h>
#define TRIGGER_PIN A1
#define ECHO_PIN A0
#define MAX_DISTANCE 100
  

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);


AF_DCMotor Motor1(1);
AF_DCMotor Motor2(2);
int distance = 100;

Servo myservo;
 
int pos =0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(9);
  myservo.write(90);
    // turn on motor #2
  Motor1.setSpeed(200);
  Motor1.run(RELEASE);
  Motor2.setSpeed(200);
  Motor2.run(RELEASE);
  distance = readPing();
}


void loop() {
  int distanceRight = 0;
  int distanceLeft = 0;
  
  // put your main code here, to run repeatedly:

  delay(50);
  distance = readPing();
  Serial.print("distance");
  Serial.println(distance);
  
if(distance<=40){
  Motor1.setSpeed(0);
  Motor1.run(RELEASE);
  Motor2.setSpeed(0);
  Motor2.run(RELEASE);
  distanceRight = lookRight();
  delay(300);
  distanceLeft = lookLeft();
  delay(300);
  if(distance >= distanceLeft) {
    Motor1.setSpeed(200);
    Motor1.run(FORWARD);
    Motor2.setSpeed(200);
    Motor2.run(BACKWARD);
    delay(1000);
  }else {
    Motor1.setSpeed(200);
    Motor1.run(BACKWARD);
    Motor2.setSpeed(200);
    Motor2.run(FORWARD);
    delay(1000);
  }
}else {
  Motor1.setSpeed(120);
  Motor1.run(FORWARD);
  Motor2.setSpeed(120);
  Motor2.run(FORWARD);
  delay(100);
}
}

 int lookRight(){  
  myservo.write(45);
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(90);
  return distance;
}

int lookLeft(){
  myservo.write(135);
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(90);
  return distance;
  delay(100);
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  Serial.print(sonar.ping_cm());
  if (cm==0){
    cm=250;
  }
  return cm;
}
