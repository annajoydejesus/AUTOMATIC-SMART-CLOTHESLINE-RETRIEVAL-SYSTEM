//// AUTOMATIC SMART CLOTHESLINE RETRIEVAL SYSTEM -- Arduino1

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);
byte tx = 1;

#define IN1 10
#define IN2 9
#define IN3 7
#define IN4 6

int RainSensor = 13; /// sensor 1
int Light = A0; /// sensor 2
int InfraSen0 = A2; /// sensor 3.a -- OUTSIDE IR
int InfraSen1 = A1; /// sensor 3.b -- INSIDE IR

String textForSMS;
void setup(){
  lcd.begin(40, 2);
  delay(100);
  pinMode(tx, OUTPUT);
  pinMode(RainSensor, INPUT);
  pinMode(Light, INPUT);
  pinMode(InfraSen0, INPUT);
  pinMode(InfraSen1, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(8, OUTPUT);
  
  mySerial.begin(9600);
  Serial.begin(9600);


}

void INSIDE() /// COUNTERCLOCKWISE
{ 

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("GOING INSIDE");
  delay(1000);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(100);
}

void OUTSIDE(){ /// CLOCKWISE

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("GOING OUTSIDE");
  delay(1000);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(100);
}

void InPos() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("In Position");
  delay(500);
   }

void OFF() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("OFF");
//delay(500);
   }

void servo_IN(){
digitalWrite(8,HIGH);
}

void servo_OUT(){
digitalWrite(8,LOW);
}

void loop(){
int Rain = digitalRead(RainSensor);
Serial.print("RS:");
Serial.println(Rain); /// Rain Sensor value reading
int LDR = analogRead(Light);
Serial.print("LDR:");
Serial.println(LDR); delay(50);
int IR0 = analogRead(InfraSen0);
Serial.print("IR0:");
Serial.println(IR0); delay(50);
int IR1 = analogRead(InfraSen1);
Serial.print("IR1:");
Serial.println(IR1); delay(50);

///morning
if (LDR>=20){
  servo_OUT();
}

///dry
else if (Rain == LOW){
  servo_OUT();
}

/// eve

if (Rain == HIGH){
  servo_IN();
}

///rain
else if (LDR<=20){
  servo_IN();
}


if (LDR<=20){
if (Rain == LOW){ /// EVENING DRY
if (IR1 == 1){
  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("         OH! IT'S EVENING!          ");
    delay(100);
    lcd.setCursor(0,1);
    lcd.print("IT'S TIME FOR THE CLOTHES TO GO INSIDE!");
    delay(150);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("        Just wait a second...          ");
    delay(100);


    Serial.print("AT+CMGF=1\r");
    delay(100);
    Serial.print("AT+CMGS=\"+639383493888\"\r");
    Serial.print("YOUR CLOTHES BEING MOVED SAFELY.\r");
    delay(500);
    
INSIDE(); delay(1000);
lcd.clear();
lcd.print("hooray! YOUR CLOTHES ARE SAFELY COVERED!");

    
    Serial.println((char)26); // End AT command with a ^Z, ASCII code 26
    delay(200);
    Serial.println();
    
OFF(); delay(200);
}
}
}


if (LDR<=20){
if (Rain == HIGH){ /// EVENING RAINING
if (IR1 == 1){
  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("         OH! IT'S EVENING!          ");
    delay(100);
    lcd.setCursor(0,1);
    lcd.print("IT'S TIME FOR THE CLOTHES TO GO INSIDE!");
    delay(150);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("        Just wait a second...          ");
    delay(100);

    Serial.print("AT+CMGF=1\r");
    delay(100);
    Serial.print("AT+CMGS=\"+639383493888\"\r");
    Serial.print("YOUR CLOTHES BEING MOVED SAFELY.\r");
    delay(500);
    
INSIDE(); delay(1000);
lcd.clear();
lcd.print("hooray! YOUR CLOTHES ARE SAFELY COVERED!");

    
    Serial.println((char)26); // End AT command with a ^Z, ASCII code 26
    delay(200);
    Serial.println();
    
OFF(); delay(200);
}
}
}

else if (LDR>=20){
if (Rain == HIGH){ /// morning raining
if (IR1 == 1){ 
  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("         OH, NO! IT'S RAINING!          ");
    delay(100);
    lcd.setCursor(0,1);
    lcd.print("DON'T WORRY! Clothes will go INSIDE!");
    delay(150);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("        Just wait a second...       ");
    delay(100);


    Serial.print("AT+CMGF=1\r");
    delay(100);
    Serial.print("AT+CMGS=\"+639383493888\"\r");
    Serial.print("YOUR CLOTHES ARE BEING MOVED INSIDE.\r");
    delay(500);
     
INSIDE(); delay(1000);
lcd.clear();
lcd.print("hooray! YOUR CLOTHES ARE SAFELY COVERED!");
    
    Serial.println((char)26); // End AT command with a ^Z, ASCII code 26
    delay(200);
    Serial.println();

OFF(); delay(200);

}
}
}

  /// morning DRY
if (LDR>=20){
if (Rain == LOW){
if (IR0 == 1){
   
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("         OH! IT'S SUNNY DAY!          ");
    delay(100);
    lcd.setCursor(0,1);
    lcd.print("     LET'S DRY YOUR CLOTHES OUTSIDE!     ");
    delay(150);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("        Just wait a second...       ");
    delay(100);

    Serial.print("AT+CMGF=1\r");
    delay(100);
    Serial.print("AT+CMGS=\"+639383493888\"\r");
    Serial.print("YOUR CLOTHES ARE BEING MOVED OUTSIDE.\r");
    delay(500);
    
OUTSIDE(); delay(1000);
lcd.clear();
lcd.print("hooray! YOUR CLOTHES ARE OUTSIDE!");
    
    Serial.println((char)26); // End AT command with a ^Z, ASCII code 26
    delay(200);
    Serial.println();
    
OFF(); delay(200);

}
}
}

/// IR SENSOR

/// EVENING DRY, IR
else if (LDR<=20){
if (Rain == LOW){ 
  if (IR1 == 1003){
  InPos();
}
}
}

/// EVENING RAINING, IR
if (LDR<=20){
if (Rain == HIGH){ 
  if (IR1 == 1003){
  InPos();
}
}
}

 /// morning raining, IR
else if (LDR>=20){
if (Rain == HIGH){
if (IR1 == 1){ 
InPos();
}
}
}

  /// morning DRY, IR
if (LDR>=20){
if (Rain == LOW){
if (IR0 == 1003){
InPos();
  
}
}
}

  
}  ///end
