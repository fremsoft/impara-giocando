/*
 *  Visualizza l'esperienza di laboratorio completa: 
 *  https://youtu.be/9Wre1SoD-30
 *  
 */

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop()
{
  PORTD ++;
  if (PORTD > 200) { PORTD = 100; }
  delay(1);
}
