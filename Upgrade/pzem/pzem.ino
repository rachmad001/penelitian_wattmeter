#include <PZEM004Tv30.h>
#include <ArduinoJson.h>


PZEM004Tv30 pzem(11, 12);

#define max485rec 8
#define max485send 7

int state = 1;

void setup() {
  pinMode(max485rec, OUTPUT);
  pinMode(max485send, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  Serial.begin(9600);
  digitalWrite(max485rec, LOW); //receiving mode
  digitalWrite(max485send, HIGH); //SENDER MODE
  digitalWrite(5, 1);
}

void loop() {
  const int capacity = JSON_OBJECT_SIZE(200);
  StaticJsonDocument<200> doc;
  float voltage = pzem.voltage();
  doc[0] = voltage;
  float current = pzem.current();
  doc[1] = current;
  float power = pzem.power();
  doc[2] = power;
  float energy = pzem.energy();
  doc[3] = energy;
  float frequency = pzem.frequency();
  doc[4] = frequency;
  float pf = pzem.pf();
  doc[5] = pf;
  if (voltage != NAN && current != NAN && doc[0] != NULL && doc[1] != NULL) {
    String text = "";
    serializeJson(doc, text);
    Serial.println(text);
  }
  if (Serial.available()) {
    String text = Serial.readStringUntil('\n');
    StaticJsonDocument<200> data;
    DeserializationError error = deserializeJson(data, text);
    if (error) {
      return;
    }
    if (digitalRead(2)) {
      int port = data["port1"];
      if (port != state) {
        digitalWrite(5, port);
        state = port;
      }
    }
    if (digitalRead(3)) {
      int port = data["port2"];
      if (port != state) {
        digitalWrite(5, port);
        state = port;
      }
    }
    if (digitalRead(4)) {
      int port = data["port3"];
      if (port != state) {
        digitalWrite(5, port);
        state = port;
      }
    }
  }
}
