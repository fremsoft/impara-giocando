/* 
 * Visualizza l'esperienza di laboratorio completa: 
 * https://youtu.be/JQ6aAkAivsE
 */

#include <SoftwareSerial.h>

#define RX_AUX     9
#define TX_AUX     8

SoftwareSerial mySerial ( RX_AUX, TX_AUX );

int n;

void setup()
{
  Serial.begin(9600);

  // Define pin modes for TX and RX
  pinMode( RX_AUX, INPUT );
  pinMode( TX_AUX, OUTPUT );
  mySerial.begin(9600);
  mySerial.listen();  

  n = 0;
}

void loop()
{
  mySerial.println(n + 1);

  delay(1000);
}

void serialEvent() {
  String s;
  
  /*if (Serial.available() > 0) {*/

    s = Serial.readString();

    Serial.println(s);

    n = s.toInt();
    
  /*}*/
    
}
