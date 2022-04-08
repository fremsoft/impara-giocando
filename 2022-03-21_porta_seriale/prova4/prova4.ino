/* 
 * Programma dimostrativo per capire come funziona la 
 * porta seriale con Arduino UNO.
 * 
 * Questo programma ascolta ciò che arriva sulla linea
 * seriale e lo ripete. Questo programma mette in evidenza 
 * che il metodo readString della classe Stream, blocca
 * l'esecuzione per un tempo predefinito di 1 secondo.
 * 
 * A differenza del precedente, questo programma si ferma 
 * per un secondo solo quando sono presenti dei caratteri 
 * nel buffer di ricezione della porta seriale.
 * 
 * Visualizza l'esperienza di laboratorio completa: 
 * https://youtu.be/Z3j8LA9UF0E
 */


void setup()
{
  Serial.begin(9600);
}


void loop()
{
  String s;

  if (Serial.available() > 0) {

    s = Serial.readString();

    Serial.println(s);
    
  }
}
