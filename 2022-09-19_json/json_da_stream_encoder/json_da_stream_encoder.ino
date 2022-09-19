/*
 * Test del parse Json della libreria ArduinoJson.h
 * 
 * Questo programma converte un flusso di caratteri 
 * che trasportano un dataset in linguaggio Json
 * in valori usabili in variabili di Arduino.
 * 
 * Trasmettere via seriale la seguente stringa:
 * {"sensor":"gps","time":1351824120,"data":[48.756080,2.302038]}
 * 
 * Visualizza l'esperienza di laboratorio completa: 
 * https://youtu.be/6LKQW3CQpdE
 *  
 */

#include <ArduinoJson.h>

DynamicJsonDocument doc(200);

void setup() {
  Serial.begin(9600);
}

void loop() {

  DeserializationError error = deserializeJson(doc, Serial);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  const char* sensor = doc["sensor"];
  long time = doc["time"];
  double latitude = doc["data"][0];
  double longitude = doc["data"][1];

  // Print values.
  Serial.println(sensor);
  Serial.println(time);
  Serial.println(latitude, 6);
  Serial.println(longitude, 6);
}
