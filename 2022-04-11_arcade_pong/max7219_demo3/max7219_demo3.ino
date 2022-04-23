/* 
 * Programma di test per testare tutti i LED e modificare 
 * la luminosita' del display display a matrice di punti 8x8 
 * mediante MAX7219. 
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


char bitmap[8];
int row, col;
int intensity;


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

  row = 0;
  col = 0;
  intensity = 0;
}

void loop() {
  int i;
  
  for (int r=0; r<8; r++) {
    
    if ( r==row ) {

      bitmap[r] = 1 << col;
      
    } else {
      
      bitmap[r] = 0xFF;
    
    }

    sendByte( r+1, bitmap[r] );

    intensity++;
    i = (intensity >> 2) & 0x1F;
    if (i > 0x0F) { i = 0x20 - i - 1; }
    sendByte( REG_INTENSITY, i ); 
  }
  
  col++;
  if (col >= 8) { 
    col=0;
    row++;
    if (row >= 8) { row=0; }
  } 

  delay (50);

}
