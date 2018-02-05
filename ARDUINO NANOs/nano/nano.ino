/*
 Writes to :-
 Up-Down motor
 Down Servo

 Reads from :-
 Up-Down switches
 Laser Receiver
 Up ultrasonic sensor
 Down ultrasonic sensor

 Talks with :-
 Rasberry PI
 RF Module
*/

// libraries
#include <NewPing.h>
#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// constants
const byte address[6] = "00001";
boolean received = true,downValue=false;  // down-going value here true=HIGH false=LOW
Servo myservo; 
#define MAX_DISTANCE 200               // Maximum distance (in cm) to ping.
#define SONAR_NUM 2                    // Number of sensors.
#define PINGDELAY 30

// pins
int dswitch=A5,tswitch=A7;             // up-down switch
int dir= 4,pwm= 3;                     // up-down motor
int laser = A6;                        // Receiver input
int servo=6;                           // Servo pin
RF24 radio(10,9);                      // CE, CSN
NewPing sonar[SONAR_NUM] = {           // Sensor object array.
  NewPing(2, 5, MAX_DISTANCE),         // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing(8, 7, MAX_DISTANCE), 
};

// variables
int s1=190,s2=70,s3=7,s4=140,s5=90,sp=50,acc=0;     // Servo variables
int count=0,tCount=10,dl=270;          // Count and releasing delay
int d0=15,d1=15;                       // Ultrasonic distances
int upSpeed=220,downSpeed=120;         // motor speed
boolean state = false;

void setup()
{
// define pins
  pinMode(dir,OUTPUT);
  pinMode(pwm,OUTPUT);
  pinMode(dswitch,INPUT_PULLUP);
  pinMode(tswitch,INPUT_PULLUP);
// Initialize
  Serial.begin(9600);
  Serial.println();
  radio.begin();  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  myservo.attach(servo);
  myservo.write(s2);

// initial calls
//  openServo();
}

void openServo()
{
  Serial.println("Open");
  const char text = 'o';
  radio.write(&text, sizeof(text));
}

void closeServo()
{
  Serial.println("Clos");
  const char text = 'g';
  radio.write(&text, sizeof(text));  
}

boolean rackPick()
{
  Serial.println("Rack");

// go down
  digitalWrite(dir,downValue);
  analogWrite(pwm,downSpeed);
  while(!downSwitch());
  analogWrite(pwm,0);

// middle to rack
  int pos=s2;
  int a=1;
  myservo.write(s1);
  delay(1000);

// rack to middle
  a=1;
  for(pos=(s1);pos>s4;)
  {
    myservo.write(pos);
    delay(sp);
    pos-=a;
    a+=acc;
  }
  a=2;
  for(pos=(s4);pos>s2;)
  {
    myservo.write(pos);
    delay(sp);
    pos-=a;
    a+=acc;
  }
  delay(1000);

// check ball
  for(int i=0; i<100; i++)
  {
    int d = sonar[0].ping_cm();
   Serial.print("d0 : ");
   Serial.println(d);
    delay(PINGDELAY);
    if(d<d0 && d!=0)
      return true;
  }
  return false;
}

boolean armLoad()
{
  Serial.println("Load");

// go up
  digitalWrite(dir,!downValue);
  analogWrite(pwm,upSpeed);
  while(!upSwitch());
  openServo();

// middle to arm
  int pos=s2;
  int a=2;
  for(pos=s2;pos>(s3);)
  {
    myservo.write(pos);
    delay(sp);
    pos-=a;
    a+=acc;
  }

// grab
  delay(1000);
  closeServo();
  delay(1000);

// arm to middle
  analogWrite(pwm,0);
  myservo.write(s5);
  delay(1000);
  return true;
  
// check ball
/*  for(int i=0; i<100; i++)
  {
    int d = sonar[1].ping_cm();
  // Serial.print("d1 : ");
  // Serial.println(d);
    delay(PINGDELAY);
    if(d<d1 && d!=0)
      return true;
  }
  return false;
*/
}

boolean countLoops()
{
  Serial.println("Loop");
  count=0;
  received = true;
  while(1)
  {
    int r = analogRead(laser);
//    Serial.println(r);
    if(!received && r<250)
    {
      received=true;
    }
    else if(received && r>550)
    {
      received=false;
      count++;
//      Serial.print("count : ");
      Serial.println(count);
    }
    
    if(count==tCount)
    {
      delay(dl);
      openServo();
      return true;
    }
  }
}

boolean upSwitch()
{
  int r = analogRead(tswitch);
  if(r>900)
    return false;
  else if(r<100)
    return true;
}

boolean downSwitch()
{
  int r = analogRead(dswitch);
  if(r>900)
    return false;
  else if(r<250)
    return true;
}

boolean test()
{
  openServo();
  digitalWrite(dir,downValue);
  analogWrite(pwm,downSpeed);
  while(!downSwitch());
  analogWrite(pwm,0);

  myservo.write(s1);
  delay(1000);
  
  myservo.write(s2);
  delay(1000);

  digitalWrite(dir,!downValue);
  analogWrite(pwm,upSpeed);
  while(!upSwitch());
  analogWrite(pwm,0);
  
  myservo.write(s3);
  delay(1000);
  
  myservo.write(s2);
  delay(1000);

  for(int i=0; i<5; i++)
  {
    Serial.print("Receiver : ");
    Serial.println(analogRead(laser));
    Serial.print("Up Switch : ");
    Serial.println(analogRead(tswitch));
    Serial.print("Down Switch : ");
    Serial.println(analogRead(dswitch));
    Serial.print("Up Sonic : ");
    Serial.println(sonar[0].ping_cm());
    delay(PINGDELAY);
    Serial.print("Down Sonic : ");
    Serial.println(sonar[1].ping_cm());
    Serial.println();
    delay(PINGDELAY);
  }
  delay(10000);
  return true;
}

void loop()
{
  if(Serial.available()>0)
  {
    char input = Serial.read();
    state = false;
    Serial.println("Okay");
    
    if(input=='s')
      state = rackPick();
    else if(input=='c')
      state = armLoad();
    else if(input=='t')
      state = countLoops();
    else if(input=='q')
      state = test();
    Serial.println(state ? "TRUE" : "FALS");
  }

//  if(!state)
//      state = rackPick();
//  state = armLoad();
//  state = countLoops();
//  state = test();
//  Serial.println(state ? "TRUE" : "FALS");
}
