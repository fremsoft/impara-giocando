/* 
 * Programma dimostrativo per capire come funziona la 
 * porta seriale con Arduino UNO.
 * 
 * Questo programma trasmette ripetutamente il carattere
 * corrispondente al numero zero (codice ASCII 48 o 30h)
 * cosicché possiamo osservarlo all'oscilloscopio.
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
  char digit = '0';
  
  Serial.write( digit );
}
