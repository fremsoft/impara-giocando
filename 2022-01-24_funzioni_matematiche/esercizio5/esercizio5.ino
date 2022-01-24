/* Questo sketch configura i 6 bit MSB del PORT-D per generare 
 *  segnali analogici con convertitore DIGITALE-ANALOGICO 6-bit
 *  su CH1 dell'oscilloscopio e configura i 6 bit LSB del PORT-B 
 *  per generare segnali analogici con DAC 6-bit su CH2.
 */

int ch1, ch2;
float alfa;
float d;
int   dd;

int n;
int valori[360];

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
  d = 10;
  dd = 1;
  
  // SINUSOIDALE
  for (n=0; n<360; n++)
  {
    valori[n] = 32 + 31*sin(alfa);
    //valori[n] = 32 + ((31*sin(alfa) + 15*sin(3*alfa) + 8*sin(5*alfa) + 4*sin(7*alfa))*3)/4;
    
    alfa = alfa + 0.01745329251994; 
  }

  n = 0;
}

void loop()
{
  ch1 = valori[n];

  n++; if (n >= 360) { n=0; }
  
  PORTD = ch1 << 2;
  PORTB = ch2;
  
  delayMicroseconds((int)d);

  if (dd == 1) 
  {
    /* sta andando avanti */
    d = d + 0.0001;
    if (d >= 20) { dd = 0; /* va indietro */ }
  }
  else
  {
    /* sta andando indietro */
    d = d - 0.0001;
    if (d <= 1) { dd = 1; /* va avanti */ }
  }
}
