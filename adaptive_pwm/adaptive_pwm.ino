/*
 >^/M! (FL)       \^< M2 (FR)
   ----------------
  |                |
  |                |
  |                |
  |                |
  |                |
   ----------------
 >v\M3 (BL)       /v< M4 (BR)
 left - ACW <
 right - CW >
 */

#include <SPI.h>

int pins[]={52,46,48,51};
int temp_pwm[]={50,50,50,50};
int m11 = 3; //FL
int m12 = 4;
int m21 = 11; //FR
int m22 = 12;
int m31 = 8; //BL
int m32 = 9;
int m41 = 5; //BR
int m42 = 6  ;
int spd = 50;
int pwm[]={50,50,50,50};
int thresh =800;
boolean flag[4];
int count[4];
boolean vals[1000][4];
unsigned long startt;
int diff;
int KP=3;
int prev[4];
void setup() {

   Serial.begin(9600);
  delay(5000);
   /*if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  */
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
  digitalWrite(m12, LOW);
  digitalWrite(m22, LOW);
  digitalWrite(m32, LOW);
  digitalWrite(m42, LOW);
  pinMode(pins[0], INPUT);
  pinMode(pins[1], INPUT);
  pinMode(pins[2], INPUT);
  pinMode(pins[3], INPUT);

}

void loop() {

    for (int i=0;i<4;i++)
    {
      flag[i]=LOW;
      count[i]=0;
    }
    for (int i =0;i<1000;i++)
    {
      for(int j=0;j<4;j++)
      {
        vals[i][j]=digitalRead(pins[j]);
      }
      
    }
    for (int i =0;i<1000;i++)
    {for (int j=0;j<4;j++)
      {
        if(vals[i][j]!=flag[j])
        {
          if (vals[i][j] == HIGH)
          {
            flag[j]=HIGH;
            count[j]++;
          }
          else
          {
             flag[j]=LOW;
          }
        }
      }
    }
     
    for(int i=0;i<4;i++)
    prev[i]=temp_pwm[i]-pwm[i];
    
    for (int i=0;i<4;i++)
    {
      int factor = (count[i] -40)/KP ;
      temp_pwm[i] = pwm[i] - factor + prev[i];
      Serial.print(factor);
      Serial.print("-");
      Serial.print(prev[i]);
      Serial.print("=");
      Serial.print(temp_pwm[i]);
      Serial.print("|\t");
    }
    Serial.println(" ");
   
    analogWrite(m11, temp_pwm[0]);
    analogWrite(m21, temp_pwm[1]);
    analogWrite(m31, temp_pwm[2]);
    analogWrite(m41, temp_pwm[3]);



  Serial.println("------------");
}

