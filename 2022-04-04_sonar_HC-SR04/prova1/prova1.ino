/* 
 * Visualizza l'esperienza di laboratorio completa: 
 * https://youtu.be/anoGPaztyF4
 */

#define  SONAR_ECHO    6
#define  SONAR_TRIG    7


void setup()
{
  Serial.begin(9600);

  pinMode( SONAR_ECHO, INPUT );
  pinMode( SONAR_TRIG, OUTPUT );
}


void loop()
{
  unsigned long t, d;

  /* produco impulso */
  digitalWrite( SONAR_TRIG, HIGH );
  delayMicroseconds( 10 );
  digitalWrite( SONAR_TRIG, LOW );
  
  /* leggo il segnale di ritorno */
  t = pulseIn( SONAR_ECHO, HIGH, 30000 ); /* oltre i 450 cm ritorna 0 */

  /* calcolo distanza */
  d = t / 6;  /* approssimata ed espressa in millimetri */

  /* scrivo distanza */
  Serial.println( d );

  delay( 100 );
}
