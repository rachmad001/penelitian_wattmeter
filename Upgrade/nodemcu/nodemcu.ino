#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "OPPO A12";
const char* password = "1234duakali";
void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(30);
    Serial.print(".");
  }
  Serial.print("connecting to ");
  Serial.println(WiFi.SSID());
  Serial.print("IP Address = ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (Serial.available()) {
    String dataSensor = Serial.readStringUntil('\n');
    char* server = "http://v1.penelitianrpla.com/Device";
    WiFiClient client;
    HTTPClient http;

    if (http.begin(client, server)) {
      http.addHeader("content-type", "application/x-www-url-form-urlencoded");
      String data = "data=" + dataSensor;
      int httpResponseCode = http.POST(data);
      if (httpResponseCode > 0) {
        String payload = http.getString();
        Serial.println(payload);
      }
      http.end();
    }
    else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }
}
