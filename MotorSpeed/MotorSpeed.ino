int a=-1,b=-1,flag=0,rev=0,diff=0;
long start=0,flip=0;
int ba=0,bb=0;
void setup() 
{
  // put your setup code here, to run once:
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  Serial.begin(9600);
  start = micros();
}

void loop() 
{
// put your main code here, to run repeatedly:
  a=analogRead(A0);
  b=analogRead(A1);
  diff=abs(a-b);
  if(diff>900)flip++;
//  if(a>900)ba=1;
//  else if(a<100)ba=0;
//  else ba=-1;
//  if(b>900)bb=1;
//  else if(b<100)bb=0;
//  else bb=-1;
//  Serial.print("a : ");
//  Serial.println(a);
//  Serial.print(",b : ");
//  Serial.println(b);
//  if(a>900)
//  {
//    if(b>900 && flag==3)
//    {
//      flag=0;
//      flip++;
//    }
//    else if(b<100 && flag==2)
//    {
//      flag=3;
//    }
//  }
//  else if(a<100)
//  {
//    if(b>900 && flag==0)
//    {
//      flag=1;
//    }
//    else if(b<100 && flag==1)
//    {
//      flag=2;
//    }
//  }
//  if(flip>=456)
//  {
//    rev++;
//    flip=0;
//  }
//  Serial.print("a : ");
//  Serial.print(ba);
//  Serial.print(",b : ");
//  Serial.print(bb);
//  Serial.print(",flag : ");
//  Serial.println(flag);
//  Serial.println(abs(a-b));
  if(micros()>=start+1000000)
  {
//    Serial.println(rev*60);
    Serial.println(flip*60*1.0/456*1.0);
    rev=0;
    flip=0;
    flag=0;
    start=micros();
  }
}
