//// SMART CLOTHESLINE

#include<Servo.h>
Servo myservo;
int sm = 2;
int pos = 0;
int val;


void setup(){
  myservo.attach(3);
  pinMode(sm,INPUT);

}

void loop(){
int smr = digitalRead(sm);

 if (smr == HIGH){
   myservo.write(0);
   delay(100);
 }

else{
  
  (smr = LOW);
   myservo.write(180);
   delay(100);
}
  
}
