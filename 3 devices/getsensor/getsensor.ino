#include <SPI.h>
#include <RH_RF95.h>
#include "ACS712.h"
RH_RF95 rf95;

ACS712 sensor(ACS712_30A, A0);
ACS712 sensor1(ACS712_30A, A1);
ACS712 sensor2(ACS712_30A, A2);

void setup() 
{

  Serial.begin(9600);
  Serial.println("Calibrating... Ensure that no current flows through the sensor at this moment");
  sensor.calibrate();
  sensor1.calibrate();
  sensor2.calibrate();
  Serial.println("Done!");
  while (!Serial) ; // Wait for serial port to be available
  if (!rf95.init())
    Serial.println("init failed");
}

void loop()
{
  //standar listrik yang digunakan
  float U = 240;

  //untuk mendapatkan arus ampere
  float I = sensor.getCurrentAC();
  float I1 = sensor1.getCurrentAC();
  float I2 = sensor2.getCurrentAC();
  
  //menghitung total watt
  float P = U * I;
  float P1 = U * I1;
  float P2 = U * I2;

  String dataToNode = "{\"VoltAc\": " + String(U) + 
                      ", \"Ampere\": " + String(I) + 
                      ", \"Watt\": "+ String(P) +
                      ", \"Ampere1\": " + String(I1) +
                      ", \"Watt1\": "+ String(P1) +
                      ", \"Ampere2\": " + String(I2) +
                      ", \"Watt2\": "+ String(P2) +
                      "}";
                      
  int str_len = dataToNode.length();
  uint8_t data[str_len+1];
  dataToNode.toCharArray(data, str_len+1);
  rf95.send(data, sizeof(data));
  
  rf95.waitPacketSent();
  delay(500);
}
