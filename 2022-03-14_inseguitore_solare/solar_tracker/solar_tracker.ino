/*
 * Programma per la movimentazione di un motore stepper 
 * 28BYJ-48 con half-steps insieme a un servomotore SG90
 * 
 * Il movimento è studiato in modo da inseguire il sole 
 * sulla base dei quattro segnali analogici provenienti 
 * da 4 celle solari fotovaoltaiche connesse agli ingressi 
 * analogici A0..A3 (mediante partitore resistivo).
 * 
 * Visualizza l'esperienza di laboratorio completa: 
 * https://youtu.be/fwKB6lmJ89s
 * 
 */

#include <Servo.h>

#define SERVOMOTORE  5

#define FASE_A_P     8
#define FASE_B_P     9
#define FASE_A_N    10
#define FASE_B_N    11

   
int  step_motore;
int  posizione_stepper; // passi 4096 = 360 gradi

int  posizione_servo;   // gradi da 0 a 180 gradi

Servo servo;

void setup() {

  pinMode( 14, INPUT );
  pinMode( 15, INPUT );
  pinMode( 16, INPUT );
  pinMode( 17, INPUT );
  
  
  Serial.begin ( 115200 );
  Serial.println( "Solar Tracker" );
  
  /* CONFIGURAZIONE MOTORE PASSO-PASSO */
  pinMode( FASE_A_P, OUTPUT );
  pinMode( FASE_B_P, OUTPUT );
  pinMode( FASE_A_N, OUTPUT );
  pinMode( FASE_B_N, OUTPUT );

  digitalWrite( FASE_A_P, LOW );
  digitalWrite( FASE_B_P, LOW );
  digitalWrite( FASE_A_N, LOW );
  digitalWrite( FASE_B_N, LOW );

  step_motore = 1;
  posizione_stepper = 0;

  /* CONFIGURAZIONE SERVOMOTORE */
  posizione_servo = 45;
  servo.attach( SERVOMOTORE /*, min, max */);
  servo.write( posizione_servo );

}

void loop() {

  int a1, a2, a3, a4;

  /* ACQUISIZIONE DELLE CELLE SOLARI */
  a1 = analogRead( A0 ); 
  a2 = analogRead( A1 ); 
  a3 = analogRead( A2 ); 
  a4 = analogRead( A3 ); 

  Serial.print( posizione_servo );
  Serial.print( "," );
  Serial.print( posizione_stepper );
  Serial.print( "," );
  Serial.print( a1 );
  Serial.print( "," );
  Serial.print( a2 );
  Serial.print( "," );
  Serial.print( a3 );
  Serial.print( "," );
  Serial.println( a4 );
    
  /* MOVIMENTAZIONE DEGLI ASSI */
  if ((a2+a3) > (a1+a4)) {

    if (posizione_servo < 180) { posizione_servo ++; }
    
  }
  else if ((a2+a3) < (a1+a4)) {

    if (posizione_servo > 0) { posizione_servo --; }
    
  }
  
  if ((a1+a2) > (a3+a4)) {

    posizione_stepper ++;
    step_motore ++; 
    if (step_motore > 8) { step_motore = 1; }
  
  }
  else if ((a1+a2) < (a3+a4)) {

    posizione_stepper --;
    step_motore --; 
    if (step_motore < 1) { step_motore = 8; }
  }

  
  /* BASE_DEI TEMPI */
  delay( 100 );
     
  /* COMANDO DEL MOTORE STEPPER */
  switch( step_motore ) 
  {
    case 1 : // piloto la fase A in positivo
      digitalWrite( FASE_A_P, HIGH );
      digitalWrite( FASE_B_P, LOW );
      digitalWrite( FASE_A_N, LOW );
      digitalWrite( FASE_B_N, LOW );
      break;
    case 2 : // piloto la fase A in positivo e B in positivo
      digitalWrite( FASE_A_P, HIGH );
      digitalWrite( FASE_B_P, HIGH );
      digitalWrite( FASE_A_N, LOW );
      digitalWrite( FASE_B_N, LOW );
      break;
    case 3 : // piloto la fase B in positivo
      digitalWrite( FASE_A_P, LOW );
      digitalWrite( FASE_B_P, HIGH );
      digitalWrite( FASE_A_N, LOW );
      digitalWrite( FASE_B_N, LOW );
      break;
    case 4 : // piloto la fase B in positivo e A in negativo
      digitalWrite( FASE_A_P, LOW );
      digitalWrite( FASE_B_P, HIGH );
      digitalWrite( FASE_A_N, HIGH );
      digitalWrite( FASE_B_N, LOW );
      break;
    case 5 : // piloto la fase A in negativo
      digitalWrite( FASE_A_P, LOW );
      digitalWrite( FASE_B_P, LOW );
      digitalWrite( FASE_A_N, HIGH );
      digitalWrite( FASE_B_N, LOW );
      break;
    case 6 : // piloto la fase A in negativo e B in negativo
      digitalWrite( FASE_A_P, LOW );
      digitalWrite( FASE_B_P, LOW );
      digitalWrite( FASE_A_N, HIGH );
      digitalWrite( FASE_B_N, HIGH );
      break;
    case 7 : // piloto la fase B in negativo
      digitalWrite( FASE_A_P, LOW );
      digitalWrite( FASE_B_P, LOW );
      digitalWrite( FASE_A_N, LOW );
      digitalWrite( FASE_B_N, HIGH );
      break;
    case 8 : // piloto la fase B in negativo e A in positivo
      digitalWrite( FASE_A_P, HIGH );
      digitalWrite( FASE_B_P, LOW );
      digitalWrite( FASE_A_N, LOW );
      digitalWrite( FASE_B_N, HIGH );
      break;
    default : 
      step_motore = 1;  
      break;
  }

  /* COMANDO DEL SERVOMOTORE */
  servo.write( posizione_servo );
}
