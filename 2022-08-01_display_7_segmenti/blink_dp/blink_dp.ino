/*
 * Test del Display 7 Segmenti a Catodo Comune collegato su pin 2..9
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
  digitalWrite(SEG_DP, HIGH);
  delay(300); 
  digitalWrite(SEG_DP, LOW);
  delay(300); 
}
