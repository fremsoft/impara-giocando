/* 
 * Programma dimostrativo per capire come funzionano la 
 * porta seriale fisica e quella emulata con Arduino UNO.
 * 
 * Attraverso un loop di interfaccia si dimostrano le 
 * funzionalità principali e i limiti della SoftwareSerial.
 * 
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
  String s;
  
  n++;
  mySerial.println(n);
    
  if (Serial.available() > 0) {

    s = Serial.readString();

    Serial.println(s);
    
  }

  delay(1000);
}
