/*
 * Centralina di irrigazione che gestisce:
 *  - interruttore crepuscolare fatto con un partitore 
 *    di tensione composto da un Fotoresistore (pull-up) 
 *    e 10kohm (pull-down) connesso all'ingresso analogico 
 *    A0. La soglia di scatto per l'alba è circa 200/1024
 *    
 *  - sensore di pioggia fatto con un resistore da 10kohm
 *    (pull-up) e da due chiodi conficcati nel terreno 
 *    collegati verso massa (pull-down). La soglia di 
 *    scatto per la pioggia è circa 200/1024
 *    NOTA: il sensore di pioggia va posizionato dove 
 *          non si deve irrigare
 *        
 *  - sensore di umidità e temperatura DHT11, senza usare 
 *    le librerie, collegato al pin 2
 *    
 * 
 * Visualizza l'esperienza di laboratorio completa: 
 * https://youtu.be/LmC222QxVow
 *  
 */

/* parametri e variabili del crepuscolare */
const float k_filtro_crepuscolare        = 100.0;
const float soglia_scatto_crepuscolare   = 200.0;
const float soglia_rilascio_crepuscolare = 150.0;

float luce_filtrata;
bool  interruttore_crepuscolare;

unsigned long t_alba;
unsigned long t_tramonto;
unsigned long t_giorno;
unsigned long t_mezzanotte;

int   giorno_n;

/* parametri e variabili del sensore di pioggia */
const float soglia_scatto_pluviometro   = 200.0;

/* parametri e variabili del sensore DHT11 */
#define DHTPIN              2
#define DHTTYPE         DHT11

#define TIMEOUT_DHT_MS      2

float temperatura, umidita;
float temperatura_somma, temperatura_media;
int   numero_campioni_temperatura;


#define K_10SEC_MS        10000
#define K_12ORE_MS     43200000L
#define K_10MIN_MS       600000L
#define K_20MIN_MS      1200000L
#define K_30MIN_MS      1800000L

#define SOGLIA_TEMPERATURA_MAX    30.0   /* gradi centigradi */
#define SOGLIA_TEMPERATURA_MEDIA  20.0   /* gradi centigradi */
#define SOGLIA_TEMPERATURA_MIN     5.0   /* gradi centigradi */

#define IN_CREPUSCOLARE    A0
#define IN_PLUVIOMETRO     A1

#define OUT_IRRIGATORE LED_BUILTIN


void eseguiLetturaDHT11() {

  int i;
  int n_bit;
  int value;
  unsigned char raw[5];

  unsigned long t;
  
  
  // Sequenza di start : tengo basso per almeno 18ms
  pinMode( DHTPIN, OUTPUT );
  digitalWrite( DHTPIN, LOW );
  delay( 19 );
  pinMode( DHTPIN, INPUT );

  // Buttiamo via il primo bit
  // aspetta che la linea dati vada a zero
  t = millis() + TIMEOUT_DHT_MS;
  while ( (digitalRead( DHTPIN ) != 0) && (millis() <= t) ) /* do nothing */;
      
  // aspetta il fronte di salita
  t = millis() + TIMEOUT_DHT_MS;
  while ( (digitalRead( DHTPIN ) == 0) && (millis() <= t) ) /* do nothing */;

  
  // ascolto 40 bit: [8bit RH%][8bit 1/10RH%][8bit T°C][8bit 1/10T°C][CHECKSUM]
  for (i=0; i<5; i++) {
    // lettura del byte i-esimo
    raw[i] = 0;
    
    for (n_bit=0; n_bit<8; n_bit++) {

      // aspetta che la linea dati vada a zero
      t = millis() + TIMEOUT_DHT_MS;
      while ( (digitalRead( DHTPIN ) != 0) && (millis() <= t) ) /* do nothing */;
      
      // aspetta il fronte di salita
      t = millis() + TIMEOUT_DHT_MS;
      while ( (digitalRead( DHTPIN ) == 0) && (millis() <= t) ) /* do nothing */;
      
      // aspetta 50uSec 
      delayMicroseconds(50);
      
      // lettura della linea dati
      value = digitalRead( DHTPIN );
      raw[i] = raw[i] << 1;
      if (value != 0) { raw[i] = raw[i] | 0x01; }
    }
  }
  
  // controllo checksum ed eventuale scrittura dei valori letti
  /*
  Serial.print (raw[0]);
  Serial.print (" ");
  Serial.print (raw[1]);
  Serial.print (" ");
  Serial.print (raw[2]);
  Serial.print (" ");
  Serial.print (raw[3]);
  Serial.print (" ");
  Serial.println(raw[4]);
  */

  if ( (raw[0] + raw[1] + raw[2] + raw[3]) == raw[4] ) {
    // la lettura è corretta
    temperatura = raw[2] + (0.1 * raw[3]);
    umidita     = raw[0] + (0.1 * raw[1]);;
  }
}


void setup() {
  
  Serial.begin( 9600 );

  /* Non serve inizializzare gli ingress1 analogici A0, A1 */

  pinMode( OUT_IRRIGATORE, OUTPUT );
  pinMode( DHTPIN, INPUT );

  /* Azzero variabili globali */
  luce_filtrata = 0.0;
  interruttore_crepuscolare = false;

  t_alba       = 0;
  t_tramonto   = 0;
  t_giorno     = 0;
  t_mezzanotte = 0;

  giorno_n     = 0;

  temperatura  = 0.0;
  umidita      = 0.0;
  temperatura_somma = 0.0;
  temperatura_media = 0.0;
  numero_campioni_temperatura = 0;
}

void loop() {
  unsigned long tt, hh, mm, ss; 

  // make a string for assembling the data to log:
  String dataString = "";
  char str[32];
  
  // calcolo il timestamp stimando la mezzanotte
  tt = (millis() - t_mezzanotte) % 86400000L; 
  
  ss = tt / 1000;
  mm = ss / 60;
  hh = mm / 60;

  ss = ss % 60;
  mm = mm % 60;

  sprintf(str, "%02d:%02d:%02d,", (int)hh, (int)mm, (int)ss);
  dataString += String(str);
  
  // lettura del valore di luce dal fotoresistore
  int luce = analogRead( IN_CREPUSCOLARE );
  dataString += String(luce);

  luce_filtrata = (( luce_filtrata * k_filtro_crepuscolare ) + ((float)luce)) / (k_filtro_crepuscolare + 1.0);
  dataString += ",";
  dataString += String(luce_filtrata);

  if ( !interruttore_crepuscolare ) {
    /* deve ancora scattare */
    if (luce_filtrata > soglia_scatto_crepuscolare) {
      interruttore_crepuscolare = true;

      t_alba = millis();
      t_mezzanotte = (t_alba/2) + (t_tramonto/2);
      giorno_n ++;

      temperatura_media = temperatura_somma / (float)numero_campioni_temperatura;
    }    

    dataString += ",0";
  }
  else {
    /* l'interruttore deve rilasciarsi */
    if (luce_filtrata < soglia_rilascio_crepuscolare) {
      interruttore_crepuscolare = false;

      t_tramonto = millis();
      t_giorno   = (t_tramonto - t_alba);
    }    

    dataString += ",1000";
  }

  dataString += ",";
  dataString += t_giorno;

  int pioggia = analogRead( IN_PLUVIOMETRO ); /* logica negativa */
  dataString += ",";
  dataString += pioggia;

  eseguiLetturaDHT11(); 
  dataString += ",";
  dataString += temperatura;
  dataString += ",";
  dataString += umidita;

  temperatura_somma += temperatura;
  numero_campioni_temperatura ++;

  bool irrigare = false;
  if ( t_giorno < K_12ORE_MS ) {
    /* siamo in autunno o in inverno */
    /* quindi non si deve irrigare   */
    irrigare = false;    
    dataString += ",AUTUNNO/INVERNO";
  } 
  else {
    /* siamo in primavera o in estate */
    /* quindi bisogna irrigare */

    /* ma solo se non è piovuto */
    if ( pioggia > soglia_scatto_pluviometro ) {
      /* la terra e' secca e ha bisogno di essere irrigata */
      
      if (temperatura_media > SOGLIA_TEMPERATURA_MAX) {
        /* dobbiamo irrigare tutti i giorni per 30 minuti */
        if ((millis() - t_alba) < K_30MIN_MS) { irrigare = true; }
      }
      else if (temperatura_media > SOGLIA_TEMPERATURA_MEDIA) {
        /* dobbiamo irrigare ogni 2 giorni per 20 minuti */
        if ((giorno_n % 2) == 0) {
          if ((millis() - t_alba) < K_20MIN_MS) { irrigare = true; }  
        }        
      }
      else if (temperatura_media > SOGLIA_TEMPERATURA_MIN) {
        /* dobbiamo irrigare ogni 3 giorni per 10 minuti */
        if ((giorno_n % 3) == 0) {
          if ((millis() - t_alba) < K_10MIN_MS) { irrigare = true; }  
        }        
      }
    }
    dataString += ",PRIMAVERA/ESTATE";
  } 

  digitalWrite( OUT_IRRIGATORE, irrigare );

  Serial.println(dataString);

  delay(K_10SEC_MS);
}
