#include <SPI.h>
#include <RH_RF95.h>
#include <ArduinoJson.h>

RH_RF95 rf95;

void setup() {
  // put your setup code here, to run once:
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  digitalWrite(7, HIGH); //SENDER
  digitalWrite(8, LOW); //RECEIVER
  while (!Serial) ;
  if (!rf95.init())
    Serial.println("init failed");
}

bool device1 = false;
bool device2 = false;
bool device3 = false;
StaticJsonDocument<200> sensor;
void loop() {
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
  if (rf95.recv(buf, &len)) {
    Serial.println((char*)buf);
  }
  if (Serial.available()) {
    StaticJsonDocument<200> doc;
    String data = Serial.readStringUntil('\n');
    DeserializationError error = deserializeJson(doc, data);
    if (error) {
      return;
    }
    addData(0, doc);
    device1 = true;
  }
  if (Serial1.available()) {
    StaticJsonDocument<200> doc;
    String data = Serial1.readStringUntil('\n');
    DeserializationError error = deserializeJson(doc, data);
    if (error) {
      return;
    }
    addData(1, doc);
    device2 = true;
  }
  if (Serial2.available()) {
    StaticJsonDocument<200> doc;
    String data = Serial2.readStringUntil('\n');
    DeserializationError error = deserializeJson(doc, data);
    if (error) {
      return;
    }
    addData(2, doc);
    device3 = true;
  }
  if (device1 && device2 && device3) {
      device1 = false;
      device2 = false;
      device3 = false;
      String portdata = "";
      serializeJson(sensor, portdata);
      uint8_t datatoserver[portdata.length() + 1];
      portdata.toCharArray(datatoserver, portdata.length() + 1);
      rf95.send(datatoserver, sizeof(datatoserver));
      rf95.waitPacketSent();
      delay(500);
    }
}

void addData(int port, StaticJsonDocument<200> doc) {
  for(int i = 0; i < 6; i++){
    sensor[port][i] = doc[i];
  }
}
