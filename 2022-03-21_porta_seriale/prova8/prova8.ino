/* 
 * Visualizza l'esperienza di laboratorio completa: 
 * https://youtu.be/JQ6aAkAivsE
 */

#include <SoftwareSerial.h>
#include <ArduinoJson.h>

#define RX_AUX     9
#define TX_AUX     8

SoftwareSerial mySerial ( RX_AUX, TX_AUX );

DynamicJsonDocument doc(200);
/* StaticJsonDocument<200> doc; */

void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(100);

  // Define pin modes for TX and RX
  pinMode( RX_AUX, INPUT );
  pinMode( TX_AUX, OUTPUT );
  mySerial.begin(9600);
  mySerial.listen();  

  doc["esempio"] = "Json";
  doc["n"] = 0;
}

#define NO_USE_LIBRARY_ARDUINO_JSON 

void loop()
{

#ifdef USE_LIBRARY_ARDUINO_JSON
  serializeJson(doc, mySerial);
#else
  mySerial.print("{ \"esempio\" : \"Json\", \"n\" : ");
  mySerial.print( doc["n"].as<int>() );
  mySerial.println(" } ");
#endif

  delay(1000);
}

void serialEvent() {
  String s;
  
  /*if (Serial.available() > 0) {*/

    s = Serial.readString();

    Serial.println(s);

    deserializeJson(doc, s);

    doc["n"] = ( doc["n"].as<int>() ) + 1;
    
  /*}*/
    
}
