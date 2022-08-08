/*
 * Test del Display 7 Segmenti a 4 cifre Catodo Comune collegato su pin 2..9
 * 
 * Poi i catodi comuni su 10..13
 * 
 * Questo sketch ti mostra come accendere una cifra per volta usando solo 
 * i pin di Arduino (attenzione a non superare i 40 mA sui Catodi comuni)
 * 
 * Visualizza l'esperienza di laboratorio completa: 
 * https://youtu.be/vYJxRcf4lOo
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

#define  DIGIT1  13
#define  DIGIT2  12
#define  DIGIT3  11
#define  DIGIT4  10

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

  pinMode (DIGIT4, OUTPUT);
  digitalWrite(DIGIT4, LOW);

  // quando sono configurati come ingressi i digit restano spenti
  pinMode (DIGIT1, INPUT);
  pinMode (DIGIT2, INPUT);
  pinMode (DIGIT3, INPUT);
  
}

void loop()
{
  // 1 CIFRA A SINISTRA
  pinMode (DIGIT1, OUTPUT);
  digitalWrite(DIGIT1, LOW);
  // quando sono configurati come ingressi i digit restano spenti
  pinMode (DIGIT2, INPUT);
  pinMode (DIGIT3, INPUT);
  pinMode (DIGIT4, INPUT);
  
  digitalWrite(SEG_A,  LOW);
  digitalWrite(SEG_B,  HIGH);
  digitalWrite(SEG_C,  HIGH);
  digitalWrite(SEG_D,  LOW);
  digitalWrite(SEG_E,  LOW);
  digitalWrite(SEG_F,  LOW);
  digitalWrite(SEG_G,  LOW);
  digitalWrite(SEG_DP, LOW);
  delay(1); 
  digitalWrite(SEG_A,  LOW);
  digitalWrite(SEG_B,  LOW);
  digitalWrite(SEG_C,  LOW);
  digitalWrite(SEG_D,  LOW);
  digitalWrite(SEG_E,  LOW);
  digitalWrite(SEG_F,  LOW);
  digitalWrite(SEG_G,  LOW);
  digitalWrite(SEG_DP, LOW);

  // 2 CIFRA 
  pinMode (DIGIT2, OUTPUT);
  digitalWrite(DIGIT2, LOW);
  // quando sono configurati come ingressi i digit restano spenti
  pinMode (DIGIT1, INPUT);
  pinMode (DIGIT3, INPUT);
  pinMode (DIGIT4, INPUT);
  
  digitalWrite(SEG_A,  HIGH);
  digitalWrite(SEG_B,  HIGH);
  digitalWrite(SEG_C,  LOW);
  digitalWrite(SEG_D,  HIGH);
  digitalWrite(SEG_E,  HIGH);
  digitalWrite(SEG_F,  LOW);
  digitalWrite(SEG_G,  HIGH);
  digitalWrite(SEG_DP, LOW);
  delay(1); 
  digitalWrite(SEG_A,  LOW);
  digitalWrite(SEG_B,  LOW);
  digitalWrite(SEG_C,  LOW);
  digitalWrite(SEG_D,  LOW);
  digitalWrite(SEG_E,  LOW);
  digitalWrite(SEG_F,  LOW);
  digitalWrite(SEG_G,  LOW);
  digitalWrite(SEG_DP, LOW);
  
  // 3 CIFRA
  pinMode (DIGIT3, OUTPUT);
  digitalWrite(DIGIT3, LOW);
  // quando sono configurati come ingressi i digit restano spenti
  pinMode (DIGIT1, INPUT);
  pinMode (DIGIT2, INPUT);
  pinMode (DIGIT4, INPUT);
  
  digitalWrite(SEG_A,  HIGH);
  digitalWrite(SEG_B,  HIGH);
  digitalWrite(SEG_C,  HIGH);
  digitalWrite(SEG_D,  HIGH);
  digitalWrite(SEG_E,  LOW);
  digitalWrite(SEG_F,  LOW);
  digitalWrite(SEG_G,  HIGH);
  digitalWrite(SEG_DP, LOW);
  delay(1); 
  digitalWrite(SEG_A,  LOW);
  digitalWrite(SEG_B,  LOW);
  digitalWrite(SEG_C,  LOW);
  digitalWrite(SEG_D,  LOW);
  digitalWrite(SEG_E,  LOW);
  digitalWrite(SEG_F,  LOW);
  digitalWrite(SEG_G,  LOW);
  digitalWrite(SEG_DP, LOW);

  // 4 CIFRA A DESTRA
  pinMode (DIGIT4, OUTPUT);
  digitalWrite(DIGIT4, LOW);
  // quando sono configurati come ingressi i digit restano spenti
  pinMode (DIGIT1, INPUT);
  pinMode (DIGIT2, INPUT);
  pinMode (DIGIT3, INPUT);
  
  digitalWrite(SEG_A,  HIGH);
  digitalWrite(SEG_B,  HIGH);
  digitalWrite(SEG_C,  HIGH);
  digitalWrite(SEG_D,  HIGH);
  digitalWrite(SEG_E,  HIGH);
  digitalWrite(SEG_F,  HIGH);
  digitalWrite(SEG_G,  HIGH);
  digitalWrite(SEG_DP, HIGH);
  delay(1); 
  digitalWrite(SEG_A,  LOW);
  digitalWrite(SEG_B,  LOW);
  digitalWrite(SEG_C,  LOW);
  digitalWrite(SEG_D,  LOW);
  digitalWrite(SEG_E,  LOW);
  digitalWrite(SEG_F,  LOW);
  digitalWrite(SEG_G,  LOW);
  digitalWrite(SEG_DP, LOW);

}
