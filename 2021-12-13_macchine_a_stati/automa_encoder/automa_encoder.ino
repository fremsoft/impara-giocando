// PROBALO SU THINKER CAD:
// https://www.tinkercad.com/things/6ZEv0ZyfSyf

// Scrivendo sul monitor seriale si simulano gli ingressi digitali:
// 'a' (minuscolo) --> a = 0
// 'A' (maiuscolo) --> a = 1
// 'b' (minuscolo) --> b = 0
// 'B' (maiuscolo) --> b = 1

int stato;
int a, b;
int contatore;

void setup() {

  Serial.begin( 115200 );
  stato = 0;
  a = 0;
  b = 0;
  contatore = 0;

}

void loop() {
  int c;

  // LETTURA DEGLI INGRESSI
  
  if (Serial.available() > 0) {
    
    c = Serial.read();

    switch( c ) {

      case 'a' : a = 0; break;
      case 'A' : a = 1; break;
      case 'b' : b = 0; break;
      case 'B' : b = 1; break;
      
    }
    
  }

  
  // ELABORAZIONE DEGLI INGRESSI
  
  switch( stato ) {

    case 0 : 
      if ((a == 0) && (b == 0)) { stato = 1; }
      break;
    
    case 1 : 
      if (a == 1) { stato = 2; }
      if (b == 1) { stato = 4; contatore --; }
      break;
    
    case 2 : 
      if (a == 0) { stato = 1; }
      if (b == 1) { stato = 3; }
      break;

    case 3 : 
      if (a == 0) { stato = 4; }
      if (b == 0) { stato = 2; }
      break;

    case 4 : 
      if (a == 1) { stato = 3; }
      if (b == 0) { stato = 1; contatore ++; }
      break;

    default : 
      Serial.println( "STATO SCONOSCIUTO" );
      stato = 0;
      break;
  }

  
  // SCRITTURA DELLA USCITE 
  
  Serial.print( "STATO = " );
  Serial.print( stato );
  Serial.print( ", CONTATORE = " );
  Serial.println( contatore );
    
}
