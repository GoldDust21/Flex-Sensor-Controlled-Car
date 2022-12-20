#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#define enA 9
#define in1 4
#define in2 5
#define enB 10
#define in3 6
#define in4 7
RF24 radio(2, 3); 
const byte address[6] = {"00002"}; 
int fin1;
int fin2;
int motorSpeedA = 0;
int motorSpeedB = 0;
struct MyStruct{
  int sensorval1=1;
  int sensorval2=1;
}myStruct;
const int trig=8;
const int echo=1;
long duration; 
int distance;
bool newData=false;
void setup() {
 radio.begin();
   radio.setChannel(76);  //76 library default
   //RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX
   radio.setPALevel(RF24_PA_HIGH);
   radio.setDataRate( RF24_250KBPS );
   radio.openReadingPipe(1, address);
   radio.startListening();
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(trig, OUTPUT); 
  pinMode(echo, INPUT); 
  Serial.begin(9600);  
}
void loop()
{
   getData();
   showData();
}

//==============

void getData()
{
   if ( radio.available() )
   {
      radio.read( &myStruct, sizeof(myStruct) );
      newData = true;
      delay(250);
   }
}

void showData()
{
   if (newData == true)
   {
      Serial.print("Data received >> ");
      Serial.print("Fin1=");
      Serial.print(myStruct.sensorval1);
      Serial.print("Fin2= ");
      Serial.println(myStruct.sensorval2);
      newData = false;
   }
}
/*void loop() {
  MyStruct myStruct;
  Receiver.startListening(); 
while(!Receiver.available()){
 
Receiver.read(&myStruct, sizeof(myStruct));
   Serial.println(myStruct.sensorval1);
   fin1=myStruct.sensorval1;
   fin2=myStruct.sensorval2;
    delay(500);
}
  
 
   //CalculateDistance();
  
  if(distance<50){
      if (fin1 <15 && fin2<50)
 {
motorSpeedA=0;
motorSpeedB=0;
 }
 if(fin1>15 && fin1<30){
      motorSpeedA=0;
    }
    if(fin2>50 && fin1<85){
      motorSpeedB=0;
    }
  else if (fin1 <15) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    //digitalWrite(in3, HIGH);
    //digitalWrite(in4, LOW);
    motorSpeedA = map(fin1, 15, 0, 0, 255);
    //motorSpeedB = map(yAxis, 300, 0, 0, 255);
  }
 else if(fin2<50){
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    motorSpeedB = map(fin2, 50, 0, 0, 255);   
 }
  
  if (fin1 > 30) {
     digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
     motorSpeedA = map(fin1, 30, 50, 0, 255);
     
   
  }
  if (fin2 > 85) {
     digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    motorSpeedB = map(fin2,85, 120, 0, 255); 
    
    if (motorSpeedA > 255) {
      motorSpeedA = 255;
    }
    if (motorSpeedB < 0) {
      motorSpeedB = 0;
    }
  }
  // Prevent buzzing at low speeds (Adjust according to your motors. My motors couldn't start moving if PWM value was below value of 70)
  if (motorSpeedA < 10) {
    motorSpeedA = 0;
  }
  if (motorSpeedB <10) {
    motorSpeedB = 0;
  }
  }
  else{ 
    if(fin1>15 && fin1<30){
      motorSpeedA=0;
    }
    if(fin2>50 && fin1<85){
      motorSpeedB=0;
    }
     if (fin1 <15 ) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    //digitalWrite(in3, HIGH);
    //digitalWrite(in4, LOW);
    motorSpeedA = map(fin1, 15, 0, 0, 255);
    //motorSpeedB = map(yAxis, 300, 0, 0, 255);
  }
   if(fin2<50){
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    motorSpeedB = map(fin2, 50, 0, 0, 255);   
 }
  
  if (fin1 > 30) {
     digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
     motorSpeedA = map(fin1, 30 , 50, 0, 255);
     
    if (motorSpeedA > 255) {
      motorSpeedA = 255;
    }
    if (motorSpeedB < 0) {
      motorSpeedB = 0;
    }
  }
  if (fin2 > 85) {
     digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    motorSpeedB = map(fin2, 85, 120, 0, 255);
  }
  // Prevent buzzing at low speeds (Adjust according to your motors. My motors couldn't start moving if PWM value was below value of 70)
  if (motorSpeedA < 10) {
    motorSpeedA = 0;
  }
  if (motorSpeedB < 10) {
    motorSpeedB = 0;
  }
  }
  analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
  analogWrite(enB, motorSpeedB); // Send PWM signal to motor B
  delay(100);
  }



int CalculateDistance(){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2; 
  return distance;
}*/
