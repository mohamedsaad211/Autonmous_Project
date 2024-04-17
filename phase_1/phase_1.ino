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
#define ENL 2

void readEncoder_R();
void readEncoder_L();
void IMU();
void setMotor(int dir, int pwmVal ,int sel, int in1 ,int in2);



unsigned long timer = 0;
float angle=0;

volatile double pos_R;
volatile double pos_L;



void setup()
{

Serial.begin(9600);

pinMode(ENR,INPUT);
digitalWrite(2, HIGH);       
attachInterrupt(digitalPinToInterrupt(ENR),readEncoder_R,RISING);

pinMode(ENL,INPUT);
digitalWrite(3, HIGH);       
attachInterrupt(digitalPinToInterrupt(ENL),readEncoder_L,RISING);

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

}

void loop() 
{ 
  IMU();

}


// void setMotor(char sel,int pwmVal,int dir){

//   if(dir == 1 && sel =="R"){  

//     analogWrite(PWR,pwmVal);
//     digitalWrite(IN1,HIGH);
//     digitalWrite(IN2,LOW);
//   }
//   else if(dir == -1 && sel =="R"){
//     analogWrite(PWR,pwmVal);
//     digitalWrite(IN2,LOW);
//     digitalWrite(in2,HIGH);
//   }
//   else
//   {
//     digitalWrite(in1,LOW);
//     digitalWrite(in2,LOW);
//   }
// }


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
    angle = int(mpu.getAngleZ());
  	Serial.println(angle);
	  timer = millis();  
   }
}
