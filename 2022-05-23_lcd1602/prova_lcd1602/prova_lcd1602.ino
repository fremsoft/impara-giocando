/*
  LiquidCrystal Library - Hello World

   Demonstrates the use of a 16x2 LCD display.
  The LiquidCrystal library works with all LCD
  displays that are compatible with the  Hitachi
  HD44780 driver. There are many of them out
  there, and you  can usually tell them by the
  16-pin interface.

  This sketch prints "Hello World!" to the LCD
  and shows the time.

  The circuit:
  * LCD RS pin to digital pin 7
  * LCD Enable pin to digital pin 6
  * LCD D4 pin to digital pin 5
  * LCD D5 pin to digital pin 4
  * LCD D6 pin to digital pin 3
  * LCD D7 pin to digital pin 2
  * LCD R/W pin to ground
  * LCD VSS pin to ground
  * LCD VCC pin to 5V
  * 10K resistor:
  * ends to +5V and ground
  * wiper to LCD VO pin (pin 3)

  Library originally added 18 Apr 2008  by David A. Mellis
  library modified 5 Jul 2009  by Limor Fried
  (http://www.ladyada.net)
  example added 9 Jul 2009  by Tom Igoe
  modified 22 Nov 2010  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/LiquidCrystal


* Visualizza l'esperienza di laboratorio completa: 
* https://youtu.be/z1R0VC7QhMU
* 
*/

#include <LiquidCrystal.h>
//                 ( rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd_1(  7,      6,  5,  4,  3,  2);


int secondi = 0;
int ore     = 0;

void setup()
{
  //lcd_1.begin(20, 4); // Set up the number of columns and rows on the LCD.
  lcd_1.begin(16, 2); // Set up the number of columns and rows on the LCD.
  
  // Print a message to the LCD.
  lcd_1.print("hello world!");
}

void loop()
{
  
  char stringa[20];
  sprintf( stringa, "---%04d--%04d---", secondi, ore );
  
  lcd_1.setCursor(0, 1);
  lcd_1.print(stringa);
  
  delay(10); // Wait for 1000 millisecond(s)
  
  secondi += 1;
  if (secondi > 3600) { secondi = 0; ore ++; }
  
}
