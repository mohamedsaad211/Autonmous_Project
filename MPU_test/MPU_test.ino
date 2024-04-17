// Including Libraries:
#include <Wire.h>
#include <MPU6050_light.h>

// IMU:
MPU6050 mpu(Wire);


unsigned long timer = 0;
float angle=0;

void setup() {
  Serial.begin(9600);
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



void loop() {
  mpu.update();

  if((millis()-timer)>10)
  { 
	  Serial.print("yaw : ");
    angle = int(mpu.getAngleZ());
  	Serial.println(angle);
	  timer = millis();  
   }
}
