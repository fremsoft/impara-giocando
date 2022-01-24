/* Questo sketch configura i 6 bit MSB del PORT-D per generare 
 *  segnali analogici con convertitore DIGITALE-ANALOGICO 6-bit
 *  su CH1 dell'oscilloscopio e configura i 6 bit LSB del PORT-B 
 *  per generare segnali analogici con DAC 6-bit su CH2.
 */

int ch1, ch2;
float alfa;

void setup()
{
  Serial.begin(9600);
    
  /* CH1 dell'oscilloscopio */
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  /* CH2 dell'oscilloscopio */
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  ch1 = 0;
  ch2 = 0;
  alfa = 0;
}

void loop()
{
  alfa = alfa + 0.0175;
  
  ch1 = 32 + 31*sin(alfa);
  ch2 = 32 + 31*sin(3*alfa);

  ch1 = (ch1+ch2)/2;
  
  PORTD = ch1 << 2;
  PORTB = ch2;
  
  delay(1);
}
