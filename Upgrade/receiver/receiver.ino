#include <SPI.h>
#include <RH_RF95.h>
#include <ArduinoJson.h>

RH_RF95 rf95;

void setup()
{
  Serial.begin(9600);
  while (!Serial) ; // Wait for serial port to be available
  Serial.println("Start");
  if (!rf95.init())
    Serial.println("init failed");
}

void loop()
{
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
  if (rf95.recv(buf, &len))
  {
    String data = String((char*)buf);
    Serial.println(data);
  }
  if(Serial.available()){
    String text = Serial.readStringUntil('\n');
    uint8_t data[text.length() + 1];
    text.toCharArray(data, text.length() + 1);
    rf95.send(data, sizeof(data));
    rf95.waitPacketSent();
  }
}
