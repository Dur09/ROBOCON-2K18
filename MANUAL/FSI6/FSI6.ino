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

// Wiring http://301o583r8shhildde3s0vcnh.wpengine.netdna-cdn.com/wp-content/uploads/2014/11/conn.png

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
// in "MPU6050_6Axis_MotionApps20.h"
// I'm now using the default value on line 305 to:  0x02,   0x16,   0x02,   0x00, 0x01                // D_0_22 inv_set_fifo_rate
// Correcting the PID code fixed my issues with the fifo buffer being too fast
#include "Wire.h"

MPU6050 mpu;

// These are my MPU6050 Offset numbers: for mpu.setXGyroOffset()
// supply your own gyro offsets here, scaled for min sensitivity use MPU6050_calibration.ino <<< download to calibrate your MPU6050 put the values the probram returns below
//                       XA      YA      ZA      XG      YG      ZG
int MPUOffsets[6] = {  -467, 643, 1854,  32,  -13, -7};


volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high


// ================================================================
// ===               INTERRUPT DETECTION ROUTINE                ===
// ================================================================

// ================================================================
// ===                      MPU DMP SETUP                       ===
// ================================================================
int FifoAlive = 0; // tests if the interrupt is triggering
int IsAlive = -20;     // counts interrupt start at -20 to get 20+ good values before assuming connected

// MPU control/status vars
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
float Yaw, Pitch, Roll; // in degrees



int bias = 0;
float factor = 2.0;
int x1, x2, y1, y2, p1, p2, p3, p4, s, vec;
int m11 = 9; //FL
int m12 = A2;
int m21 = 5; //FR
int m22 = 4;
int m31 = 6; //BL
int m32 = 7;
int m41 = 10; //BR
int m42 = A3;
int m51 = A0;
int m52 = A1;
int s1 = 200;
int s2 = 200;
int s3 = 200;
int s4 = 200;
int c1 = 8, c2 = 3, c3 = 12, c4 = 13;
int v1 = 0, v2 = 0, v3 = 0, v4 = 0;

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  i2cSetup();

  Serial.println(F("Alive"));
  MPU6050Connect();
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
}

void loop()
{
  calYaw();
  Serial.print("Yaw : ");
  Serial.println(Yaw);
  traverse();
}
void calYaw()
{
  if (mpuInterrupt )
  {
    GetDMP(); // Gets the MPU Data and canculates angles
  }
}
void traverse()
{
  v1 = pulseIn(c1, HIGH);
  v2 = pulseIn(c2, HIGH);
  v3 = pulseIn(c3, HIGH);
  v4 = pulseIn(c4, HIGH);
  Serial.println(v1);
  Serial.println(v2);
  Serial.println(v3);
  Serial.println(v4);
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
    x1 =  map(v1, 1000, 2000, -122, 123);
    y1 =  map(v2, 1000, 2000, -122, 123);
    x2 =  map(v3, 1000, 2000, -122, 123);
    //    Serial.println(x1);
    //    Serial.println(y1);
    //    Serial.println(x2);
    //    Serial.println(l);

    s = sqrt(2);
    if (x1 > -8 && x1 < 8)
      x1 = 0;
    if (y1 > -8 && y1 < 8)
      y1 = 0;

    bias = int(Yaw * factor);
    p1 = -x1 - y1 / s + bias;
    p2 =  x1 - y1 / s - bias;
    p3 = -x1 - y1 / s - bias;
    p4 =  x1 - y1 / s + bias;

    if ( x2 < 8 && x2 > -8) {
      if (p1 > 0) {
        p1 = map(p1, 0, 173, 0, s1);
        analogWrite(m11, p1);
        digitalWrite(m12, LOW);
        Serial.println("M1 forward");
      }
      else {
        p1 = map(p1, -173, 0, s1, 0);
        analogWrite(m11, p1);
        digitalWrite(m12, HIGH);
        Serial.println("M1 backward");
      }
      if (p2 > 0) {
        p2 = map(p2, 0, 173, 0, s2);
        analogWrite(m21, p2);
        digitalWrite(m22, LOW);
        Serial.println("M2 forward");
      }
      else {
        p2 = map(p2, -173, 0, s2, 0);
        analogWrite(m21, p2);
        digitalWrite(m22, HIGH);
        Serial.println("M2 backward");
      }
      if (p3 > 0) {
        p3 = map(p3, 0, 173, 0, s3);
        analogWrite(m31, p3);
        digitalWrite(m32, LOW);
        Serial.println("M3 forward");
      }
      else {
        p3 = map(p3, -173, 0, s3, 0);
        analogWrite(m31, p3);
        digitalWrite(m32, HIGH);
        Serial.println("M3 backward");
      }
      if (p4 > 0) {
        p4 = map(p4, 0, 173, 0, s4);
        analogWrite(m41, p4);
        digitalWrite(m42, LOW);
        Serial.println("M4 forward");
      }
      else {
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
  }
  Serial.println("----");
}
void GetDMP() { // Best version I have made so far
  // Serial.println(F("FIFO interrupt at:"));
  // Serial.println(micros());
  mpuInterrupt = false;
  FifoAlive = 1;
  fifoCount = mpu.getFIFOCount();
  /*
    fifoCount is a 16-bit unsigned value. Indicates the number of bytes stored in the FIFO buffer.
    This number is in turn the number of bytes that can be read from the FIFO buffer and it is
    directly proportional to the number of samples available given the set of sensor data bound
    to be stored in the FIFO
  */

  // PacketSize = 42; refference in MPU6050_6Axis_MotionApps20.h Line 527
  // FIFO Buffer Size = 1024;
  uint16_t MaxPackets = 20;// 20*42=840 leaving us with  2 Packets (out of a total of 24 packets) left before we overflow.
  // If we overflow the entire FIFO buffer will be corrupt and we must discard it!

  // At this point in the code FIFO Packets should be at 1 99% of the time if not we need to look to see where we are skipping samples.
  if ((fifoCount % packetSize) || (fifoCount > (packetSize * MaxPackets)) || (fifoCount < packetSize)) { // we have failed Reset and wait till next time!
    Serial.println(F("Reset FIFO"));
    if (fifoCount % packetSize) Serial.print(F("\t Packet corruption")); // fifoCount / packetSize returns a remainder... Not good! This should never happen if all is well.
    Serial.print(F("\tfifoCount ")); Serial.print(fifoCount);
    Serial.print(F("\tpacketSize ")); Serial.print(packetSize);

    mpuIntStatus = mpu.getIntStatus(); // reads MPU6050_RA_INT_STATUS       0x3A
    Serial.print(F("\tMPU Int Status ")); Serial.print(mpuIntStatus , BIN);
    // MPU6050_RA_INT_STATUS       0x3A
    //
    // Bit7, Bit6, Bit5, Bit4          , Bit3       , Bit2, Bit1, Bit0
    // ----, ----, ----, FIFO_OFLOW_INT, I2C_MST_INT, ----, ----, DATA_RDY_INT

    /*
      Bit4 FIFO_OFLOW_INT: This bit automatically sets to 1 when a FIFO buffer overflow interrupt has been generated.
      Bit3 I2C_MST_INT: This bit automatically sets to 1 when an I2C Master interrupt has been generated. For a list of I2C Master interrupts, please refer to Register 54.
      Bit1 DATA_RDY_INT This bit automatically sets to 1 when a Data Ready interrupt is generated.
    */
    if (mpuIntStatus & B10000) { //FIFO_OFLOW_INT
      Serial.print(F("\tFIFO buffer overflow interrupt "));
    }
    if (mpuIntStatus & B1000) { //I2C_MST_INT
      Serial.print(F("\tSlave I2c Device Status Int "));
    }
    if (mpuIntStatus & B1) { //DATA_RDY_INT
      Serial.print(F("\tData Ready interrupt "));
    }
    Serial.println();
    //I2C_MST_STATUS
    //PASS_THROUGH, I2C_SLV4_DONE,I2C_LOST_ARB,I2C_SLV4_NACK,I2C_SLV3_NACK,I2C_SLV2_NACK,I2C_SLV1_NACK,I2C_SLV0_NACK,
    mpu.resetFIFO();// clear the buffer and start over
    mpu.getIntStatus(); // make sure status is cleared we will read it again.
  } else {
    while (fifoCount  >= packetSize) { // Get the packets until we have the latest!
      if (fifoCount < packetSize) break; // Something is left over and we don't want it!!!
      mpu.getFIFOBytes(fifoBuffer, packetSize); // lets do the magic and get the data
      fifoCount -= packetSize;
    }
    MPUMath(); // <<<<<<<<<<<<<<<<<<<<<<<<<<<< On success MPUMath() <<<<<<<<<<<<<<<<<<<
    if (fifoCount > 0) mpu.resetFIFO(); // clean up any leftovers Should never happen! but lets start fresh if we need to. this should never happen.
  }
}


void MPUMath() {
  mpu.dmpGetQuaternion(&q, fifoBuffer);
  mpu.dmpGetGravity(&gravity, &q);
  mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
  Yaw = (ypr[0] * 180 / M_PI);
  // Pitch = (ypr[1] * 180 / M_PI);
  //Roll = (ypr[2] * 180 / M_PI);
}
void dmpDataReady() {
  mpuInterrupt = true;
}
void MPU6050Connect() {
  static int MPUInitCntr = 0;
  // initialize device
  mpu.initialize(); // same
  // load and configure the DMP
  devStatus = mpu.dmpInitialize();// same

  if (devStatus != 0) {
    // ERROR!
    // 1 = initial memory load failed
    // 2 = DMP configuration updates failed
    // (if it's going to break, usually the code will be 1)

    char * StatStr[5] { "No Error", "initial memory load failed", "DMP configuration updates failed", "3", "4"};

    MPUInitCntr++;

    Serial.print(F("MPU connection Try #"));
    Serial.println(MPUInitCntr);
    Serial.print(F("DMP Initialization failed (code "));
    Serial.print(StatStr[devStatus]);
    Serial.println(F(")"));

    if (MPUInitCntr >= 10) return; //only try 10 times
    delay(1000);
    MPU6050Connect(); // Lets try again
    return;
  }

  // mpu.setXAccelOffset(MPUOffsets[0]);
  // mpu.setYAccelOffset(MPUOffsets[1]);
  mpu.setZAccelOffset(MPUOffsets[2]);
  // mpu.setXGyroOffset(MPUOffsets[3]);
  //mpu.setYGyroOffset(MPUOffsets[4]);
  mpu.setZGyroOffset(MPUOffsets[5]);

  Serial.println(F("Enabling DMP..."));
  mpu.setDMPEnabled(true);
  // enable Arduino interrupt detection

  Serial.println(F("Enabling interrupt detection (Arduino external interrupt pin 2 on the Uno)..."));
  attachInterrupt(0, dmpDataReady, FALLING); //pin 2 on the Uno

  mpuIntStatus = mpu.getIntStatus(); // Same
  // get expected DMP packet size for later comparison
  packetSize = mpu.dmpGetFIFOPacketSize();
  delay(1000); // Let it Stabalize
  mpu.resetFIFO(); // Clear fifo buffer
  mpu.getIntStatus();
  mpuInterrupt = false; // wait for next interrupt

}
// ================================================================
// ===                      i2c SETUP Items                     ===
// ================================================================
void i2cSetup() {
  // join I2C bus (I2Cdev library doesn't do this automatically)
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
  TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif
}
