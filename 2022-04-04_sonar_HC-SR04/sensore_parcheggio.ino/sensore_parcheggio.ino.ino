/* 
 * Visualizza l'esperienza di laboratorio completa: 
 * https://youtu.be/anoGPaztyF4
 */

#define  BUZZER              5
#define  TEMPO_CICALINO_MS  50

#define  SONAR_ECHO          6
#define  SONAR_TRIG          7

#define  DISTANZA_MIN_MM    60
#define  DISTANZA_MAX_MM   150
#define  ATTESA_MIN_MS     200
#define  ATTESA_MAX_MS    1000

      


void setup()
{
  Serial.begin(9600);

  pinMode( BUZZER,     OUTPUT );
  digitalWrite( BUZZER, LOW );

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


  if (d != 0) {
    if (d <= DISTANZA_MIN_MM) {
      /* SUONO CONTINUO */
      digitalWrite( BUZZER, HIGH );
    }
    else if (d > DISTANZA_MAX_MM ) {
      /* NESSUN SUONO */
      digitalWrite( BUZZER, LOW );
    }
    else {
      /* SUONA UN BEEP */
      digitalWrite( BUZZER, HIGH );
      delay( TEMPO_CICALINO_MS );
      digitalWrite( BUZZER, LOW );

      delay( map(d, DISTANZA_MIN_MM, DISTANZA_MAX_MM, ATTESA_MIN_MS, ATTESA_MAX_MS) );
    }
  }
}
