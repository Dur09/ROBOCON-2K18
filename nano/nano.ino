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
boolean received = true;
Servo myservo; 
#define MAX_DISTANCE 200               // Maximum distance (in cm) to ping.
#define SONAR_NUM 2                    // Number of sensors.
#define PINGDELAY 30

// pins
int dswitch=4,tswitch=5 ;              //up-down switch
int dir= 31,pwm= 10;                   //up-down motor
RF24 radio(9,10);                      // CE, CSN
NewPing sonar[SONAR_NUM] = {           // Sensor object array.
  NewPing(4, 5, MAX_DISTANCE),         // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing(6, 7, MAX_DISTANCE), 
};

// variables
int s1=180,s2=90,s3=7,sp=25,acc=2;     // Servo variables
int count=0,tCount=10,dl=270;          // Count and releasing delay
int d0=15,d1=15;                       // Ultrasonic distances

void setup()
{
// define pins
  pinMode(dir,OUTPUT);
  pinMode(pwm,OUTPUT);
  pinMode(dswitch,INPUT_PULLUP);
  pinMode(tswitch,INPUT_PULLUP);
  pinMode(A15,INPUT);
 
// Initialize
  Serial.begin(115200);

  radio.begin();  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  myservo.attach(2);
  myservo.write(s2);

// initial calls
  openServo();
}

void openServo()
{
  Serial.println("openServo");
  const char text = 'o';
  radio.write(&text, sizeof(text));
}

void closeServo()
{
  Serial.println("closeServo");
  const char text = 'g';
  radio.write(&text, sizeof(text));  
}

boolean rackPick()
{
  Serial.println("rackpick");

// go down
  digitalWrite(dir,HIGH);
  analogWrite(pwm,255);
  while(digitalRead(tswitch)==HIGH);
  analogWrite(pwm,0);

// middle to rack
  int pos=s2;
  int a=0;
  for(pos=(s2);pos<(s2+45);)
  {
    myservo.write(pos);
    delay(sp);
    pos+=a;
    a+=acc;
  }
  for(pos=(s2+45);pos<s1;)
  {
    myservo.write(pos);
    delay(sp);
    pos+=a;
    a-=acc;
  }
  delay(1000);

// rack to middle
  a=0;
  for(pos=(s1);pos>(s1-45);)
  {
    myservo.write(pos);
    delay(sp);
    pos-=a;
    a+=acc;
  }
  for(pos=(s1-45);pos>s2;)
  {
    myservo.write(pos);
    delay(sp);
    pos-=a;
    a-=acc;
  }
  delay(1000);

// check ball
  for(int i=0; i<100; i++)
  {
    int d = sonar[0].ping_cm();
  // Serial.print("d0 : ");
  // Serial.println(d);
    delay(PINGDELAY);
    if(d<d0)
      return true;
  }
  return false;
}

boolean armLoad()
{
  Serial.println("armload");

// go up
  digitalWrite(dir,LOW);
  analogWrite(pwm,255);
  while(digitalRead(tswitch)==HIGH);
  analogWrite(pwm,0);
  openServo();

// middle to arm
  int pos=s2;
  int a=1;
  for(pos=s2;pos>(s2-45);)
  {
    myservo.write(pos);
    delay(sp);
    pos-=a;
    a+=acc;
  }
  for(pos=(s2-45);pos>s3;)
  {
    myservo.write(pos);
    delay(sp);
    pos-=a;
    a-=acc;
  }

// grab
  delay(1000);
  closeServo();
  delay(1000);

// arm to middle
  a=1;
  for(pos=(s3);pos<(s3+45);)
  {
    myservo.write(pos);
    delay(sp);
    pos+=a;
    a+=2;
  }
  for(pos=(s3+45);pos<s2;)
  {
    myservo.write(pos);
    delay(sp);
    pos+=a;
    a-=2;
  }
  delay(1000);

// check ball
  for(int i=0; i<100; i++)
  {
    int d = sonar[1].ping_cm();
  // Serial.print("d1 : ");
  // Serial.println(d);
    delay(PINGDELAY);
    if(d<d1)
      return true;
  }
  return false;
}

boolean countLoops()
{
  received = true;

  int r = analogRead(A0);
// Serial.println(r);
  if(!received && r<100)
  {
    received=true;
  }
  else if(received && r>700)
  {
    received=false;
    count++;
//    Serial.print("count : ");
//    Serial.println(count);
  }
  if(count==tCount)
  {
    delay(dl);
    openServo();
    return true;
  }
}

boolean test()
{
  digitalWrite(dir,LOW);
  analogWrite(pwm,255);
  while(digitalRead(dswitch)==HIGH);
  digitalWrite(dir,HIGH);
  analogWrite(pwm,255);
  while(digitalRead(tswitch)==HIGH);
  analogWrite(pwm,0);
  myservo.write(0);
  delay(1000);
  myservo.write(180);
  delay(1000);
  for(int i=0; i<10; i++)
  {
    Serial.print("Receiver : ");
    Serial.println(analogRead(A0));
    Serial.print("Up Sonic : ");
    Serial.println(sonar[0].ping_cm());
    delay(PINGDELAY);
    Serial.print("Down Sonic : ");
    Serial.println(sonar[1].ping_cm());
    Serial.println();
    delay(PINGDELAY);
  }
  return true;
}

void loop()
{
  if(Serial.available())
  {
    char input = Serial.read();
    char output;
    boolean state = false;
    if(input=='s')
      state = rackPick();
    else if(input=='c')
      state = armLoad();
    else if(input=='t')
      state = countLoops();
    else if(input=='q')
      state = test();
    output = state ? 'T' : 'F';
    Serial.print(output);
  }
}
