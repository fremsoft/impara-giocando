/* 
 * Programma di test per mostrare alcuni caratteri dell'alfabeto
 * su display a matrice di punti 8x8 mediante MAX7219. 
 * 
 * Visualizza l'esperienza di laboratorio completa: 
 * https://youtu.be/...
 */


#define MAX7219_CLK   8 /* CLOCK : campionamento sul fronte di salita */
#define MAX7219_CS    9 /* LOAD : salvataggio dei dati sul fronte di salita */
#define MAX7219_DIN  10 /* DATA : dati seriali MSB first */ 



#define REG_DECODE_BCD   0x09
#define REG_INTENSITY    0x0A
#define REG_SCAN_LIMIT   0x0B
#define REG_SHUTDOWN     0x0C
#define REG_TEST         0x0F

const char CAR_A[] = { 0b00000000, 
                       0b00111100, 
                       0b01000010, 
                       0b01000010, 
                       0b01111110, 
                       0b01000010, 
                       0b01000010, 
                       0b00000000 };

const char CAR_b[] = { 0b00000000, 
                       0b01000000, 
                       0b01000000, 
                       0b01000000, 
                       0b01111000, 
                       0b01100100, 
                       0b01011000, 
                       0b00000000 };

const char CAR_C[] = { 0b00000000, 
                       0b00111110, 
                       0b01111110, 
                       0b01100000, 
                       0b01100000, 
                       0b01111110, 
                       0b00111110, 
                       0b00000000 };

void sendChar(const char *c) {

  for (int i=0; i<8; i++) {
    sendByte( i+1, c[i] ); 
  }
  
}


void sendByte(int address, int data) {

  unsigned int raw;
  signed int i;

  raw = ((address & 0x0F) << 8) | (data & 0xFF);
  
  digitalWrite( MAX7219_CS,  LOW );

  for (i=15; i>=0; i--) {

    digitalWrite( MAX7219_DIN, bitRead(raw, i) );
    delayMicroseconds(1);
    digitalWrite( MAX7219_CLK, HIGH );
    digitalWrite( MAX7219_CLK, LOW );
  
  }
  
  digitalWrite( MAX7219_CS,  HIGH );  
 
}

void setup() {

  pinMode( MAX7219_DIN, OUTPUT );
  pinMode( MAX7219_CLK, OUTPUT );
  pinMode( MAX7219_CS,  OUTPUT );

  digitalWrite( MAX7219_CLK, LOW );
  digitalWrite( MAX7219_CS,  HIGH );  

  for (int r=1; r<=8; r++ ) { sendByte( r, 0 ); } /* azzero tutti i caratteri */
  
  sendByte( REG_DECODE_BCD, 0 ); /* modalità bit=led (no BCD) per tutte 8 le righe */
  sendByte( REG_INTENSITY,  8 ); /* intensità media */
  sendByte( REG_SCAN_LIMIT, 7 ); /* attive 8 righe */
  sendByte( REG_SHUTDOWN,   1 ); /* display attivo */
  sendByte( REG_TEST,       0 ); /* no modalità test */
  
}

void loop() {

  sendChar( CAR_A );
  delay( 1500 );

  sendChar( CAR_b );
  delay( 1500 );

  sendChar( CAR_C );
  delay( 1500 );


}
