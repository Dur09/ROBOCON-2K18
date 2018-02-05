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

int x1, x2, y1, y2, p1, p2, p3, p4, s, vec;
int m11 = 9; //FL
int m12 = 1;
int m21 = 5; //FR
int m22 = 4;
int m31 = 6; //BL
int m32 = 7;
int m41 = 10; //BR
int m42 = 0;
int m51 = 14;
int m52 = 3;
int s1 = 255;
int s2 = 255;
int s3 = 255;
int s4 = 255;
int c1=8,c2=11,c3=13,c4=12;

void setup() {

//  Serial.begin(115200);

  //Serial.print(F("\r\nPS3 Bluetooth Library Started"));
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
  digitalWrite(m52, LOW);
}

void loop() 
{
    int l = pulseIn(c4, HIGH);
    if (l > 1600 || l < 1400)
    {
      if(l > 1800)
      {
///        Serial.println("DOWN");
        digitalWrite(m51,HIGH);
        digitalWrite(m52,HIGH);
      }
      if(l < 1200)
      {
///        Serial.println("UP");
        digitalWrite(m51,HIGH);
        digitalWrite(m52,LOW);
      }
    }
    else
    {
        digitalWrite(m51,LOW);
    }
    //Taking Analog input from joystick
    x1 =  map(pulseIn(c1, HIGH), 1000, 2000, -122, 123);
    y1 =  map(pulseIn(c2, HIGH), 1000, 2000, -122, 123);
    x2 =  map(pulseIn(c3, HIGH), 1000, 2000, -122, 123);
//    Serial.println(x1);
//    Serial.println(y1);
//    Serial.println(x2);
//    Serial.println(l);
    //Projections on motor lines
    s = sqrt(2);
    if(x1 > -8 && x1 < 8)
      x1 = 0;
    if(y1 > -8 && y1 < 8)
      y1 = 0;
      
    p1 = -x1-y1/s;
    p2 = x1-y1/s;
    p3 = x1+y1/s;
    p4 = x1-y1/s;
    //Printing all values
    //Serial.println(x1);
    //Serial.println(y1);
    //Serial.println(x2);
    //Serial.println(p1);
    //Serial.println(p2);
    //Serial.println(p3);
    //Serial.println(p4); 
  if ( x2 < 5 && x2 > -5) {
    if (p1>0) {
      //Serial.println("I");
      p1 = map(p1, 0, 173, 0, s1);
      analogWrite(m11, p1);
      digitalWrite(m12, LOW);
///      Serial.println("M1 forward");
    }
    else {
      //Serial.println("II");
      p1 = map(p1, -173, 0, s1, 0);
      analogWrite(m11, p1);
      digitalWrite(m12, HIGH);
///   Serial.println("M1 backward");
    }
    if (p2>0) {
      //Serial.println("III");
      p2 = map(p2, 0, 173, 0, s2);
      analogWrite(m21, p2);
      digitalWrite(m22, LOW);
///      Serial.println("M2 forward");
    }
    else {
      //Serial.println("IV");
      p2 = map(p2, -173, 0, s2, 0);
      analogWrite(m21, p2);
      digitalWrite(m22, HIGH);
///      Serial.println("M2 backward");
    }
    if (p3>0) {
      //Serial.println("V");
      p3 = map(p3, 0, 173, 0, s3);
      analogWrite(m31, p3);
      digitalWrite(m32, LOW);
//      Serial.println("M3 forward");
    }
    else {
      //Serial.println("VI");
      p3 = map(p3, -173, 0, s3, 0);
      analogWrite(m31, p3);
      digitalWrite(m32, HIGH);
///      Serial.println("M3 backward");
    }
    if (p4>0) {
      //Serial.println("VII");
      p4 = map(p4, 0, 173, 0, s4);
      analogWrite(m41, p4);
      digitalWrite(m42, LOW);
///      Serial.println("M4 forward");
    }
    else {
      //Serial.println("VIII");
      p4 = map(p4, -173, 0, s4, 0);
      analogWrite(m41, p4);
      digitalWrite(m42, HIGH);
///      Serial.println("M4 backward");
    }
  }

  else 
  {
    if (x2>0) 
    {
      vec = map(x2, 0, 123, 0, 150);
      analogWrite(m11, vec);
      analogWrite(m21, vec);
      analogWrite(m31, vec);
      analogWrite(m41, vec);
      digitalWrite(m12, HIGH);
      digitalWrite(m22, LOW);
      digitalWrite(m32, HIGH);
      digitalWrite(m42, HIGH);   
///      Serial.println("Turn Right");
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
      digitalWrite(m32, LOW);
      digitalWrite(m42, LOW); 
///      Serial.println("Turn Left");
    }
  }
///  Serial.println();
  delay(100);
}
