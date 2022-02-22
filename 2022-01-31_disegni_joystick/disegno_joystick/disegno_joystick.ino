/* Questo sketch configura i 6 bit MSB del PORT-D per generare 
 *  segnali analogici con convertitore DIGITALE-ANALOGICO 6-bit
 *  su CH1 dell'oscilloscopio e configura i 6 bit LSB del PORT-B 
 *  per generare segnali analogici con DAC 6-bit su CH2.
 *  
 *  Configura l'ingresso analogico A0 per leggere la coordinata X
 *  da un Joystick Analogico, A1 per la coordinata Y e A2 (con 
 *  resistenza di Pull-Up) per leggere il pulsante.
 *  
 *  Ogni volta che il tasto viene premuto memorizzo nell'Array disegno
 *  le coordinate del punto in cui si trova in quel momento il Joystick
 *  
 *  Visualizza l'esperienza di laboratorio completa: 
 *  https://youtu.be/lPdT0cLojwc
 *  
 */

#define N_MAX_PUNTI  100

#define JOYSTICK_X    A0
#define JOYSTICK_Y    A1
#define JOYSTICK_SW   16     // Digital Input con Pull-UP


int ch1, ch2;
int disegno[N_MAX_PUNTI][2];
int n_punti;

void setup()
{
  Serial.begin(9600);
    
  /* CH1 dell'oscilloscopio */
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  /* CH2 dell'oscilloscopio */
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  /* pulsante del Joystick con Resistenza di Pull-UP */
  pinMode(JOYSTICK_SW, INPUT_PULLUP);

  /* Azzeramento delle variabili globali */
  ch1 = 0;
  ch2 = 0;
  n_punti = 0;
}

void loop()
{
  int n;

  /* eseguo il disegno */
  for( n=0; n<n_punti; n++)
  {
    ch1 = disegno[n][0];
    ch2 = disegno[n][1];

    Serial.print(ch1);
    Serial.print(",");
    Serial.print(ch2);
    Serial.println();
  
    PORTD = ch1 << 2;
    PORTB = ch2;
  
    delay(1);
  }

  /* mostrare il joystick dove sta puntando */
  ch1 = analogRead( JOYSTICK_X ) >> 4;
  ch2 = 63 - (analogRead( JOYSTICK_Y ) >> 4);

  Serial.print(ch1);
  Serial.print(",");
  Serial.print(ch2);
  Serial.println();
  
  PORTD = ch1 << 2;
  PORTB = ch2;
  
  delay(1);

  /* controllo la pressione del tasto SW */
  if ( digitalRead(JOYSTICK_SW) == LOW )
  {
    if (n_punti < N_MAX_PUNTI)
    {
      disegno[n_punti][0] = ch1;
      disegno[n_punti][1] = ch2;

      n_punti ++;

      n = 0;
      while ( digitalRead(JOYSTICK_SW) == LOW ) 
      { 
        delay (50); /* antirimbalzo */

        /* dopo un secondo cancella la figura */
        n++; 
        if (n > (1000/50)) { n_punti = 0; } 
      }

      delay (200); /* antirimbalzo */
    }
  }
}
