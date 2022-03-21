/* 
 * Visualizza l'esperienza di laboratorio completa: 
 * https://youtu.be/Z3j8LA9UF0E
 */


int contatore;

void setup()
{
  Serial.begin(9600);

  pinMode ( LED_BUILTIN, OUTPUT );
  digitalWrite ( LED_BUILTIN, LOW );

  contatore = 0;
}


void loop()
{
  char digit;
  String s;

  digit = Serial.read();
  
  if (digit == '1') {
    digitalWrite ( LED_BUILTIN, HIGH );
  }

  if (digit == '0') {
    digitalWrite ( LED_BUILTIN, LOW );
  }

  Serial.println( contatore ++ );
}
