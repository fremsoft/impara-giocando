/* Questo sketch configura i 6 bit MSB del PORT-D per generare 
 *  segnali analogici con convertitore DIGITALE-ANALOGICO 6-bit
 *  su CH1 dell'oscilloscopio e configura i 6 bit LSB del PORT-B 
 *  per generare segnali analogici con DAC 6-bit su CH2.
 *  
 *  Visualizza l'esperienza di laboratorio completa: 
 *  https://youtu.be/x8drnUEzlVc
 *   
 */

#define N_PUNTI  62

int ch1, ch2;
int disegno[N_PUNTI][2]={
  {27,20}, {23,20}, {19,21}, {17,25}, {18,28},
  {20,32}, {18,38}, {17,43}, {17,50}, {19,55},
  {20,56}, {23,55}, {25,52}, {27,45}, {28,33},
  {29,40}, {30,46}, {34,53}, {36,53}, {38,50},
  {38,45}, {36,35}, {35,32}, {37,30}, {38,27},
  {38,23}, {35,21}, {27,20}, {30,12}, {37, 8},
  {45, 8}, {37, 8}, {33, 7}, {33, 5}, {40, 2},
  {44, 3}, {45, 5}, {47, 4}, {59, 4}, {57, 7},
  {55,10}, {52,11}, {49, 8}, {45, 8}, {49, 8},
  {52,11}, {55,15}, {55,17}, {54,20}, {55,17},
  {57,17}, {60,20}, {60,23}, {57,25}, {53,23},
  {54,20}, {51,25}, {45,28}, {40,28}, {38,27},
  {38,23}, {35,21}, /*{27,20}, {25,28}, {27,20},
  {30,29}*/
};

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

  ch1 = 0;
  ch2 = 0;
}

void loop()
{
  int n;

  for( n=0; n<N_PUNTI; n++)
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
}
