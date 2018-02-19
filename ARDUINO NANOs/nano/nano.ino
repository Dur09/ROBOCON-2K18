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
boolean received = true, downValue = true; // down-going value here true=HIGH false=LOW
Servo myservo;
Servo smallServo;
#define MAX_DISTANCE 200               // Maximum distance (in cm) to ping.
#define SONAR_NUM 2                    // Number of sensors.
#define PINGDELAY 30

// pins
int dswitch = A5, tswitch = A7;        // up-down switch
int dir = 4, pwm = 3;                  // up-down motor
int laser1 = A6, laser2 = A4, laser3 = A2, laser4 = A1;                     // Receiver input
int servo = 6, servo2 = 5;                      // Servo pins
RF24 radio(10, 9);                     // CE, CSN
NewPing sonar[SONAR_NUM] = {           // Sensor object array.
  NewPing(2, 8, MAX_DISTANCE),         // Each sensor's trigger pin, echo pin, and max distance to ping.
  NewPing(5, 7, MAX_DISTANCE),
};

// variables
const int s1 = 190, s2 = 55, s3 = -2, s4 = 160, s5 = 90, sms1 = 85, sms2 = 170, sp = 50, acc = 0; // Servo variables
int count = 0, tCount = 10, dl = 270;  // Count and releasing delay
int d0 = 15, d1 = 15;                  // Ultrasonic distances
int upSpeed = 255, downSpeed = 140;    // motor speed
boolean state = false;

void setup()
{
  // define pins
  pinMode(dir, OUTPUT);
  pinMode(pwm, OUTPUT);
  pinMode(dswitch, INPUT_PULLUP);
  pinMode(tswitch, INPUT_PULLUP);
  // Initialize
  Serial.begin(9600);
  Serial.println();
  radio.begin();  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  myservo.attach(servo);
  smallServo.attach(servo2);
  //  myservo.write(-2);
  //  delay(100000);
  //  initial calls
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

void openSmallServo()
{
  smallServo.write(sms1);
}

void closeSmallServo()
{
  smallServo.write(sms2);
}

boolean rackPick()
{
  Serial.println("Rack");

  openSmallServo();
  // go down
  digitalWrite(dir, downValue);
  analogWrite(pwm, downSpeed);
  while (!downSwitch());
  analogWrite(pwm, 0);

  // middle to rack
  int pos = s2;
  int a = 1;
  myservo.write(s1);
  delay(500);

  // rack to middle
  a = 1;
  for (pos = (s1); pos > s4;)
  {
    myservo.write(pos);
    delay(sp);
    pos -= a;
    a += acc;
  }
  closeSmallServo();
  a = 2;
  for (pos = (s4); pos > s2;)
  {
    myservo.write(pos);
    delay(sp);
    pos -= a;
    a += acc;
  }
  delay(500);

  // check ball
  for (int i = 0; i < 100; i++)
  {
    int d = sonar[0].ping_cm();
    Serial.print("d0 : ");
    Serial.println(d);
    delay(PINGDELAY);
    if (d < d0 && d != 0)
      return true;
  }
  return false;
}

boolean armLoad()
{
  Serial.println("Load");

  // go up
  digitalWrite(dir, !downValue);
  analogWrite(pwm, upSpeed);
  while (!upSwitch());
  analogWrite(pwm, 0);
  openServo();

  // middle to arm
  int pos = s2;
  int a = 2;
  for (pos = s2; pos >= (s3);)
  {
    myservo.write(pos);
    delay(sp);
    pos -= a;
    a += acc;
  }
  myservo.write(s3);
  // grab
  delay(1000);
  closeServo();
  delay(500);
  openSmallServo();
  delay(500);
  // arm to middle
  analogWrite(pwm, 0);
  myservo.write(s5);
  delay(1000);
  return true;
}

boolean ballCheck()
{
  // check ball
  for (int i = 0; i < 500; i++)
  {
    int d = sonar[1].ping_cm();
    Serial.print("d1 : ");
    Serial.println(d);
    delay(PINGDELAY);
    if (d < d1 && d != 0)
      return true;
  }
  return false;
}

boolean countLoops(int t)
{
  Serial.println("Loop");
  count = 0;
  received = true;
  while (1)
  {
    int r;
    if (t == 1)
    {
      r = analogRead(laser3);
    }
    else if (t == 2)
    {
      r = analogRead(laser1);
    }
    else if (t == 3)
    {
      r = analogRead(laser2);
    }
    //Serial.println(r);
    if (!received && r < 100)
    {
      received = true;
    }
    else if (received && r > 500)
    {
      received = false;
      count++;
      //      Serial.print("count : ");
      Serial.println(count);
    }

    if (count == tCount)
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
  if (r > 900)
    return false;
  else if (r < 100)
    return true;
  else
    return false;
}

boolean downSwitch()
{
  int r = analogRead(dswitch);
  if (r > 900)
    return false;
  else if (r < 250)
    return true;
  else
    return false;
}

boolean test()
{
  openServo();
  digitalWrite(dir, downValue);
  analogWrite(pwm, downSpeed);
  while (!downSwitch());
  analogWrite(pwm, 0);

  myservo.write(s1);
  delay(1000);

  myservo.write(s2);
  delay(1000);

  digitalWrite(dir, !downValue);
  analogWrite(pwm, upSpeed);
  while (!upSwitch());
  analogWrite(pwm, 0);

  myservo.write(s3);
  delay(1000);

  myservo.write(s2);
  delay(1000);

  for (int i = 0; i < 5; i++)
  {
    Serial.print("Receiver : ");
    Serial.println(analogRead(laser3));
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
  if (Serial.available() > 0)
  {
    char input = Serial.read();
    state = false;
    Serial.println("Okay");

    if (input == 's')
      state = rackPick();
    else if (input == 'c')
      state = armLoad();
    else if (input == 't')
      state = countLoops(1);
    else if (input == 'u')
      state = countLoops(2);
    else if (input == 'v')
      state = countLoops(3);
    else if (input == 'q')
      state = test();
    Serial.println(state ? "TRUE" : "FALS");
  }

  //  if(!state)
  //  state = ballCheck();
  //    state = rackPick();
  //    state = armLoad();
  //    state = countLoops(2);
  //  state = test();
  //  Serial.println(state ? "TRUE" : "FALS");
}
