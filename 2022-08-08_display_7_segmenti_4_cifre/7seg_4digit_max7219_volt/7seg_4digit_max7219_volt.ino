/* 
 * Programma di test per verificare il funzionamento del
 * driver per 8 display 7-segmenti o display a matrice di 
 * punti 8x8, MAX7219. 
 * 
 * Questo programma comanda un display 5461AS (4 cifre catodo comune)
 * 
 * Visualizza l'esperienza di laboratorio completa: 
 * https://youtu.be/vYJxRcf4lOo
 * 
 */


#define MAX7219_CLK   8 /* CLOCK : campionamento sul fronte di salita */
#define MAX7219_CS    9 /* LOAD : salvataggio dei dati sul fronte di salita */
#define MAX7219_DIN  10 /* DATA : dati seriali MSB first */ 


#define REG_DECODE_BCD   0x09
#define REG_INTENSITY    0x0A
#define REG_SCAN_LIMIT   0x0B
#define REG_SHUTDOWN     0x0C
#define REG_TEST         0x0F



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

  Serial.begin (9600);
  
  pinMode( MAX7219_DIN, OUTPUT );
  pinMode( MAX7219_CLK, OUTPUT );
  pinMode( MAX7219_CS,  OUTPUT );

  digitalWrite( MAX7219_CLK, LOW );
  digitalWrite( MAX7219_CS,  HIGH );  

  for (int r=1; r<=8; r++ ) { sendByte( r, 0 ); } /* azzero tutti i caratteri */
  
  sendByte( REG_DECODE_BCD, 0x0F ); /* modalità bit=led (BCD) per le prime 4 cifre/righe */
  sendByte( REG_INTENSITY,  3 ); /* intensità media */
  sendByte( REG_SCAN_LIMIT, 3 ); /* attive solo 4 cifre */
  sendByte( REG_SHUTDOWN,   1 ); /* display attivo */
  sendByte( REG_TEST,       0 ); /* no modalità test */

  sendByte( 1, 0x0F );           /* spengo la cifra LSB */
  sendByte( 2, 0x0F );           /* spengo la seconda cifra */
  sendByte( 3, 0x0F );           /* spengo la terza cifra */
  sendByte( 4, 0x0F );           /* spengo la cifra MSB */
  
}


void loop() {

  static float v_an0_filtrata = 0;
  float v_an0 = (5.0 * analogRead( A0 )) / 1023.0;
  
  v_an0_filtrata = ((v_an0_filtrata * 9.0) + v_an0) / 10.0;
  
  int an0 = (int)(v_an0_filtrata * 1000.0);
  char _7seg[4] = { 0x0f, 0x0f, 0x0f, 0x0f };

  /* lettura del valore */
  Serial.println( v_an0_filtrata );

  /* rendering della stringa */
  _7seg[0] = an0 % 10;
  an0 = an0 / 10;
  _7seg[1] = an0 % 10;
  an0 = an0 / 10;
  _7seg[2] = an0 % 10;
  an0 = an0 / 10;
  _7seg[3] = an0 % 10; /* NON SERVIREBBE "% 10" perche al massimo ho 5V */

  /* aggiungo il punto decimale */
  _7seg[3] = _7seg[3] | 0x80;
    
  /* visualizza 1234 */
  sendByte( 1, _7seg[0] );    
  sendByte( 2, _7seg[1] );    
  sendByte( 3, _7seg[2] );    
  sendByte( 4, _7seg[3] );    
  
  delay( 100 );
}
