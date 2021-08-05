#include <SPI.h>
#include <RH_RF95.h>

RH_RF95 rf95;

int led = 8;

void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  while (!Serial) ; // Wait for serial port to be available
  if (!rf95.init())
    Serial.println("init failed");
}

void loop()
{
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
  if (rf95.recv(buf, &len))
  {
    Serial.println((char*)buf);
  }
}
