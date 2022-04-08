/* 
 * Programma dimostrativo per capire come funzionano la 
 * porta seriale fisica e quella emulata con Arduino UNO.
 * 
 * Attraverso un meccanismo di lettura molto grezzo si 
 * possono trasmettere dei numeri da un Arduino all'altro.
 * 
 * Usando la SoftwareSerial simuliamo la presenza di un 
 * secondo Arduino che trasmette i dati via seriale.
 * 
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
  String s;
  
  Serial.println(n);
    
  if (mySerial.available() > 0) {

    s = mySerial.readString();

    /* Serial.println(s); */
    n = s.toInt() + 1;
    
  }

  delay(1000);
}
