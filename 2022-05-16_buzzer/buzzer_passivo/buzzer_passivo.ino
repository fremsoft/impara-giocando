/* 
 * Questo programma per Arduino UNO serve a collaudare il buzzer passivo
 * 
 * https://www.mouser.it/datasheet/2/334/AT-1224-TWT-R-41276.pdf
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

  /*
  digitalWrite( BUZZER, LOW );
  delayMicroseconds(208);
  digitalWrite( BUZZER, HIGH );
  delayMicroseconds(208);
  */

  for ( int f=1000; f<5000; f+=15 ) {
    
     tone ( BUZZER, f );
     delay( 1 );
 
  }

  for ( int f=5000; f>1000; f-=15 ) {
    
     tone ( BUZZER, f );
     delay( 1 );
 
  }
  
}



 
