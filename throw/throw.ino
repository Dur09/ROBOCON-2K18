#include <Servo.h> 
int ruptPin = A2; 
int val = 0;
int count=0;
int result=70;
int top = 255;
long t1,t2,spd,maxspd,c=0;
int set=135;
int motor_pin[4]= {8,9,10,11};
int servoPin = 3; 
Servo Servo1; 

void setup()
{
    Serial.begin(9600);
    Servo1.attach(servoPin); 
    Servo1.write(30);
    delay(20);
    pinMode(7,OUTPUT);
    pinMode(6,OUTPUT);
    for(int i=0;i<4;i++)
    {
      pinMode(motor_pin[i],OUTPUT);
    }
    digitalWrite(7,HIGH);
    analogWrite(6,top);
    //delay(5000);
}

void loop()
{
  if(count<set)
  {
    
    digitalWrite(motor_pin[1],HIGH);
    digitalWrite(motor_pin[0],LOW);
    val = analogRead(ruptPin);
    while(val>500)
    {
      val=analogRead(ruptPin);
      if(val<500)
        count++;
    }
    //Serial.println(count);
    if(count%30==0)
    {
      count+=1;
      t2=micros();
      /*Serial.print("t1=");
      Serial.println(t1);
      Serial.print("t2=");
      Serial.println(t2);*/
      if(t2-t1>0)
      {
      spd=60000000/(t2-t1);
      Serial.println(spd);
      //Serial.print("top=");
      //Serial.println(top);
      }
      /*if(spd<=result)
      {
        if(top<255)
        top++;
        analogWrite(6,top);
      }
      else if(spd>result)
      {
        //top=map(result,0,spd,0,255);
        analogWrite(6,top-2);
        top-=2; 
      } */
      t1=micros();
    }
    
  }
  else
    {
      Servo1.write(0);
      delay(2000);
      digitalWrite(motor_pin[1],LOW);
      digitalWrite(motor_pin[0],LOW);
    }
}
