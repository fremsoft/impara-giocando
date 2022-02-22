/* 
 *  Questo Sketch serve a testare le funzionalità
 *  del servomotore SG90 e del motore in corrente 
 *  continua.
 *  
 *  Al pin 8 è connesso un transistor NPN (PN2222)
 *  con Resistenza di base=1k ohm per comandare il 
 *  motore in corrente continua quando si preme il 
 *  tasto del Joystick.
 *  
 *  Al pin 9 è collegato il segnale PWM che comanda 
 *  il servomotore SG90.
 *  
 *  Sugli ingressi analogici A0 e A1 sono posizionati 
 *  rispettivamente Rx e Ry del Joystick, mentre su A2
 *  in configurazione ingresso digitale con resistenza
 *  di Pull-UP il punsante Sw del Joystick.
 *  
 *  Muovendo l'asse X del Joystick si produce un 
 *  movimento del servomotore da -90 a +90 gradi
 *  
 *  Visualizza l'esperienza di laboratorio completa:  
 *  https://youtu.be/IW2o1Hg2DLk
 *  
 */

#define MOTORE_DC            8
#define SERVOMOTORE          9

#define JOYSTICK_X          A0
#define JOYSTICK_Y          A1
#define JOYSTICK_SW         16     // Digital Input con Pull-UP

#define PERIODO_PWM_US   20000     // periodo del PWM in microsecondi

void setup() {

  // DEBUG : 
  // Serial.begin( 9600 );
  
  pinMode( MOTORE_DC, OUTPUT );
  digitalWrite( MOTORE_DC, LOW );

  pinMode( SERVOMOTORE, OUTPUT );
  digitalWrite( SERVOMOTORE, LOW );

  /* pulsante del Joystick con Resistenza di Pull-UP */
  pinMode(JOYSTICK_SW, INPUT_PULLUP);
  
}


void loop() {

  unsigned int ton, toff;

  digitalWrite( MOTORE_DC, ! digitalRead(JOYSTICK_SW) );

  
  // IMPOSTO IL PERIODO Ton DEL PWM PER PILOTARE IL SERVO
  // 1000 = -90°
  // 1500 =   0°
  // 2000 =  90°
  ton = map( analogRead(JOYSTICK_X), 0, 1023, 1000, 2000);
  toff = (PERIODO_PWM_US - 10000) - ton;

  /*
   * DEBUG:
   * Serial.print( ton );
   * Serial.print( "," );
   * Serial.println( toff );
   */
  
  // COMANDO PWM "CASERECCIO" PER IL SERVOMOTORE
  digitalWrite( SERVOMOTORE, HIGH );
  delayMicroseconds(ton);
  
  digitalWrite( SERVOMOTORE, LOW );
  // Currently, the largest value that will produce an accurate delay is 16383;
  delayMicroseconds(10000);
  delayMicroseconds(toff);
  
}
