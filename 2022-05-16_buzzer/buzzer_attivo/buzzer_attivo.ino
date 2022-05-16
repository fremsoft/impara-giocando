/* 
 * Questo programma per Arduino UNO serve a collaudare il buzzer attivo
 * 
 * TMB12A05
 * 
 * 
 * Visualizza l'esperienza di laboratorio completa: 
 * https://youtu.be/Cs4E_jhcFlY
 * 
 */

#define BUZZER    4

void setup() {

  pinMode( BUZZER, OUTPUT );
  
}

void loop() {

  digitalWrite( BUZZER, HIGH );
  
}



 
