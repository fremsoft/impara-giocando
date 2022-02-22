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
 *  https://youtu.be/1MA13Oi-SsI
 *   
 */

#define MOTORE_DC            8
#define SERVOMOTORE          9

#define JOYSTICK_X          A0
#define JOYSTICK_Y          A1
#define JOYSTICK_SW         16     // Digital Input con Pull-UP

#define PERIODO_PWM_US   20000     // periodo del PWM in microsecondi

#define TIPO_PWM             2

#if TIPO_PWM == 2
  #include <Servo.h>
  Servo servo1;
#endif

void setup() {

  // DEBUG : 
  // Serial.begin( 9600 );
  
  pinMode( MOTORE_DC, OUTPUT );
  digitalWrite( MOTORE_DC, LOW );

#if TIPO_PWM == 2
  //servo1.attach( SERVOMOTORE, 1000, 2000 ); 
  // SEGUENDO LE INDICAZIONI DEL DATASHEET NON COPRE INTERAMENTE I 180 GRADI
  
  servo1.attach( SERVOMOTORE );
#else
  pinMode( SERVOMOTORE, OUTPUT );
  digitalWrite( SERVOMOTORE, LOW );
#endif  

  /* pulsante del Joystick con Resistenza di Pull-UP */
  pinMode(JOYSTICK_SW, INPUT_PULLUP);
}


void loop() {

  digitalWrite( MOTORE_DC, ! digitalRead(JOYSTICK_SW) );

#if TIPO_PWM == 0
  unsigned int ton, toff;
  // COMANDO PWM "CASERECCIO" PER IL SERVOMOTORE
  
  // IMPOSTO IL PERIODO Ton DEL PWM PER PILOTARE IL SERVO
  // 1000 = -90°
  // 1500 =   0°
  // 2000 =  90°
  ton = map( analogRead(JOYSTICK_X), 0, 1023, 1000, 2000);
  toff = (PERIODO_PWM_US - 10000) - ton;
  
  digitalWrite( SERVOMOTORE, HIGH );
  delayMicroseconds(ton);
  
  digitalWrite( SERVOMOTORE, LOW );
  // Currently, the largest value that will produce an accurate delay is 16383;
  delayMicroseconds(10000);
  delayMicroseconds(toff);
#endif  

#if TIPO_PWM == 1
  unsigned int dc;
  // COMANDO PWM CON ANALOGWRITE()
  
  // IMPOSTO IL DUTY CUYCLE DEL PWM PER PILOTARE IL SERVO
  // 1000 = -90° 
  // 1500 =   0°
  // 2000 =  90°
  dc = map( analogRead(JOYSTICK_X), 0, 1023, 125, 250);
  
  analogWrite( SERVOMOTORE, dc );
#endif  

#if TIPO_PWM == 2
  unsigned int angolo;
  // COMANDO PWM CON LIBRERIA SERVO
  
  // IMPOSTO IL DUTY CUYCLE DEL PWM PER PILOTARE IL SERVO
  // 1000 = -90° 
  // 1500 =   0°
  // 2000 =  90°
  angolo = map( analogRead(JOYSTICK_X), 0, 1023, 0, 180);
  
  servo1.write( angolo );
#endif  

}
