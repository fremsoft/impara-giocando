/*
 * Test del Display 7 Segmenti a Catodo Comune collegato su pin 2..9
 * 
 * Collegando il display con un solo resistore da 330 ohm sul catodo comune, 
 * questo sketch ti mostra come cambia la luminosità del puntino DP accendendo
 * prima solo lui e poi anche tutti gli altri led del display.
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
}

void loop()
{
  digitalWrite(SEG_A,  HIGH);
  digitalWrite(SEG_B,  HIGH);
  digitalWrite(SEG_C,  HIGH);
  digitalWrite(SEG_D,  HIGH);
  digitalWrite(SEG_E,  HIGH);
  digitalWrite(SEG_F,  HIGH);
  digitalWrite(SEG_G,  HIGH);
  digitalWrite(SEG_DP, HIGH);
  delay(300); 
  
  digitalWrite(SEG_A,  LOW);
  digitalWrite(SEG_B,  LOW);
  digitalWrite(SEG_C,  LOW);
  digitalWrite(SEG_D,  LOW);
  digitalWrite(SEG_E,  LOW);
  digitalWrite(SEG_F,  LOW);
  digitalWrite(SEG_G,  LOW);
  digitalWrite(SEG_DP, HIGH);
  delay(300); 
}
