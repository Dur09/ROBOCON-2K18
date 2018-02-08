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
#include <PS3BT.h>
#include <Servo.h>

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
int pwm[]={spd,spd,spd,spd};
int thresh =800;
boolean flag[4];
int count[4];
boolean vals[1000][4];
unsigned long startt;
int diff;
void setup() {

   Serial.begin(9600);
  Serial.print("start");
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
    
   for(int i =0;i<4;i++)
    {Serial.print(count[i]);
    Serial.print("\t");
    }
    Serial.println(" ");
    delay(100);
    
    //Serial.println(diff);

    
    
    analogWrite(m11, pwm[0]);
    analogWrite(m21, pwm[1]);
    analogWrite(m31, pwm[2]);
    analogWrite(m41, pwm[3]);



  Serial.println("------------");
//}
}

