/* 
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
