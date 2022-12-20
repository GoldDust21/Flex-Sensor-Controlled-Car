#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
RF24 radio(7, 8);
unsigned long currentMillis;
unsigned long prevMillis;
unsigned long txIntervalMillis = 1000; // send once per second
const byte address[6] = {"00002"};
const int flexpin1=A0;
const int flexpin2=A1;
struct MyStruct {
 int sensorVal1=0;
 int sensorVal2=0;
}myStruct;
void setup() {
  pinMode(flexpin1, INPUT);
  pinMode(flexpin2, INPUT);
   radio.begin();
   radio.setChannel(76);  //76 library default
   //RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX
   radio.setPALevel(RF24_PA_HIGH);
   radio.setDataRate( RF24_250KBPS );
radio.openWritingPipe(address);
  Serial.begin(9600);
}
void loop() {
    currentMillis = millis();
   if (currentMillis - prevMillis >= txIntervalMillis)
   {
      send();
      Serial.print("Sensor1=");
      Serial.print(myStruct.sensorVal2);
      Serial.print("Sendsor2 = ");
      Serial.println(myStruct.sensorVal2);
      prevMillis = millis();
   }

}
void send()
{
   myStruct.sensorVal1 = analogRead(flexpin1);
   myStruct.sensorVal2 = analogRead(flexpin2);
   radio.write(&myStruct,sizeof(myStruct));
}
