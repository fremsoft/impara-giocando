// SUONA JINGLE BELLS E ACCENDE 6 LED (o 6 FILE DI LED)

/*
 *  Visualizza l'esperienza di laboratorio completa: 
 *  https://youtu.be/JXIj4VEVkEU
 *   
 */

#define LED_ROSSO   7
#define LED_GIALLO  6
#define LED_ARANCIO 5
#define LED_BLU     4
#define LED_VERDE   3
#define LED_BIANCO  2

#define BUZZER     10


#define DO5       523
#define DOd5      554
#define RE5       587
#define MIb5      622
#define MI5       659
#define FA5       698
#define FAd5      740
#define SOL5      784
#define SOLd5     830
#define LA5       880
#define SIb5      932
#define SI5       988
#define DO6      DO5 * 2
#define RE6      RE5 * 2
#define MI6      MI5 * 2

#define TEMPO_BASE  1000
#define TEMPO_PAUSA  200


void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(LED_ROSSO, OUTPUT);
  pinMode(LED_GIALLO, OUTPUT);
  pinMode(LED_ARANCIO, OUTPUT);
  pinMode(LED_BLU, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_BIANCO, OUTPUT);

  pinMode(BUZZER, OUTPUT);
  
  tone(BUZZER, 500);
}

void loop()
{
  digitalWrite(LED_ROSSO, HIGH);
  delay(100);
  digitalWrite(LED_GIALLO, HIGH);
  delay(100);
  digitalWrite(LED_ARANCIO, HIGH);
  delay(100);
  digitalWrite(LED_BLU, HIGH);
  delay(100);
  digitalWrite(LED_VERDE, HIGH);
  delay(100);
  digitalWrite(LED_BIANCO, HIGH);
  delay(100);
  
  digitalWrite(LED_ROSSO, LOW);
  delay(100);
  digitalWrite(LED_GIALLO, LOW);
  delay(100);
  digitalWrite(LED_ARANCIO, LOW);
  delay(100);
  digitalWrite(LED_BLU, LOW);
  delay(100);
  digitalWrite(LED_VERDE, LOW);
  delay(100);
  digitalWrite(LED_BIANCO, LOW);
  delay(100); 
  
  
  
  /* MELODIA */
  
  /* 1a riga */
  
  digitalWrite(LED_ROSSO, HIGH);
  
  tone(BUZZER, RE5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, SI5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, LA5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, SOL5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, RE5, TEMPO_BASE/4);
  delay(TEMPO_PAUSA);
  delay((TEMPO_BASE/4) + TEMPO_PAUSA);
  
  digitalWrite(LED_GIALLO, HIGH);
  
  tone(BUZZER, RE5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, SI5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, LA5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, SOL5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, MI5, TEMPO_BASE/4);
  delay(TEMPO_PAUSA);
  delay((TEMPO_BASE/4) + TEMPO_PAUSA);
  
  digitalWrite(LED_ARANCIO, HIGH);
  
  tone(BUZZER, MI5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, DO6, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, SI5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, LA5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, FAd5, TEMPO_BASE/4);
  delay(TEMPO_PAUSA);
  delay((TEMPO_BASE/4) + TEMPO_PAUSA);
  
  digitalWrite(LED_BLU, HIGH);
  
  tone(BUZZER, RE6, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, RE6, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, DO6, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, LA5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, SI5, TEMPO_BASE/4);
  delay(TEMPO_PAUSA);
  delay((TEMPO_BASE/4) + TEMPO_PAUSA);
  
  
  /* 2a riga */
  
  digitalWrite(LED_VERDE, HIGH);
  
  tone(BUZZER, RE5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, SI5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, LA5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, SOL5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, RE5, TEMPO_BASE/4);
  delay(TEMPO_PAUSA);
  delay((TEMPO_BASE/4) + TEMPO_PAUSA);
  
  digitalWrite(LED_BIANCO, HIGH);
  
  tone(BUZZER, RE5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, SI5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, LA5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, SOL5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, MI5, TEMPO_BASE/4);
  delay(TEMPO_PAUSA);
  delay((TEMPO_BASE/4) + TEMPO_PAUSA);
  
  digitalWrite(LED_ROSSO, LOW);
    
  tone(BUZZER, MI5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, DO6, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, SI5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, LA5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, RE6, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, RE6, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, RE6, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, RE6, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  
  digitalWrite(LED_GIALLO, LOW);
  
  tone(BUZZER, MI6, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, RE6, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, DO6, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, LA5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, SOL5, TEMPO_BASE/4);
  delay(TEMPO_PAUSA);
  delay((TEMPO_BASE/4) + TEMPO_PAUSA);
  
  /* 3a riga */
  
  digitalWrite(LED_ARANCIO, LOW);
  
  tone(BUZZER, SI5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, SI5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, SI5, TEMPO_BASE/4);
  delay(2*TEMPO_PAUSA);
  tone(BUZZER, SI5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, SI5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, SI5, TEMPO_BASE/4);
  delay(2*TEMPO_PAUSA);
  
  digitalWrite(LED_BLU, LOW);
  
  tone(BUZZER, SI5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, RE6, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, SOL5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, LA5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, SI5, TEMPO_BASE/4);
  delay(TEMPO_PAUSA);
  delay((TEMPO_BASE/4) + TEMPO_PAUSA);
  
  digitalWrite(LED_VERDE, LOW);
  
  tone(BUZZER, DO6, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, DO6, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, DO6, TEMPO_BASE/4);
  delay(2*TEMPO_PAUSA);
  tone(BUZZER, DO6, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, SI5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, SI5, TEMPO_BASE/4);
  delay(2*TEMPO_PAUSA);
  
  digitalWrite(LED_BIANCO, LOW);
  
  tone(BUZZER, RE6, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, RE6, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, DO6, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, LA5, TEMPO_BASE/8);
  delay(TEMPO_PAUSA);
  tone(BUZZER, SOL5, TEMPO_BASE/4);
  delay(TEMPO_PAUSA);
  delay((TEMPO_BASE/4) + TEMPO_PAUSA);
  
}
