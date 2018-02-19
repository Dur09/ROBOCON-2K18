    /*
    * Arduino Wireless Communication Tutorial
    *       Example 1 - Receiver Code
    *                
    * by Dejan Nedelkovski, www.HowToMechatronics.com
    * 
    * Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
    */
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include<Servo.h>
Servo myservo;
char text;
int flag=1;
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  //radio.setChannel(10);
  pinMode(3,OUTPUT);
  digitalWrite(3,LOW);
  myservo.attach(6);
}

void loop() 
{
  if (radio.available()) 
  {
    radio.read(&text, sizeof(text));
    Serial.println(text);
    if (text=='g')
    {
      digitalWrite(3,HIGH);
      delay(100);
      digitalWrite(3,LOW);
      Serial.println("LED");
      myservo.write(120);
    }
    else if(text=='o')
    {
      digitalWrite(3,HIGH);
      delay(100);
      digitalWrite(3,LOW);
      Serial.println("LED");
      myservo.write(50);
    }
  }
}
