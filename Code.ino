#include<Servo.h>

#define TRIG_PIN A0
#define ECHO_PIN A1
#define MAX_DISTANCE 200
#define MAX_SPEED 190
#define MAX_SPEED_OFFSET 20

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

Servo myServo;

boolean goesForward=false;
int distance =100;
int speedSet=0;

void setup() {
  myServo.attach(10);
  myServo.write(115);
  delay(2000);
  distance=readPing();
  delay(100);
  distance=readPing();
  delay(100);
  distance=readPing();
  delay(100);
  distance=readPing();
  delay(100);
}

void loop() {
  int disR =0;
  int disL=0;
  delay(40);

  if(distance<=15)
  {
    moveStop();
    delay(100);
    moveBackward();
    delay(300);
    moveStop();
    delay(200);
    disR=lookRight();
    delay(200);
    disL=lookLeft();
    delay(200);

    if(disR>=distL){
      turnRight();
      moveStop();
      Serial.println("Turn right");
    }else{
      turnLeft();
      moveStop();
      Serial.println("Turn left");
    }
  }
  else{
    moveForward();
    Serial.println("Move Forward");
  }
  distance= readPing();
}
int lookRight(){
  myServo.write(50);
  delay(500);
  int distance=readPing();
  delay(100);
  myServo.write(115);
  return distance;
}
int lookLeft(){
  myServo.write(170);
  delay(500);
  int distance=readPing();
  delay(100);
  myServo.write(115);
  return distance;
  delay(100);
}
int readPing(){
  delay(70);
  int cm=sonar.ping_cm();
  if(cm==0){
    cm=250;
  }
  return cm;
}
void moveStop(){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
void moveForward(){
  if(!goesForward){
    goesForward=true;
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
    for(speedSet=0;speedSet<MAX_SPEED;speedSet+=2){
      motor1.setSpeed(sppedSet);
      motor2.setSpeed(sppedSet);
      motor3.setSpeed(sppedSet);
      motor4.setSpeed(sppedSet);
      delay(5);
    }
  }
}
void moveBackward(){
  goesForward=false;
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  for(speedSet=0;speedSet<MAX_SPEED;speedSet+=2){
      motor1.setSpeed(sppedSet);
      motor2.setSpeed(sppedSet);
      motor3.setSpeed(sppedSet);
      motor4.setSpeed(sppedSet);
      delay(5);
  }
}
void turnRight(){
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  delay(500);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
void turnLEFT(){
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(500);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
