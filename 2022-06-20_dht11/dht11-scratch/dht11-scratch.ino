/*
 * Come leggere i valori di temperatura e umidità dal
 * DHT11, senza usare le librerie.
 * 
 * Visualizza l'esperienza di laboratorio completa: 
 * https://youtu.be/O72t-QcfDvM
 *  
 */

#define DHTPIN              2
#define DHTTYPE         DHT11

#define TIMEOUT_DHT_MS      2

float temperatura, umidita;

void setup() {

  Serial.begin( 9600 );

  pinMode( DHTPIN, INPUT );

}

void eseguiLettura() {

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


void loop() {

  eseguiLettura();

  Serial.print ( "Temperatura: " );
  Serial.print ( temperatura );
  Serial.print ( "°C, Umidità: " );
  Serial.print ( umidita );
  Serial.println( "%" );
  
  delay (2000);

}
