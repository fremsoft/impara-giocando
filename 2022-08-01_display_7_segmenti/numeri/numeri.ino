/*
 * Test del Display 7 Segmenti a Catodo Comune collegato su pin 2..9
 * 
 * Questo programma conta da 0 a 9 sul display a 7 segmenti in continuazione
 * 
 * Visualizza l'esperienza di laboratorio completa: 
 * https://youtu.be/eWZZ-GNG15Y
 *  
 */


#define  SEG_A   2
#define  SEG_B   3
#define  SEG_C   4
#define  SEG_D   5
#define  SEG_E   6
#define  SEG_F   7
#define  SEG_G   8
#define  SEG_DP  9

                        /* ABCDEFGp */
const unsigned char _0 = 0b11111100;
const unsigned char _1 = 0b01100000;
const unsigned char _2 = 0b11011010;
const unsigned char _3 = 0b11110010;
const unsigned char _4 = 0b01100110;
const unsigned char _5 = 0b10110110;
const unsigned char _6 = 0b10111110;
const unsigned char _7 = 0b11100000;
const unsigned char _8 = 0b11111110;
const unsigned char _9 = 0b11110110;

const unsigned char numeri[] = { _0, _1, _2, _3, _4, _5, _6, _7, _8, _9 };  

int contatore;

void setup()
{
  pinMode(SEG_A, OUTPUT);
  pinMode(SEG_B, OUTPUT);
  pinMode(SEG_C, OUTPUT);
  pinMode(SEG_D, OUTPUT);
  pinMode(SEG_E, OUTPUT);
  pinMode(SEG_F, OUTPUT);
  pinMode(SEG_G, OUTPUT);
  pinMode(SEG_DP, OUTPUT);

  digitalWrite(SEG_A,  LOW );
  digitalWrite(SEG_B,  LOW );
  digitalWrite(SEG_C,  LOW );
  digitalWrite(SEG_D,  LOW );
  digitalWrite(SEG_E,  LOW );
  digitalWrite(SEG_F,  LOW );
  digitalWrite(SEG_G,  LOW );
  digitalWrite(SEG_DP, LOW );

  contatore = 0;
}

void loop()
{
  digitalWrite(SEG_A,  bitRead( numeri[contatore], 7) );
  digitalWrite(SEG_B,  bitRead( numeri[contatore], 6) );
  digitalWrite(SEG_C,  bitRead( numeri[contatore], 5) );
  digitalWrite(SEG_D,  bitRead( numeri[contatore], 4) );
  digitalWrite(SEG_E,  bitRead( numeri[contatore], 3) );
  digitalWrite(SEG_F,  bitRead( numeri[contatore], 2) );
  digitalWrite(SEG_G,  bitRead( numeri[contatore], 1) );
  digitalWrite(SEG_DP, bitRead( numeri[contatore], 0) );

  delay(1000);
  contatore ++; if (contatore > 9) { contatore = 0; }
  // metodo alternativo 
  // contatore = (contatore + 1) % 10;
}
