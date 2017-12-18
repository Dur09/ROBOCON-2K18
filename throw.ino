#include <Servo.h>
Servo myservo;
int count=0;
int pos=60;
int flag=0;
int top =140;    
int motor[2]= {7,6};      //{dir,pwm}
void setup() {
  pinMode(motor[0],OUTPUT);
  pinMode(motor[1],OUTPUT);
  digitalWrite(motor[0],HIGH);  
  pinMode(4,OUTPUT);
  digitalWrite(4,HIGH);
  analogWrite(motor[1],0);
  myservo.attach(9);
  pinMode(A0,INPUT); // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.write(0);
  delay(5000);
  digitalWrite(motor[0],HIGH);
  analogWrite(motor[1],top);
  }

void loop() {
 int a=analogRead(A0);
 //delay(15);
   Serial.println(count);
  /* if(top!=255){
   for( top =120; top!=255;top ++)
      analogWrite(motor[1],top);
      delay(100);
   }*/
/* if(a<=400 && flag==0 )           //ldr
 {
  count++;
  flag=1;
 }
 else if(a>800 && flag==1)
 {
  Serial.println(" ");
  flag=0;
 }*/
 /* // 5v
  float volts = analogRead(A5)*0.0048828125;  // value from sensor * (5/1024)
  float a = 13*pow(volts, -1); // worked out from datasheet graph
  //delay(1000); // slow down serial port 
     Serial.println(a);
*/
   if(a>=250 && flag==0 )
 {
  count++;
  flag=1;
 }
 else if(a<=30 && flag==1)
 {
  //Serial.println(" ");
  flag=0;
 }
 if(count>=10)
  {
    delay(160);
    Serial.println("aaa");
    myservo.write(pos);
    delay(100);
    digitalWrite(motor[0],LOW);
    analogWrite(motor[1],0);
    
  }
  
  
}
