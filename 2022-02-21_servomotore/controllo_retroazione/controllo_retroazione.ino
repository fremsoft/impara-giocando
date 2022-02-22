/*
 * Questo programma serve a realizzare il controllo di posizione 
 * per un servomotore costituito da un motore DC pilotato mediante
 * driver L293D e in cui la posizione angolare viene rilevata 
 * mediante un potenziometro, comandato con un Joystick analogico.
 * 
 * I test sono stati condotti usando un servomotore SG90 a cui è 
 * stata sottratta la parte attiva (controller), utilizzando solamente 
 * motore, cascata di ingranaggi e potenziometro.
 * 
 * Visualizza l'esperienza di laboratorio completa: 
 * https://youtu.be/sk58MOnjTg8
 * 
 */
 
#define L293D_ENABLE   11
#define L293D_A        10
#define L293D_B         9

#define JOYSTICK_X     A0     // comando dell'operatore
#define POTENZIOMETRO  A3     // trasduttore di posizione angolare

#define K_P             1     // costante di proporzionalita' del controllo
#define ZONA_MORTA     40     // zona di lavoro in cui il driver deve restare spento

void setup() {

  Serial.begin( 115200 );

  pinMode( L293D_ENABLE, OUTPUT );
  pinMode( L293D_A,      OUTPUT );
  pinMode( L293D_B,      OUTPUT );

  pinMode( JOYSTICK_X,   INPUT );   /* superflua */  
  
}

void loop() {

  int velocita, duty_cycle, setpoint, posizione;

  setpoint  = analogRead( JOYSTICK_X );
  posizione = analogRead( POTENZIOMETRO );

  velocita = (setpoint - posizione) * K_P;

  if (velocita > ZONA_MORTA) {
    duty_cycle = constrain(velocita, 0, 255);
  
    analogWrite( L293D_A, duty_cycle );
    analogWrite( L293D_B, 0 );
    digitalWrite( L293D_ENABLE, HIGH );
  } 
  else 
  if (velocita < -ZONA_MORTA) {
    duty_cycle = constrain((0-velocita), 0, 255);
      
    analogWrite( L293D_A, 0 );
    analogWrite( L293D_B, duty_cycle );
    digitalWrite( L293D_ENABLE, HIGH );
  } 
  else /* -ZONA_MORTA < velocita < ZONA_MORTA */ {
    duty_cycle = 0;
      
    analogWrite( L293D_A, 0 );
    analogWrite( L293D_B, 0 );
    digitalWrite( L293D_ENABLE, HIGH );
  }

  Serial.print( "0,255,1023," );  // Limiti fissi per Plotter seriale
  Serial.print( setpoint );
  Serial.print( "," );
  Serial.print( posizione );
  Serial.print( "," );
  Serial.print( velocita );
  Serial.print( "," );
  Serial.println( duty_cycle );
  
}
