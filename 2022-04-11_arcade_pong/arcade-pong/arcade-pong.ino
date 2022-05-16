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
 * 4) https://youtu.be/dZbgcdEF2_o
 * 5) https://youtu.be/Cs4E_jhcFlY
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

/* Trasmette un generico Registro a MAX7219 */
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
  int old_x;
  int old_y;
  int vel_x;
  int vel_y;
  int visibile;
} giocatore_a, giocatore_b, pallina;

void render() {
  int xSprite, ySprite, xBuffer, yBuffer;
  
  /* cancella il buffer */
  for (int n=0; n<8; n++) { buffer[n] = 0; }
  
  /* posizionamento del primo sprite : paletta */
  if (giocatore_a.visibile != 0) {
    for (ySprite=0, yBuffer=giocatore_a.y; ySprite<PLAYER_HEIGHT; ) {
      if ( (yBuffer >= 0) && (yBuffer < 8) ) { /* controllo integrita Y */
        for (xSprite=0, xBuffer=giocatore_a.x; xSprite<PLAYER_WIDTH; ) {
          if ( (xBuffer >= 0) && (xBuffer < 8) ) { /* controllo integrita X */
            if ( spritePaletta[ySprite][xSprite] != 0 ) {
              bitSet ( buffer[7-xBuffer], (7 - yBuffer));
            }
          }
          xSprite++; xBuffer++;      
        }
      }
      ySprite++; yBuffer++;
    }
  }
  
  /* posizionamento secondo sprite : paletta */
  if ( giocatore_b.visibile != 0) {
    for (ySprite=0, yBuffer=giocatore_b.y; ySprite<PLAYER_HEIGHT; ) {
      if ( (yBuffer >= 0) && (yBuffer < 8) ) { /* controllo integrita Y */
        for (xSprite=0, xBuffer=giocatore_b.x; xSprite<PLAYER_WIDTH; ) {
          if ( (xBuffer >= 0) && (xBuffer < 8) ) { /* controllo integrita X */
            if ( spritePaletta[ySprite][xSprite] != 0 ) {
              bitSet ( buffer[7-xBuffer], (7 - yBuffer));
            }
          }
          xSprite++; xBuffer++;      
        }
      }
      ySprite++; yBuffer++;
    }
  }
  
  /* posizionamento terzo sprite : pallina */ 
  if (pallina.visibile != 0) {
    for (ySprite=0, yBuffer=pallina.y; ySprite<BALL_HEIGHT; ) {
      if ( (yBuffer >= 0) && (yBuffer < 8) ) { /* controllo integrita Y */
        for (xSprite=0, xBuffer=pallina.x; xSprite<BALL_WIDTH; ) {
          if ( (xBuffer >= 0) && (xBuffer < 8) ) { /* controllo integrita X */
            if ( spritePallina[ySprite][xSprite] != 0 ) {
              bitSet ( buffer[7-xBuffer], (7 - yBuffer));
            }
          }
          xSprite++; xBuffer++;      
        }
      }
      ySprite++; yBuffer++;
    }
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
    delayMicroseconds( 1 );
    digitalWrite( MAX7219_CLK, HIGH );
    delayMicroseconds( 1 );
    digitalWrite( MAX7219_CLK, LOW );
    delayMicroseconds( 1 );
  }
  
  digitalWrite( MAX7219_CS, HIGH );
  delayMicroseconds( 1 ); 
}


/* GESTIONE DEL SUONO CON BUZZER PASSIVO */ 

#define   BUZZER              4
#define   TONO_BATTUTA_HZ   400
#define   TONO_BATTUTA_MS    50
#define   TONO_PUNTO_HZ    1000
#define   TONO_PUNTO_MS     500


/*
   Stato del gioco: 
   1 = attesa che il giocatore si muova per iniziare
   2 = gioco in corso
   3 = pallina fuori dal campo di gioco
*/
int stato;
int giocatoreIniziale;
unsigned long ultimoTempoMs;

#define DELTA_T_GIOCO_MS      200
#define DELTA_T_PUNTO_MS     1000
#define DELTA_T_LAMPEGGIO_MS  200

void setup() {

  Serial.begin( 9600 );
  
  pinMode( MAX7219_CLK, OUTPUT );
  digitalWrite( MAX7219_CLK, LOW );
  
  pinMode( MAX7219_CS, OUTPUT );
  digitalWrite( MAX7219_CS, HIGH );
  
  pinMode( MAX7219_DIN, OUTPUT );

  pinMode ( BUZZER, OUTPUT );
  noTone( BUZZER );


  /* inizializzazione MAX7219 */
  sendByte( REG_DECODE_BCD, 0 ); /* modalità bit=led (no BCD) per tutte 8 le righe */
  sendByte( REG_INTENSITY,  2 ); /* intensità media */
  sendByte( REG_SCAN_LIMIT, 7 ); /* attive 8 righe */
  sendByte( REG_SHUTDOWN,   1 ); /* display attivo */
  sendByte( REG_TEST,       0 ); /* no modalità test */
   
  /* reset buffer */
  for (int n=0; n<8; n++) { buffer[n] = 0; }
  
  /* posizioni di gioco iniziali */
  giocatore_a.x = 0; giocatore_a.y = 2; /* vel non ci interessa */
  giocatore_b.x = 7; giocatore_b.y = 3; /* vel non ci interessa */
  pallina.x = 3;     pallina.y = 4;
  pallina.vel_x = 0; pallina.vel_y = 0;
  
  giocatore_a.visibile = 1;
  giocatore_b.visibile = 1;
  pallina.visibile = 1;
  
  stato = 0; 
  giocatoreIniziale = 1;  
}

void loop() {
  
  /* visualizzazione */
  render();  
  for (int r=0; r<8; r++) { sendBuffer( r ); }
    
  
  /* gestione degli ingressi */
  
  /* THINKERCAD               :    512 = alto; 159 = basso */
  /* POTENZIOMETRO o JOYSTICK :   1023 = alto;   0 = basso*/
#ifdef THINKERCAD  
  giocatore_a.y = map( analogRead( A0 ), 512, 159, 0, 8 - PLAYER_HEIGHT );
  giocatore_b.y = map( analogRead( A1 ), 512, 159, 0, 8 - PLAYER_HEIGHT );
#else
  giocatore_a.y = map( analogRead( A0 ), 1023, 100, 0, 8 - PLAYER_HEIGHT );
  giocatore_b.y = map( analogRead( A1 ), 1023, 100, 0, 8 - PLAYER_HEIGHT );
#endif

  
  /* debug */
  
  /* Serial.println( analogRead( A0 ) ); */
  Serial.println( stato );
  
   
  /* elaborazione dello stato del gioco */
  
  switch( stato ) {
    case 1:  /* 1 = attesa che il giocatore si muova per iniziare */
      giocatore_a.visibile = 1;
      giocatore_b.visibile = 1;
      pallina.visibile = 1;
  
      if ( giocatoreIniziale == 1) {
        pallina.x = PLAYER_WIDTH;
        pallina.y = giocatore_a.y+1;
        
        if ( giocatore_a.y != giocatore_a.old_y) {
          /* il giocatore A si è mosso e può iniziare la partita*/

          tone( BUZZER, TONO_BATTUTA_HZ, TONO_BATTUTA_MS );
          
          pallina.vel_x = 1;
          if ( giocatore_a.y > giocatore_a.old_y ) {
            pallina.vel_y = 1;
          }
          else {
            pallina.vel_y = -1;
          }
            
          ultimoTempoMs = millis();
          stato = 2; 
        }
      }
      else /* if ( giocatoreIniziale == 2) */ {
        pallina.x = 7-PLAYER_WIDTH;
        pallina.y = giocatore_b.y+1;
      
        if ( giocatore_b.y != giocatore_b.old_y) {
          /* il giocatore B si è mosso e può iniziare la partita*/

          tone( BUZZER, TONO_BATTUTA_HZ, TONO_BATTUTA_MS );
          
          pallina.vel_x = -1;
          if ( giocatore_b.y > giocatore_b.old_y ) {
            pallina.vel_y = 1;
          }
          else {
            pallina.vel_y = -1;
          }
          
          ultimoTempoMs = millis();
          stato = 2;
        }
      }
      break;  
    
    case 2: /* 2 = gioco in corso */
      /* aspetto che trascorra un certo delta t */
      if ( millis() > (ultimoTempoMs + DELTA_T_GIOCO_MS) ) {
      
        /* movimentazione pallina */
        /* calcolo posizione teorica */
        pallina.x = pallina.x + pallina.vel_x;
        pallina.y = pallina.y + pallina.vel_y;

        /* gestione collisioni Y */
        if (pallina.y >= 8) {
          pallina.vel_y = -1;
          pallina.y     = 6;
        }
        else if (pallina.y < 0) {
          pallina.vel_y = 1;
          pallina.y     = 1;
        }

        /* gestione collisioni X */
        if (pallina.x >= 7) {
          /* devo verificare se c'è la paletta B */
          if (
               (pallina.y >= giocatore_b.y)
              &&
               (pallina.y < (giocatore_b.y + PLAYER_HEIGHT))
             )
          {
            /* il giocatore B ha colpito la pallina */
            pallina.vel_x = -1;
            pallina.x    -= 2;

            tone( BUZZER, TONO_BATTUTA_HZ, TONO_BATTUTA_MS );
          }
          else
          {
            pallina.vel_x = 0;
            pallina.vel_y = 0;
            stato = 3;

            tone( BUZZER, TONO_PUNTO_HZ, TONO_PUNTO_MS );
          }
        }
        if (pallina.x <= 0) {
          /* devo verificare se c'è la paletta A */
          if (
               (pallina.y >= giocatore_a.y)
              &&
               (pallina.y < (giocatore_a.y + PLAYER_HEIGHT))
             )
          {
            /* il giocatore A ha colpito la pallina */      
            pallina.vel_x = 1;
            pallina.x    += 2;

            tone( BUZZER, TONO_BATTUTA_HZ, TONO_BATTUTA_MS );
          }
          else
          {
            pallina.vel_x = 0;
            pallina.vel_y = 0;
            stato = 3;

            tone( BUZZER, TONO_PUNTO_HZ, TONO_PUNTO_MS );
          }    
        }        
        
        ultimoTempoMs = millis();  
      } 
      break;
    
    case 3: /* 3 = pallina fuori dal campo di gioco */
      if (millis() < (ultimoTempoMs + DELTA_T_PUNTO_MS)) {
        /* lampeggia il pallino */   
        if (millis()%DELTA_T_LAMPEGGIO_MS > (DELTA_T_LAMPEGGIO_MS/2)) {
          if (pallina.visibile != 0) { pallina.visibile = 0; }
          else { pallina.visibile = 1; }
        }
      }
      else {     
        if (pallina.x >= 7) { giocatoreIniziale = 1; }
        if (pallina.x <= 0) { giocatoreIniziale = 2; }
        stato = 1;      
      }   
      break;
    
    default: 
      stato = 1; 
      break;
  }
  
  giocatore_a.old_y = giocatore_a.y;
  giocatore_b.old_y = giocatore_b.y;
}
