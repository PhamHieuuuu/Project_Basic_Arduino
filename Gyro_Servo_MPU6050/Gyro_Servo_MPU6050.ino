#include <MPU6050_tockn.h>
#include <Wire.h>
#include"Servo.h"

Servo dc;
MPU6050 mpu6050(Wire);

float offsetX, offsetY, offsetZ;

void setup() {
  dc.attach(13);
  Serial.begin(115200);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  mpu6050.update();
  offsetX = mpu6050.getAngleX();
  offsetY = mpu6050.getAngleY();
  offsetZ = mpu6050.getAngleZ();
  dc.write(90);
}

int Servo_Angle;

void loop() {
  mpu6050.update();
//  float x = mpu6050.getAngleX() - offsetX;
  float y = mpu6050.getAngleY() - offsetY;
 // Serial.println("Góc nghiêng Y: "+ String(y));

//  float z = mpu6050.getAngleZ() - offsetZ;
  if(y<0){
    Servo_Angle = map(y,-180,0,0,90);
    dc.write(Servo_Angle);
    Serial.println("L: "+ String(y)+" | Servo Angle: "+ String(Servo_Angle));
  }
  else if(y>0){
    Servo_Angle = map(y,0,180,90,180);
    dc.write(Servo_Angle);
    Serial.println("R: "+ String(y) + " | Servo Angle: "+ String(Servo_Angle) );
  }
}
