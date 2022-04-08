/* 
 * Programma dimostrativo per capire come funziona la 
 * porta seriale con Arduino UNO.
 * 
 * Questo programma ascolta ciò che arriva sulla linea
 * seriale e lo ripete. Questo programma mette in evidenza 
 * che il metodo readString della classe Stream, blocca
 * l'esecuzione per un tempo predefinito di 1 secondo.
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

  s = Serial.readString();

  Serial.println(s);
}
