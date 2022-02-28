/*
 * Programma per la movimentazione di un motore stepper 
 * 28BYJ-48 con half-steps 
 * 
 * Visualizza l'esperienza di laboratorio completa: 
 * https://youtu.be/mGzMQISTGJk
 * 
 */
 
#define FASE_A_P   8
#define FASE_B_P   9
#define FASE_A_N  10
#define FASE_B_N  11

int  step_motore;
int  posizione;

void setup() {

  pinMode( FASE_A_P, OUTPUT );
  pinMode( FASE_B_P, OUTPUT );
  pinMode( FASE_A_N, OUTPUT );
  pinMode( FASE_B_N, OUTPUT );

  digitalWrite( FASE_A_P, LOW );
  digitalWrite( FASE_B_P, LOW );
  digitalWrite( FASE_A_N, LOW );
  digitalWrite( FASE_B_N, LOW );

  step_motore = 1;
  posizione = 0;
}

void loop() {

  // muovo i passi
  if (posizione < 4096) {
    posizione ++;

    step_motore ++; 
    if (step_motore > 8) { step_motore = 1; }
  }
  delayMicroseconds(2000); 
  

  // comando le uscite
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
}
