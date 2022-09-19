#include <ArduinoJson.h>

DynamicJsonDocument doc(200);
char json[250]; /* = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}"; */

void setup() {
  Serial.begin(9600);
}


void loop() {

  //String s = Serial.readString();
  //s.toCharArray(json, 250);

  DeserializationError error = deserializeJson(doc, Serial); // deserializeJson(doc, json);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  const char* sensor = doc["sensor"];
  const char* color = doc["colore"];
  long time = doc["time"];
  double latitude = doc["data"][0];
  double longitude = doc["data"][1];

  // Print values.
  Serial.println(sensor);
  Serial.println(color);
  Serial.println(time);
  Serial.println(latitude, 6);
  Serial.println(longitude, 6);
  
}
