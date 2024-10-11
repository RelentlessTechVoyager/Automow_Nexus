#include<Servo.h>
#include<NewPing.h>

#define TRIG_PIN A0
#define ECHO_PIN A1
#define MAX_DISTANCE 200
//centre- 115deg , Right- 60deg, left- 170deg
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

Servo myServo;

int distance =100;

void setup() {
  Serial.begin(9600);
  myServo.attach(9);
  myServo.write(115);
  delay(2000);
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
  distance=readPing();
  Serial.print("Distance:");
  Serial.println(distance);
  delay(300);
  
  if(distance<=15){
    delay(200);
    
    disR=lookRight();
    delay(200);
    
    disL=lookLeft();
    delay(200);

    if(disR>=disL){
      Serial.println("Turn right");
      delay(200);
      }
      else{
        Serial.println("Turn left");
        delay(200);
      }
  }else{
    Serial.println("Move forward");
    delay(1000);
    }
}

int lookRight(){
  myServo.write(60);
  delay(2000);
  int distance=readPing();
  Serial.print("Right Distance:");
  Serial.println(distance);
  delay(300);
  myServo.write(115);
  delay(1000);
  return distance;
}
int lookLeft(){
  myServo.write(170);
  delay(2000);
  int distance=readPing();
  Serial.print("left Distance:");
  Serial.println(distance);
  delay(300);
  myServo.write(115);
  delay(1000);
  return distance;

}
int readPing(){
  delay(70);
  int cm=sonar.ping_cm();
  if(cm==0){
    cm=250;
  }
  return cm;
}
