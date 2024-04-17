int Count=0;
double err1=0;
double err2=0;
// Including Libraries:
#include <Wire.h>
#include <MPU6050_light.h>

// IMU:
MPU6050 mpu(Wire);

// H-Bridge Pins
#define   PWR 5
#define   PWL 6
#define   IN1 7
#define   IN2 8
#define   IN3 9
#define   IN4 10

//encoders
#define ENR 2
#define ENL 3

void readEncoder_R();
void readEncoder_L();
void IMU();
unsigned long timer = 0;
float angle=0;
int pos_R;
int pos_L;

void setup() 
{
  Serial.begin(9600);

  pinMode(ENR,INPUT);
  attachInterrupt(digitalPinToInterrupt(ENR),readEncoder_R,RISING);

  pinMode(ENL,INPUT);
  attachInterrupt(digitalPinToInterrupt(ENL),readEncoder_L,RISING);

  pinMode(PWR,OUTPUT);
  pinMode(PWL,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);

  Wire.begin();
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
    
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");

  Straight();
  IMU();

}

void loop()
{
  //Serial.println(pos_L);
  IMU();
  if ((-err1 <angle) && (angle < err1)) //Error Margin
  {
    Straight();
    //Serial.println("Straight");
  }
  else if (angle > err2)  //correct right error
  {
    correction (100,150);
    //Serial.println("RIGHT");
  }
  else if (angle <-err2)  //correction error left
  {
    correction (150,100);
    //Serial.println("LEFT");
  }
  else if((pos_L>=1000))
  {
     //manover("S");
digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
    analogWrite(PWL,0);
    analogWrite(PWR,0);
     Serial.println("here");
  }
  
}
void readEncoder_R()
{
    pos_R++;
}

void readEncoder_L()
{
    pos_L++;
}

void IMU()
{

   mpu.update();

  if((millis()-timer)>10)
  { 
	  Serial.print("yaw : ");
    angle = double(mpu.getAngleZ());
  	Serial.println(angle);
	  timer = millis();  
   }
}
void Straight()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  analogWrite(PWR,100);
  analogWrite(PWL,100);
}
void correction (int pwmR,int pwmL)
{
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    analogWrite(PWR,pwmR);
    analogWrite(PWL,pwmL);
}
