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
 * 3) https://youtu.be/mzQGpVoaoDQ
 * 
 */
 

#define MAX7219_CLK   8 /* CLOCK : campionamento sul fronte di salita */
#define MAX7219_CS    9 /* LOAD : salvataggio dei dati sul fronte di salita */
#define MAX7219_DIN  10 /* DATA : dati seriali MSB first */ 

unsigned char buffer[8];


/*
   Definizione degli sprites 
   
   il giocatore A è composto da tre led in verticale 
   si muove sulla colonna 0 (a sinistra) ed è vincolato
   a muoversi da y=0 a y=5 (8-h)
   
   il giocatore B è composto da tre led in verticale 
   si muove sulla colonna 7 (a destra) ed è vincolato
   a muoversi da y=0 a y=5 (8-h)
   
   la pallina è rappresentata da un solo led 
   si muove in tutto lo schermo liberamente e quando 
   incontra un giocatore (una paletta) deve rimbalzare, 
   se incontra il fondale termina la manche
*/

#define PLAYER_WIDTH   1
#define PLAYER_HEIGHT  3

#define BALL_WIDTH   1
#define BALL_HEIGHT  1

const int spritePaletta[PLAYER_HEIGHT][PLAYER_WIDTH] = { { 1 }, { 1 }, { 1 } };
const int spritePallina[BALL_HEIGHT][BALL_WIDTH]={ { 1 } };

struct {
  int x;
  int y;
} giocatore_a, giocatore_b, pallina;

void render() {
  int xSprite, ySprite, xBuffer, yBuffer;
  
  /* cancella il buffer */
  for (int n=0; n<8; n++) { buffer[n] = 0; }
  
  /* posizionamento del primo sprite : paletta */
  for (ySprite=0, yBuffer=giocatore_a.y; ySprite<PLAYER_HEIGHT; ) {
    if ( (yBuffer >= 0) && (yBuffer < 8) ) { /* controllo integrita Y */
      for (xSprite=0, xBuffer=giocatore_a.x; xSprite<PLAYER_WIDTH; ) {
        if ( (xBuffer >= 0) && (xBuffer < 8) ) { /* controllo integrita X */
          if ( spritePaletta[ySprite][xSprite] != 0 ) {
            bitSet ( buffer[yBuffer], (7 - xBuffer));
          }
        }
        xSprite++; xBuffer++;      
      }
    }
    ySprite++; yBuffer++;
  }
  
  /* posizionamento secondo sprite : paletta */
  for (ySprite=0, yBuffer=giocatore_b.y; ySprite<PLAYER_HEIGHT; ) {
    if ( (yBuffer >= 0) && (yBuffer < 8) ) { /* controllo integrita Y */
      for (xSprite=0, xBuffer=giocatore_b.x; xSprite<PLAYER_WIDTH; ) {
        if ( (xBuffer >= 0) && (xBuffer < 8) ) { /* controllo integrita X */
          if ( spritePaletta[ySprite][xSprite] != 0 ) {
            bitSet ( buffer[yBuffer], (7 - xBuffer));
          }
        }
        xSprite++; xBuffer++;      
      }
    }
    ySprite++; yBuffer++;
  }
  
  /* posizionamento terzo sprite : pallina */ 
  for (ySprite=0, yBuffer=pallina.y; ySprite<BALL_HEIGHT; ) {
    if ( (yBuffer >= 0) && (yBuffer < 8) ) { /* controllo integrita Y */
      for (xSprite=0, xBuffer=pallina.x; xSprite<BALL_WIDTH; ) {
        if ( (xBuffer >= 0) && (xBuffer < 8) ) { /* controllo integrita X */
          if ( spritePallina[ySprite][xSprite] != 0 ) {
            bitSet ( buffer[yBuffer], (7 - xBuffer));
          }
        }
        xSprite++; xBuffer++;      
      }
    }
    ySprite++; yBuffer++;
  }
}

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

  Serial.begin( 9600 );
  
  pinMode( MAX7219_CLK, OUTPUT );
  digitalWrite( MAX7219_CLK, LOW );
  
  pinMode( MAX7219_CS, OUTPUT );
  digitalWrite( MAX7219_CS, HIGH );
  
  pinMode( MAX7219_DIN, OUTPUT );
    
  /* reset buffer */
  for (int n=0; n<8; n++) { buffer[n] = 0; }

  /* posizioni di gioco iniziali */
  giocatore_a.x = 0; giocatore_a.y = 2;
  giocatore_b.x = 7; giocatore_b.y = 3;
  pallina.x = 3;     pallina.y = 4;
  
}

void loop() {
  
  render();  
  for (int r=0; r<8; r++) { sendBuffer( r ); }
    
  /* 512= alto; 159 = basso */
  giocatore_a.y = map( analogRead( A0 ), 512, 159, 0, 8 - PLAYER_HEIGHT );
  giocatore_b.y = map( analogRead( A1 ), 512, 159, 0, 8 - PLAYER_HEIGHT );
  
  Serial.println( giocatore_a.y );
    
}
