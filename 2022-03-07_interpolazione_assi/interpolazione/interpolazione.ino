/*
 * Programma per la movimentazione di un motore stepper 
 * 28BYJ-48 con half-steps 
 * 
 * Visualizza l'esperienza di laboratorio completa: 
 * https://youtu.be/mGzMQISTGJk
 * 
 */

#include <Servo.h>

#define SERVOMOTORE  5

#define FASE_A_P     8
#define FASE_B_P     9
#define FASE_A_N    10
#define FASE_B_N    11

#define TEMPO_MANOVRA_US       5000000L
#define UNITA_DI_TEMPO_US         1000
#define NUMERO_DI_PASSI_MANOVRA (TEMPO_MANOVRA_US / UNITA_DI_TEMPO_US)

#define NUMERO_MANOVRE               6

#define DA_GRADI_A_PASSI(angolo) map(angolo,0,360,0,4096)
   
int  step_motore;
int  posizione_stepper; // passi 4096 = 360 gradi

int  posizione_servo;   // gradi da 0 a 180 gradi

long int passi_manovra;
int      numero_manovra;
const int percorso[NUMERO_MANOVRE+1][2] = 
    {/* SERVO, STEPPER */ 
      {0,0},
      {45,90}, 
      {10,20},
      {150,300},
      {100,200},
      {120,240},
      {0,0} /* copia della prima */
    };

Servo servo;

void setup() {

  /* configurazione motore passo passo */
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

  /* configurazione servomotore */
  posizione_servo = 0;
  servo.attach( SERVOMOTORE /*, min, max */);
  servo.write( posizione_servo );

  /* configurazione controllo numerico */
  passi_manovra = 0;
  numero_manovra = 0;
}

void loop() {

  int posizione_stepper_desiderata;

  // movimentazione degli assi
  posizione_servo   = map(passi_manovra, 
                          0, 
                          NUMERO_DI_PASSI_MANOVRA, 
                          percorso[numero_manovra][0],
                          percorso[numero_manovra+1][0]);

  posizione_stepper_desiderata = map(passi_manovra, 
                          0, 
                          NUMERO_DI_PASSI_MANOVRA, 
                          DA_GRADI_A_PASSI(percorso[numero_manovra][1]),
                          DA_GRADI_A_PASSI(percorso[numero_manovra+1][1]));
                           
  if (posizione_stepper < posizione_stepper_desiderata) {
    posizione_stepper ++;

    step_motore ++; 
    if (step_motore > 8) { step_motore = 1; }
  }
  else if (posizione_stepper > posizione_stepper_desiderata) {
    posizione_stepper --;

    step_motore --; 
    if (step_motore < 1) { step_motore = 8; }
  }

  /* avanzamento passi */
  int velocita;
  velocita = 1;
  //velocita = 1 + a * passi_manovra - b * (passi_manovra*passi_manovra);
  passi_manovra = passi_manovra + velocita;
  if (passi_manovra >= NUMERO_DI_PASSI_MANOVRA)
  {
    passi_manovra = 0;
    numero_manovra ++;
    if (numero_manovra >= NUMERO_MANOVRE) { numero_manovra = 0; }
  }

  /* base dei tempi */
  delayMicroseconds( UNITA_DI_TEMPO_US ); 
  

  // comando del motore stepper
  switch( step_motore ) {
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

  // comando servomotore
  servo.write( posizione_servo );
}
