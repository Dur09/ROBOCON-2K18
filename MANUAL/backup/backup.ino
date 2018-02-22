void setup() {
//  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(3,INPUT);
  pinMode(5,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int r = pulseIn(3,HIGH);
//  Serial.println(r);
  if(r<1200)
    digitalWrite(5,LOW);
  else if(r>1800)
    digitalWrite(5,HIGH);
}
