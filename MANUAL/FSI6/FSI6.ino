/*
  >^/M1 (FL)       \^< M2 (FR)
   ----------------
  |                |
  |                |
  |                |
  |                |
  |                |
   ----------------
  <^\M4 (BL)       /^> M3 (BR)
  left - ACW <
  right - CW >
*/

int pins[] = {A3, A0, A1, A2};
int temp_pwm[] = {100, 100, 100, 100};
int x1, x2, y1, y2, p1, p2, p3, p4, s, vec;
int m11 = 9; //FL
int m12 = A5;
int m21 = 6; //FR
int m22 = 7;
int m31 = 5; //BL
int m32 = 4;
int m41 = 10; //BR
int m42 = A4;
int m51 = 3;
int m52 = 2;
int pwm = 100;
int s1 = 0;
int s2 = 0;
int s3 = 0;
int s4 = 0;
int c1 = 13, c2 = 12, c3 = 11, c4 = 8;
int count = 0;
const int sizee = 300;
//boolean vals[sizee];
boolean preVal = LOW;
int KP = 3;
int prev[4];
boolean done[4] = {false, false, false, false};
int v1 = 0, v2 = 0, v3 = 0, v4 = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(m11, OUTPUT);
  pinMode(m21, OUTPUT);
  pinMode(m31, OUTPUT);
  pinMode(m41, OUTPUT);
  pinMode(m51, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(m22, OUTPUT);
  pinMode(m32, OUTPUT);
  pinMode(m42, OUTPUT);
  pinMode(m52, OUTPUT);
  pinMode(c1, INPUT);
  pinMode(c2, INPUT);
  pinMode(c3, INPUT);
  pinMode(c4, INPUT);
  analogWrite(m11, 0);
  analogWrite(m21, 0);
  analogWrite(m31, 0);
  analogWrite(m41, 0);
  analogWrite(m51, 0);
  pinMode(pins[0], INPUT);
  pinMode(pins[1], INPUT);
  pinMode(pins[2], INPUT);
  pinMode(pins[3], INPUT);

//  digitalWrite(m12, HIGH);
//  digitalWrite(m22, HIGH);
//  digitalWrite(m32, HIGH);
//  digitalWrite(m42, HIGH);
//
//  delay(1000);
//  digitalWrite(m11, 100);
//  digitalWrite(m21, 100);
//  digitalWrite(m31, 100);
//  digitalWrite(m41, 100);
//  delay(1000);
//  digitalWrite(m11, 0);
//  digitalWrite(m21, 0);
//  digitalWrite(m31, 0);
//  digitalWrite(m41, 0);
//  delay(1000);
//  digitalWrite(m11, 100);
//  digitalWrite(m21, 100);
//  digitalWrite(m31, 100);
//  digitalWrite(m41, 100);
//  delay(1000);
//  while (!done[0] || !done[1] || !done[2] || !done[3])
//  {
//    for (int i = 0; i < 4; i++)
//    {
//      count = 0;
//      preVal = LOW;
//      for (int j = 0; j < sizee; j++)
//      {
//        vals[j] = digitalRead(pins[i]);
//      }
//      for (int j = 0; j < sizee; j++)
//      {
//        if (preVal == LOW && vals[j] == HIGH)
//          count++;
//        preVal = vals[j];
//      }
//
//      prev[i] = temp_pwm[i] - pwm;
//
//      int factor = (count - 20) / KP ;
//      temp_pwm[i] = pwm - factor + prev[i];
//      if (factor == 0)
//      {
//        done[i] = true;
//      }
//      else
//      {
//        done[i] = false;
//      }
//      //      Serial.print(factor);
//      //      Serial.print("-");
//      //      Serial.print(count);
//      //      Serial.print("+");
//      //      Serial.print(prev[i]);
//      //      Serial.print("=");
//      //      Serial.print(temp_pwm[i]);
//      //      Serial.print("|\t");
//      if (temp_pwm[i] > 255)
//        temp_pwm[i] = 255;
//    }
//    //    Serial.println(" ");
//
//    analogWrite(m11, temp_pwm[0]);
//    analogWrite(m21, temp_pwm[1]);
//    analogWrite(m31, temp_pwm[2]);
//    analogWrite(m41, temp_pwm[3]);
//
//    //  Serial.println("------------");
//  }
//  s1 = temp_pwm[0];
//  s2 = temp_pwm[1];
//  s3 = temp_pwm[2];
//  s4 = temp_pwm[3];
//  analogWrite(m11, 0);
//  analogWrite(m21, 0);
//  analogWrite(m31, 0);
//  analogWrite(m41, 0);

  //  Serial.print(s1);
  //  Serial.print(",");
  //  Serial.print(s2);
  //  Serial.print(",");
  //  Serial.print(s3);
  //  Serial.print(",");
  //  Serial.print(s4);
  //  Serial.print(",");
  //  Serial.println();
}

void loop()
{
  v1 = pulseIn(c1, HIGH);
  v2 = pulseIn(c2, HIGH);
  v3 = pulseIn(c3, HIGH);
  v4 = pulseIn(c4, HIGH);
  if (!v1 == 0 && !v2 == 0 && !v3 == 0 && !v4 == 0)
  {
    int l = v4;
    if (l > 1600 || l < 1400)
    {
      if (l > 1800)
      {
        Serial.println("DOWN");
        digitalWrite(m51, 255);
        digitalWrite(m52, HIGH);
      }
      if (l < 1200)
      {
        Serial.println("UP");
        digitalWrite(m51, 255);
        digitalWrite(m52, LOW);
      }
    }
    else
    {
      digitalWrite(m51, 0);
    }
    //Taking Analog input from joystick
    x1 =  map(v1, 1000, 2000, -122, 123);
    y1 =  map(v2, 1000, 2000, -122, 123);
    x2 =  map(v3, 1000, 2000, -122, 123);
    //    Serial.println(x1);
    //    Serial.println(y1);
    //    Serial.println(x2);
    //    Serial.println(l);
    //Projections on motor lines
    s = sqrt(2);
    if (x1 > -8 && x1 < 8)
      x1 = 0;
    if (y1 > -8 && y1 < 8)
      y1 = 0;

    p1 = -x1 - y1 / s;
    p2 = x1 - y1 / s;
    p3 = -x1 - y1 / s;
    p4 = x1 - y1 / s;
    //Printing all values
    //Serial.println(x1);
    //Serial.println(y1);
    //Serial.println(x2);
    //Serial.println(p1);
    //Serial.println(p2);
    //Serial.println(p3);
    //Serial.println(p4);
    if ( x2 < 8 && x2 > -8) {
      if (p1 > 0) {
        //Serial.println("I");
        p1 = map(p1, 0, 173, 0, s1);
        analogWrite(m11, p1);
        digitalWrite(m12, LOW);
        Serial.println("M1 forward");
      }
      else {
        //Serial.println("II");
        p1 = map(p1, -173, 0, s1, 0);
        analogWrite(m11, p1);
        digitalWrite(m12, HIGH);
        Serial.println("M1 backward");
      }
      if (p2 > 0) {
        //Serial.println("III");
        p2 = map(p2, 0, 173, 0, s2);
        analogWrite(m21, p2);
        digitalWrite(m22, LOW);
        Serial.println("M2 forward");
      }
      else {
        //Serial.println("IV");
        p2 = map(p2, -173, 0, s2, 0);
        analogWrite(m21, p2);
        digitalWrite(m22, HIGH);
        Serial.println("M2 backward");
      }
      if (p3 > 0) {
        //Serial.println("V");
        p3 = map(p3, 0, 173, 0, s3);
        analogWrite(m31, p3);
        digitalWrite(m32, LOW);
        Serial.println("M3 forward");
      }
      else {
        //Serial.println("VI");
        p3 = map(p3, -173, 0, s3, 0);
        analogWrite(m31, p3);
        digitalWrite(m32, HIGH);
        Serial.println("M3 backward");
      }
      if (p4 > 0) {
        //Serial.println("VII");
        p4 = map(p4, 0, 173, 0, s4);
        analogWrite(m41, p4);
        digitalWrite(m42, LOW);
        Serial.println("M4 forward");
      }
      else {
        //Serial.println("VIII");
        p4 = map(p4, -173, 0, s4, 0);
        analogWrite(m41, p4);
        digitalWrite(m42, HIGH);
        Serial.println("M4 backward");
      }
    }

    else
    {
      if (x2 > 0)
      {
        vec = map(x2, 0, 123, 0, 150);
        analogWrite(m11, vec);
        analogWrite(m21, vec);
        analogWrite(m31, vec);
        analogWrite(m41, vec);
        digitalWrite(m12, HIGH);
        digitalWrite(m22, LOW);
        digitalWrite(m32, LOW);
        digitalWrite(m42, HIGH);
        Serial.println("Turn Right");
      }
      else
      {
        vec = map(x2, -122, 0, 150, 0);
        analogWrite(m11, vec);
        analogWrite(m21, vec);
        analogWrite(m31, vec);
        analogWrite(m41, vec);
        digitalWrite(m12, LOW);
        digitalWrite(m22, HIGH);
        digitalWrite(m32, HIGH);
        digitalWrite(m42, LOW);
        Serial.println("Turn Left");
      }
    }
    Serial.println();
  }
}
