#include <MPU6050.h>

/***************************
    scl-----A5
    Sda-----A4
***************************/
/**************************/
#include <Wire.h>
#include <MPU6050.h>
MPU6050 mpu;
#define adc1 A0
#define adc2 A1
#define adc3 A2
#define adc4 A3
#define ledd 13
int flex2=0,flex1=0,flex3=0,flex4=0;
void setup() 
{
  pinMode(ledd,OUTPUT);
  digitalWrite(ledd,LOW);
 Serial.begin(9600 );
 Serial.println("Initialize MPU6050");
 while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
 {
  Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
  delay(500);
 }
 checkSettings();
}
void checkSettings()
{
 Serial.println();  
 Serial.print(" * Sleep Mode:            ");
 Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");
 Serial.print(" * Clock Source:          ");
 switch(mpu.getClockSource())
 {
  case MPU6050_CLOCK_KEEP_RESET:     Serial.println("Stops the clock and keeps the timing generator in reset"); break;
  case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;
  case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;
  case MPU6050_CLOCK_PLL_ZGYRO:      Serial.println("PLL with Z axis gyroscope reference"); break;
  case MPU6050_CLOCK_PLL_YGYRO:      Serial.println("PLL with Y axis gyroscope reference"); break;
  case MPU6050_CLOCK_PLL_XGYRO:      Serial.println("PLL with X axis gyroscope reference"); break;
  case MPU6050_CLOCK_INTERNAL_8MHZ:  Serial.println("Internal 8MHz oscillator"); break;
 }
 Serial.print(" * Accelerometer offsets: ");
 Serial.print(mpu.getAccelOffsetX());
 Serial.print(" / ");
 Serial.print(mpu.getAccelOffsetY());
 Serial.print(" / ");
 Serial.println(mpu.getAccelOffsetZ());
 Serial.println();
}

void loop()
{
  flex1=analogRead(adc1);
  flex2=analogRead(adc2);
  flex3=analogRead(adc3);
  flex4=analogRead(adc4);
  delay(10);
  Vector rawAccel = mpu.readRawAccel();
  Vector normAccel = mpu.readNormalizeAccel();
    delay(1000);
 if(flex1<1019)
  {
   digitalWrite(ledd,LOW);
   if(normAccel.XAxis>3){Serial.println("HELP");}
   else if(normAccel.XAxis<-3){Serial.println("WASHROOM");}
   else if(normAccel.YAxis>3){Serial.println("MEDICINE");}
   else if(normAccel.YAxis<-3){Serial.println("FOOD");}
  }
  else
  {
   digitalWrite(ledd,HIGH);
   if(normAccel.XAxis>3){Serial.println("THANK YOU");}
   else if(normAccel.XAxis<-3){Serial.println("I LOVE YOU");}
   else if(normAccel.YAxis>3){Serial.println("SORRY");}
   else if(normAccel.YAxis<-3){Serial.println("HELLO");} 
  }
  
}
