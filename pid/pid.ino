/*
 >^/M! (FL)       \^< M2 (FR)
   ----------------
  |                |
  |                |
  |                |
  |                |
  |                |
   ----------------
 ^<\M3 (BL)       /^> M4 (BR)
 left - ACW <
 right - CW >
 */

#include <SPI.h>
#include <PS3BT.h>
#include <AutoPID.h>

USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd);
//pid settings and gains
#define OUTPUT_MIN 0
#define OUTPUT_MAX 255
#define KP 0.2
#define KI 0.5
#define KD 0.0001
double start, setP1, out1, setP2, out2, setP3, out3, setP4, out4;
AutoPID m1(&start, &setP1, &out1, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);
AutoPID m2(&start, &setP2, &out2, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);
AutoPID m3(&start, &setP3, &out3, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);
AutoPID m4(&start, &setP4, &out4, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);

int Led = 13;
int x1, x2, y1, y2, p1, p2, p3, p4, s, vec;
int m11 = 3; //FL
int m12 = 4;
int m21 = 5; //FR
int m22 = 6;
int m31 = 13; //BL
int m32 = 8;
int m41 = 11; //BR
int m42 = 12;

void setup() {
   start = (double) 0;
   Serial.begin(115200);

   if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }

  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
  pinMode(m11, OUTPUT);
  pinMode(m21, OUTPUT);
  pinMode(m31, OUTPUT);
  pinMode(m41, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(m22, OUTPUT);
  pinMode(m32, OUTPUT);
  pinMode(m42, OUTPUT);
  analogWrite(m11, 0);
  analogWrite(m21, 0);
  analogWrite(m31, 0);
  analogWrite(m41, 0);
  
  m1.setBangBang(255);
  m1.setTimeStep(4);
  m2.setBangBang(255);
  m2.setTimeStep(4);
  m3.setBangBang(255);
  m3.setTimeStep(4);
  m4.setBangBang(255);
  m4.setTimeStep(4);

}

void loop() {

  Usb.Task();
  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
    
    //Taking Analog input from joystick
    x1 =  map(PS3.getAnalogHat(LeftHatX), OUTPUT_MIN, OUTPUT_MAX, -122, 123);
    y1 =  map(PS3.getAnalogHat(LeftHatY), OUTPUT_MIN, OUTPUT_MAX, -122, 123);
    x2 =  map(PS3.getAnalogHat(RightHatX), OUTPUT_MIN, OUTPUT_MAX, -122, 123);
    //Projections on motor lines
    s = sqrt(2);
    p1 = x1+y1/s;
    p2 = -x1+y1/s;
    p3 = -x1+y1/s;
    
    p4 = x1+y1/s;
    //Printing all values
    Serial.println(x1);
    Serial.println(y1);
    Serial.println(x2);
    Serial.println(p1);
    Serial.println(p2);
    Serial.println(p3);
    Serial.println(p4); 
    if (p1==0 && p2==0 && p3==0 && p4==0) {
      analogWrite(m11, 0);
      analogWrite(m21, 0);
      analogWrite(m31, 0);
      analogWrite(m41, 0);
    }
    if (x2 == 0) {
      if (p1>0) {
        Serial.println("I");
        p1 = map(p1, 0, 173, OUTPUT_MIN, OUTPUT_MAX);
        setP1 = p1;
        m1.run();
        analogWrite(m11, out1);
        digitalWrite(m12, LOW);
      }
      else {
        Serial.println("II");
        p1 = map(p1, -173, 0, OUTPUT_MAX, OUTPUT_MIN);
        setP1 = p1;
        m1.run();
        analogWrite(m11, out1);
        digitalWrite(m12, HIGH);
      }
      if (p2>0) {
        Serial.println("III");
        p2 = map(p2, 0, 173, OUTPUT_MIN, OUTPUT_MAX);
        setP2 = p2;
        m2.run();
        analogWrite(m21, out2);
        digitalWrite(m22, LOW);
      }
      else {
        Serial.println("IV");
        p2 = map(p2, -173, 0, OUTPUT_MAX, OUTPUT_MIN);
        setP2 = p2;
        m2.run();
        analogWrite(m21, out2);
        digitalWrite(m22, HIGH);
      }
      if (p3>0) {
        Serial.println("V");
        p3 = map(p3, 0, 173, OUTPUT_MIN, OUTPUT_MAX);
        setP3 = p3;
        m3.run();
        analogWrite(m31, out3);
        digitalWrite(m32, LOW);
      }
      else {
        Serial.println("VI");
        p3 = map(p3, -173, 0, OUTPUT_MAX, OUTPUT_MIN);
        setP3 = p3;
        m3.run();
        analogWrite(m31, out3);
        digitalWrite(m32, HIGH);
      }
      if (p4>0) {
        Serial.println("VII");
        p4 = map(p4, 0, 173, OUTPUT_MIN, OUTPUT_MAX);
        setP4 = p4;
        m4.run();
        analogWrite(m41, out4);
        digitalWrite(m42, LOW);
      }
      else {
        Serial.println("VIII");
        p4 = map(p4, -173, 0, OUTPUT_MAX, OUTPUT_MIN);
        setP4 = p4;
        m4.run();
        analogWrite(m41, out4);
        digitalWrite(m42, HIGH);
      }
    }
  
    else {
    if (x2>0) { //CW turn
      vec = map(x2, 0, 123, 0, 150);
      analogWrite(m11, vec);
      analogWrite(m21, vec);
      analogWrite(m31, vec);
      analogWrite(m41, vec);
      digitalWrite(m12, LOW);
      digitalWrite(m22, LOW);
      digitalWrite(m32, HIGH);
      digitalWrite(m42, HIGH);    
    }
    else { //ACW turn
      vec = map(x2, -122, 0, 150, 0);
      analogWrite(m11, vec);
      analogWrite(m21, vec);
      analogWrite(m31, vec);
      analogWrite(m41, vec);
      digitalWrite(m12, HIGH);
      digitalWrite(m22, HIGH);
      digitalWrite(m32, LOW);
      digitalWrite(m42, LOW);
    }
  }

  if (PS3.getButtonClick(UP)) {

    digitalWrite(Led, HIGH);
    Serial.print(F("\r\nUp"));

     if (PS3.PS3Connected) {
      PS3.setLedOff();
      PS3.setLedOn(LED1);
    }

  }

}

  //Serial.println("------------"); 
}
