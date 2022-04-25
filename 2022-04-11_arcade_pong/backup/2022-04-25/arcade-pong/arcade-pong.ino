/* 
 * Questo programma per Arduino UNO serve a realizzare
 * il gioco del PONG, utilizzando due Joystick analogici
 * per muovere le palette di destra e di sinistra, 
 * utilizzando come schermo un display DOT-MATRIX  8x8
 * a LED basato su controller MAX7219.
 * 
 * Si tratta di un videogame dimostrativo a scopo didattico.
 * 
 * L'idea di creare questo gioco è sorta vedendo un video 
 * su Facebook in cui veniva ritratto un videogame fatto 
 * come descritto sopra.
 * 
 * Visualizza l'esperienza di laboratorio completa: 
 * 1) https://youtu.be/Ptr_G2O8gbQ
 * 2) https://youtu.be/bSmhxYcj3xs
 * 
 */

#define MAX7219_CLK   8 /* CLOCK : campionamento sul fronte di salita */
#define MAX7219_CS    9 /* LOAD : salvataggio dei dati sul fronte di salita */
#define MAX7219_DIN  10 /* DATA : dati seriali MSB first */ 

char buffer[8];

void sendBuffer(int n) {
  
  unsigned int raw;
  
  /* 0000 nnnn dddddddd */
  raw = (buffer[n] & 0xFF)  | (((n + 1) & 0x0F) << 8);
   
  digitalWrite( MAX7219_CS, LOW );
  
  /* invio Buffer RAW 16 bit */
  for (signed int n=15; n>=0; n--) {
    digitalWrite( MAX7219_DIN, bitRead( raw, n ) );
    delay( 1 );
    digitalWrite( MAX7219_CLK, HIGH );
    delay( 1 );
    digitalWrite( MAX7219_CLK, LOW );
    delay( 1 );
  }
  
  digitalWrite( MAX7219_CS, HIGH );
  delay( 1 );
  
}

void setup() {
  
  pinMode( MAX7219_CLK, OUTPUT );
  digitalWrite( MAX7219_CLK, LOW );
  
  pinMode( MAX7219_CS, OUTPUT );
  digitalWrite( MAX7219_CS, HIGH );
  
  pinMode( MAX7219_DIN, OUTPUT );
    
  buffer[0] = 0b00110101;
  buffer[1] = 0b11001010;
  buffer[2] = 0b00000000;
  buffer[3] = 0b11111111;
  buffer[4] = 0b10000001;
  buffer[5] = 0b01000010;
  buffer[6] = 0b00100100;
  buffer[7] = 0b00011000;

}

void loop() {
  
  sendBuffer( 0 );
  sendBuffer( 1 );
  sendBuffer( 2 );
  sendBuffer( 3 );
  sendBuffer( 4 );
  sendBuffer( 5 );
  sendBuffer( 6 );
  sendBuffer( 7 );
  
}
