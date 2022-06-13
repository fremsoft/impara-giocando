/*
 * Come estrarre un valore di temperatura da un termistore 
 * interpolando con curva esponenziale da una tabella di 
 * valori ricavati empiricamente.
 * 
 * Visualizza l'esperienza di laboratorio completa: 
 * https://youtu.be/rewihSIK1NY
 *  
 */

int sensorPin     = A0;      
int ledPin        = 13;      
int sensorValue   = 0;     
float temperatura = 0.0;

void setup() {
  
  pinMode(ledPin, OUTPUT);
  Serial.begin( 9600 );

}

void loop() {
  
  sensorValue = analogRead(sensorPin);
  temperatura = 200.55 * expf( -0.03598389 * ((float)sensorValue) );
  Serial.print( sensorValue );
  Serial.print( ", " );
  Serial.println( temperatura );
 
  // turn the ledPin on
  digitalWrite( ledPin, temperatura > 50 );
  
}
