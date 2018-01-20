
#include <Servo.h>
Servo myservo;
int count,count2=0;
int pos=60;
int x=20;
int threshold = 900;
int flag,flag3=0;
int flag4,flag5, flag6=0;
int flag2=0;
int top =100;    
int motor[2]= {7,6};      //{dir,pwm}
void setup() {
  pinMode(motor[0],OUTPUT);
  pinMode(motor[1],OUTPUT);
  digitalWrite(motor[0],HIGH);  
  pinMode(4,OUTPUT);
  digitalWrite(4,HIGH);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  analogWrite(motor[1],0);
  myservo.attach(9);
  pinMode(A0,INPUT); // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.write(0);
  //delay(5000);
  digitalWrite(motor[0],HIGH);
  analogWrite(motor[1],top);
  }

void loop() {
 int a=analogRead(A0);
 //delay(15);
 
   //Serial.println(a);
 
   Serial.println(count);

   if(a<=threshold && flag==0 )
 {
  count++;
  flag=1;
 }
 else if(a>=threshold && flag==1)
 {
  //Serial.println(" ");
  flag=0;
 }
 if(count>=10)
  {
    //delay(100);
    Serial.println("aaa");
    myservo.write(pos);
    //delay(100);
   flag3=1;
    count=0;
    analogWrite(motor[1],x);
  }
    if (count>=3 && flag3==1)
    {
     while(a>=threshold)
     { 
    a=analogRead(A0);
      analogWrite(motor[1],0);
      Serial.println("first");
     }
     x--;
     count2++;
    
     while(1)
    {
      a=analogRead(A0);
      if(a>=threshold && (count2)%2 != 0 && flag6==0)
      {
        digitalWrite(motor[0],LOW);
        analogWrite(motor[1],x);
        flag4=1;
        flag6=1;
        
      }
      else if(a<= threshold && flag4==1)  
      {
      analogWrite(motor[1],0);
      x--;
      count2++;
      flag5=1;
      flag6=0;
      flag4=0;
      }
      
      else if (a>=threshold && (count2)%2 == 0 && flag5==1)
      {
        digitalWrite(motor[0],HIGH);
        analogWrite(motor[1],x);
        
        flag5=0;
        flag4=1;
      }
     }
    }
    }
    
    
    
   
      
  
  
  

