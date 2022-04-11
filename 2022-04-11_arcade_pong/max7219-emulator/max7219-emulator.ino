/* 
 * Questo programma per Arduino UNO serve a emulare 
 * un controller MAX7219, utilizzato per accendere 
 * i LED di display molto grandi, in modo multiplato.
 * 
 * I comandi provengono dalla linea SPI da un altro 
 * Arduino UNO.
 * 
 * Visualizza l'esperienza di laboratorio completa: 
 * https://youtu.be/Ptr_G2O8gbQ
 */

#define  R_1     9
#define  R_2     8
#define  R_3     7
#define  R_4     6
#define  R_5     5
#define  R_6     4
#define  R_7     1
#define  R_8     0

#define  C_1    11
#define  C_2    10
#define  C_3    19
#define  C_4    18
#define  C_5    17
#define  C_6    16
#define  C_7    15
#define  C_8    14


#define  DIN    12
#define  CLK    3
#define  LOAD   2


char buffer[8];
volatile unsigned int registro_16bit;

void caricamentoRegistroScorrimento() {
  /* caricamento del bit LSB presente in DIN */
  registro_16bit = (registro_16bit << 1);
  if (digitalRead(DIN) != 0) { 
    registro_16bit = registro_16bit | 1; 
  }
}


void setup() {
  
  pinMode (R_1, OUTPUT);
  pinMode (R_2, OUTPUT);
  pinMode (R_3, OUTPUT);
  pinMode (R_4, OUTPUT);
  pinMode (R_5, OUTPUT);
  pinMode (R_6, OUTPUT);
  pinMode (R_7, OUTPUT);
  pinMode (R_8, OUTPUT);
  
  pinMode (C_1, OUTPUT);
  pinMode (C_2, OUTPUT);
  pinMode (C_3, OUTPUT);
  pinMode (C_4, OUTPUT);
  pinMode (C_5, OUTPUT);
  pinMode (C_6, OUTPUT);
  pinMode (C_7, OUTPUT);
  pinMode (C_8, OUTPUT);
  
  digitalWrite (R_1, LOW);
  digitalWrite (R_2, LOW);
  digitalWrite (R_3, LOW);
  digitalWrite (R_4, LOW);
  digitalWrite (R_5, LOW);
  digitalWrite (R_6, LOW);
  digitalWrite (R_7, LOW);
  digitalWrite (R_8, LOW);
  
  digitalWrite (C_1, LOW);
  digitalWrite (C_2, LOW);
  digitalWrite (C_3, LOW);
  digitalWrite (C_4, LOW);
  digitalWrite (C_5, LOW);
  digitalWrite (C_6, LOW);
  digitalWrite (C_7, LOW);
  digitalWrite (C_8, LOW);
  
  registro_16bit = 0;
  
  pinMode(DIN, INPUT);
  pinMode(CLK, INPUT);
  pinMode(LOAD, INPUT);
  attachInterrupt(digitalPinToInterrupt(CLK), 
                  caricamentoRegistroScorrimento, 
                  RISING);
}


void frullaTutteLeColonne() {

  digitalWrite (C_1, HIGH);
  delay(100);
  digitalWrite (C_1, LOW);

  digitalWrite (C_2, HIGH);
  delay(100);
  digitalWrite (C_2, LOW);

  digitalWrite (C_3, HIGH);
  delay(100);
  digitalWrite (C_3, LOW);
  
  digitalWrite (C_4, HIGH);
  delay(100);
  digitalWrite (C_4, LOW);
  
  digitalWrite (C_5, HIGH);
  delay(100);
  digitalWrite (C_5, LOW);
  
  digitalWrite (C_6, HIGH);
  delay(100);
  digitalWrite (C_6, LOW);
  
  digitalWrite (C_7, HIGH);
  delay(100);
  digitalWrite (C_7, LOW);

  digitalWrite (C_8, HIGH);
  delay(100);
  digitalWrite (C_8, LOW);
  
}

void loop() {
  
  digitalWrite (R_1, HIGH);
  frullaTutteLeColonne();
  digitalWrite (R_1, LOW);

  digitalWrite (R_2, HIGH);
  frullaTutteLeColonne();
  digitalWrite (R_2, LOW);

  digitalWrite (R_3, HIGH);
  frullaTutteLeColonne();
  digitalWrite (R_3, LOW);

  digitalWrite (R_4, HIGH);
  frullaTutteLeColonne();
  digitalWrite (R_4, LOW);

  digitalWrite (R_5, HIGH);
  frullaTutteLeColonne();
  digitalWrite (R_5, LOW);

  digitalWrite (R_6, HIGH);
  frullaTutteLeColonne();
  digitalWrite (R_6, LOW);

  digitalWrite (R_7, HIGH);
  frullaTutteLeColonne();
  digitalWrite (R_7, LOW);

  digitalWrite (R_8, HIGH);
  frullaTutteLeColonne();
  digitalWrite (R_8, LOW);
}
  
