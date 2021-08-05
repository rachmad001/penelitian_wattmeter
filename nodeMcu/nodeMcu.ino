#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "found";
const char* password = "zxcde321";
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
  StaticJsonDocument<200> doc;
  String dataSensor = Serial.readStringUntil('\n');
  DeserializationError error = deserializeJson(doc, dataSensor);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
  float volt = doc["VoltAc"];
  float ampere = doc["Ampere"];
  float watt = doc["Watt"];

  String server = "http://penelitianrpla.com/sensor.php?";
  String datatoweb = "volt=" + String(volt) + "&ampere=" + String(ampere) + "&watt=" + String(watt);
  String serverPath = server + datatoweb;
  WiFiClient client;
  HTTPClient http;

  if (http.begin(client, serverPath.c_str())) {
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
  else {
    Serial.printf("[HTTP} Unable to connect\n");
  }

}
