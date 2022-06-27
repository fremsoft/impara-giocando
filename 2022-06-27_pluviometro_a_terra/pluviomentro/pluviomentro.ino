/*
 * Pluviometro fatto con due chiondi conficcati nel terreno
 * con una resistenza di pull-up da 10 kOhm si ricavano questi valori:
 * 
 * terra secca = 1023
 * terra umida 250 ÷ 500 (circa)
 * terra molto bagnata < 250 
 * 
 * Visualizza l'esperienza di laboratorio completa: 
 * https://youtu.be/gZPlRGBh0J8
 *  
 */


void setup() {

  Serial.begin( 9600 );

  // su analog input A0 misuro la resistenza del terreno
  // usando una resistenza di PullUp da 10kOhm per fare 
  // un partitore di tensione, non serve dichiararlo qui

  pinMode( LED_BUILTIN, OUTPUT );
  
}

void loop() {
  int secchezza_del_terreno;

  secchezza_del_terreno = analogRead(A0);
  Serial.println( secchezza_del_terreno );

  if ( secchezza_del_terreno > 500 ) {
    // TERRA SECCA
    digitalWrite( LED_BUILTIN, LOW );
  }
  else {
    // TERRA BAGNATA (dalla pioggia)
    digitalWrite( LED_BUILTIN, HIGH );
  }  
  
  delay( 100 );
}
