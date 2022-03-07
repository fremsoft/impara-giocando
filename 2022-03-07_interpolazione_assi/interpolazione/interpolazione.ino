/*
 * Programma per la movimentazione di un motore stepper 
 * 28BYJ-48 con half-steps insieme a un servomotore SG90
 * 
 * Il movimento è interpolato in modo tale da muovere in
 * perfetta sincronia i due motori, non uno alla volta, 
 * sia con moto uniforme (lineare), sia con rampe di 
 * accelerazione.
 * 
 * Visualizza l'esperienza di laboratorio completa: 
 * https://youtu.be/bF1s6Cmcq7M
 * 
 */

#include <Servo.h>

#define SERVOMOTORE  5

#define FASE_A_P     8
#define FASE_B_P     9
#define FASE_A_N    10
#define FASE_B_N    11

/* commenta solo una opzione LINEARE o ACCELERATO */
#define MOVIMENTO_LINEARE        
//#define MOVIMENTO_ACCELERATO    


#define TEMPO_MANOVRA_US       3000000L
#define UNITA_DI_TEMPO_US         1000

#ifdef MOVIMENTO_LINEARE
#define NUMERO_DI_PASSI_MANOVRA (TEMPO_MANOVRA_US / UNITA_DI_TEMPO_US)
#else
#define NUMERO_DI_PASSI_MANOVRA ((4*TEMPO_MANOVRA_US) / UNITA_DI_TEMPO_US) /* il tempo va moltiplicato di 3,666 volte */
#endif

#define NUMERO_MANOVRE               6

#define DA_GRADI_A_PASSI(angolo) map(angolo,0,360,0,4096)


   
int  step_motore;
int  posizione_stepper; // passi 4096 = 360 gradi

int  posizione_servo;   // gradi da 0 a 180 gradi

long int passi_manovra;
int      numero_manovra;
const int percorso[NUMERO_MANOVRE+1][2] = 
    { /* SERVO, STEPPER */ 
      {0,0},
      {45,90}, 
      {10,20},
      {150,300},
      {100,200},
      {120,240},
      {0,0} /* copia della prima posizione */
    };

Servo servo;

void setup() {

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
  posizione_servo = 0;
  servo.attach( SERVOMOTORE /*, min, max */);
  servo.write( posizione_servo );

  /* CONFIGURAZIONE CONTROLLO NUMERICO */
  passi_manovra = 0;
  numero_manovra = 0;
}

void loop() {

  int posizione_stepper_desiderata;

  /* MOVIMENTAZIONE DEGLI ASSI */
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

  /* AVANZAMENTO PASSI */
  int velocita;
#ifdef MOVIMENTO_LINEARE
  velocita = 1;
#endif
  
#ifdef MOVIMENTO_ACCELERATO
  /* 
   *  Calcolo della curva di velocità parabolica per
   *  realizzare un moto uniformemente accelerato per 
   *  compensare le inerzie ( F = m * a )
   *   
   *   Equazione della velocità parabolica:
   *   velocita = 1 + a * passi_manovra - b * (passi_manovra^2)
   *     
   *   per passi_manovra = 0, velocita = 1
   *   
   *   1 = 1 + a * NUMERO_DI_PASSI_MANOVRA - b * (NUMERO_DI_PASSI_MANOVRA ^ 2)
   *   0 = 0 + a * NUMERO_DI_PASSI_MANOVRA - b * (NUMERO_DI_PASSI_MANOVRA ^ 2)
   *   a * NUMERO_DI_PASSI_MANOVRA = b * (NUMERO_DI_PASSI_MANOVRA ^ 2)
   *   a = b * ( NUMERO_DI_PASSI_MANOVRA )
   *   
   *   velocita = 1 + b * NUMERO_DI_PASSI_MANOVRA * passi_manovra - b * (passi_manovra ^ 2)
   *   velocita = 1 + b * passi_manovra * ( NUMERO_DI_PASSI_MANOVRA - passi_manovra)
   *   
   *   per passi_manovra = N/2, velocita = 5
   *   
   *   5 = 1 + b * (NUMERO_DI_PASSI_MANOVRA/2) * ( NUMERO_DI_PASSI_MANOVRA - NUMERO_DI_PASSI_MANOVRA/2 ) 
   *   5 = 1 + b * (NUMERO_DI_PASSI_MANOVRA/2) * ( NUMERO_DI_PASSI_MANOVRA/2 ) 
   *   4 = b * ( NUMERO_DI_PASSI_MANOVRA ^ 2 / 4 ) 
   *   b = (4 * 4) / ( NUMERO_DI_PASSI_MANOVRA ^ 2 )
   *    
   *   velocita = 1 + 16 * passi_manovra * ( NUMERO_DI_PASSI_MANOVRA - passi_manovra) / (NUMERO_DI_PASSI_MANOVRA ^ 2)
   */
   
  velocita = 1 + (16L * (long)passi_manovra * (long)(NUMERO_DI_PASSI_MANOVRA - passi_manovra)) / (long)(NUMERO_DI_PASSI_MANOVRA*NUMERO_DI_PASSI_MANOVRA);
#endif

  passi_manovra = passi_manovra + velocita;
  if (passi_manovra >= NUMERO_DI_PASSI_MANOVRA)
  {
    passi_manovra = 0;
    numero_manovra ++;
    if (numero_manovra >= NUMERO_MANOVRE) { numero_manovra = 0; }
  }

  /* BASE_DEI TEMPI */
  delayMicroseconds( UNITA_DI_TEMPO_US ); 
  
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
