/*
 * Interruttore crepuscolare fatto con un partitore di tensione
 * composto da un Fotoresistore (pull-up) e 10kohm (pull-down)
 * connesso all'ingresso analogico A0.
 * 
 * Vedi "datalog.txt"
 * 
 * Visualizza l'esperienza di laboratorio completa: 
 * https://youtu.be/j3MMkOX6ySo
 *  
 */

const float k_filtro        = 100.0;
const float soglia_scatto   = 200.0;
const float soglia_rilascio = 150.0;

float luce_filtrata;
bool  interruttore_crepuscolare;

unsigned long t_alba;
unsigned long t_tramonto;
unsigned long t_giorno;
unsigned long t_mezzanotte;


#define K_10SEC_MS        10000
#define K_12ORE_MS     43200000L

#define OUT_INTERRUTTORE LED_BUILTIN

void setup() {
  
  Serial.begin( 9600 );

  /* Non serve inizializzare l'ingresso analogico A0 */

  pinMode( OUT_INTERRUTTORE, OUTPUT );

  /* Azzero variabili globali */
  luce_filtrata = 0.0;
  interruttore_crepuscolare = false;

  t_alba       = 0;
  t_tramonto   = 0;
  t_giorno     = 0;
  t_mezzanotte = 0;
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
  
  // read three sensors and append to the string:
  int luce = analogRead( A0 );
  dataString += String(luce);

  luce_filtrata = (( luce_filtrata * k_filtro ) + ((float)luce)) / (k_filtro + 1.0);
  dataString += ",";
  dataString += String(luce_filtrata);

  if ( !interruttore_crepuscolare ) {
    /* deve ancora scattare */
    if (luce_filtrata > soglia_scatto) {
      interruttore_crepuscolare = true;

      t_alba = millis();
      t_mezzanotte = (t_alba/2) + (t_tramonto/2);
    }    

    dataString += ",0";
  }
  else {
    /* l'interruttore deve rilasciarsi */
    if (luce_filtrata < soglia_rilascio) {
      interruttore_crepuscolare = false;

      t_tramonto = millis();
      t_giorno   = (t_tramonto - t_alba);
    }    

    dataString += ",1000";
  }

  dataString += ",";
  dataString += t_giorno;

  if ( t_giorno < K_12ORE_MS ) {
    /* siamo in autunno o in inverno */
    /* quindi non si deve irrigare   */
    digitalWrite( OUT_INTERRUTTORE, LOW );
    
    dataString += ",AUTUNNO/INVERNO";
  } 
  else {
    /* siamo in primavera o in estate */
    /* quindi bisogna irrigare */
    digitalWrite( OUT_INTERRUTTORE, interruttore_crepuscolare );
    
    dataString += ",PRIMAVERA/ESTATE";
  } 
  
  Serial.println(dataString);

  delay(K_10SEC_MS);
}
