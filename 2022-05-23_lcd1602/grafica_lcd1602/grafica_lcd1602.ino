/*
 * Come usare il display LCD1602 alfanumerico come se fosse un 
 * display grafico, mediante la funzione createChar()
 * Visualizza l'esperienza di laboratorio completa: 
 * https://youtu.be/...
 *  
 */

#include <LiquidCrystal.h>
//                  ( rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd_gr(  7,      6,  5,  4,  3,  2);

byte _00[8] = { B00000, B00000, B00010, B00011, B00001, B00001, B00001, B00001 };
byte _01[8] = { B00000, B00000, B11000, B01000, B11000, B00000, B00000, B11000 };
byte _02[8] = { B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000 };
byte _03[8] = { B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000 };
byte _04[8] = { B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000 };
byte _05[8] = { B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000 };
byte _06[8] = { B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000 };
byte _07[8] = { B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000 };

byte _08[8] = { B00000, B00000, B01100, B10010, B10010, B10010, B10100, B11000 };
byte _09[8] = { B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000 };
byte _10[8] = { B00000, B00000, B11001, B10110, B10000, B10000, B00000, B00000 };
byte _11[8] = { B00000, B00000, B00000, B10000, B10000, B10010, B01100, B11000 };
byte _12[8] = { B00000, B00000, B00000, B00000, B00000, B00010, B00000, B00000 };
byte _13[8] = { B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000 };
byte _14[8] = { B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000 };
byte _15[8] = { B00000, B00000, B00000, B00000, B00000, B00010, B00000, B00000 };

byte _16[8] = { B00100, B01000, B10000, B10000, B10000, B01000, B00111, B00000 };
byte _17[8] = { B00000, B00000, B00001, B00010, B00100, B01000, B10000, B00000 };
byte _18[8] = { B01001, B11110, B10100, B10100, B10100, B00000, B00000, B00000 };
byte _19[8] = { B10001, B10010, B10010, B10010, B01101, B00000, B00000, B00000 };
byte _20[8] = { B00001, B10010, B10010, B10010, B11100, B00000, B00000, B00000 };
byte _21[8] = { B01100, B10100, B10100, B10101, B10110, B00000, B00000, B00000 };
byte _22[8] = { B10100, B10100, B10100, B10101, B11010, B00000, B00000, B00000 };
byte _23[8] = { B11100, B10100, B11000, B10001, B01110, B00000, B00000, B00000 };

byte _24[8] = { B10001, B10001, B10001, B01011, B00100, B00000, B00000, B00000 };
byte _25[8] = { B10000, B10000, B00000, B00010, B11100, B00000, B00000, B00000 };
byte _26[8] = { B00000, B00000, B10000, B10000, B11001, B00110, B00000, B00000 };
byte _27[8] = { B01011, B01010, B01100, B01000, B10000, B00000, B00000, B00000 };
byte _28[8] = { B11010, B10010, B10010, B11011, B01100, B00000, B00000, B00000 };
byte _29[8] = { B01000, B10101, B10011, B00001, B00111, B00000, B00000, B00000 };
byte _30[8] = { B11011, B00101, B00101, B00101, B11001, B00000, B00000, B00000 };
byte _31[8] = { B11010, B01010, B01010, B01010, B01101, B00000, B00000, B00000 };


#define    T     40

void setup()
{
  lcd_gr.createChar(0, _00);
  lcd_gr.createChar(1, _01);
  lcd_gr.createChar(2, _08);
  lcd_gr.createChar(3, _10);
  lcd_gr.createChar(4, _11);
  lcd_gr.createChar(5, _12);
  lcd_gr.createChar(6, _15);
  
  lcd_gr.begin(16,2); 
  lcd_gr.noAutoscroll();
  
}

void loop()
{
  lcd_gr.createChar(0, _00);
  lcd_gr.createChar(1, _01);
  lcd_gr.createChar(2, _08);
  lcd_gr.createChar(3, _10);
  lcd_gr.createChar(4, _11);
  lcd_gr.createChar(5, _12);
  lcd_gr.createChar(6, _15);
  
  lcd_gr.setCursor(0, 0);
  lcd_gr.write(byte(0));
  lcd_gr.write(byte(1));
  
  lcd_gr.setCursor(8, 0);
  lcd_gr.write(byte(2));
  
  lcd_gr.setCursor(10, 0);
  lcd_gr.write(byte(3));
  lcd_gr.write(byte(4));
  lcd_gr.write(byte(5));
  
  lcd_gr.setCursor(15, 0);
  lcd_gr.write(byte(6));
  
  delay( T ); 
  lcd_gr.clear();
  
  lcd_gr.createChar(0, _16);
  lcd_gr.createChar(1, _17);
  lcd_gr.createChar(2, _18);
  lcd_gr.createChar(3, _19);
  lcd_gr.createChar(4, _20);
  lcd_gr.createChar(5, _21);
  lcd_gr.createChar(6, _22);
  lcd_gr.createChar(7, _23);
  
  lcd_gr.setCursor(0, 1);
  
  lcd_gr.write(byte(0));
  lcd_gr.write(byte(1));
  lcd_gr.write(byte(2));
  lcd_gr.write(byte(3));
  lcd_gr.write(byte(4));
  lcd_gr.write(byte(5));
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(7));

  delay( T ); 
  lcd_gr.clear();
  
  lcd_gr.createChar(0, _24);
  lcd_gr.createChar(1, _25);
  lcd_gr.createChar(2, _26);
  lcd_gr.createChar(3, _27);
  lcd_gr.createChar(4, _28);
  lcd_gr.createChar(5, _29);
  lcd_gr.createChar(6, _30);
  lcd_gr.createChar(7, _31);
  
  lcd_gr.setCursor(8, 1);
  
  lcd_gr.write(byte(0));
  lcd_gr.write(byte(1));
  lcd_gr.write(byte(2));
  lcd_gr.write(byte(3));
  lcd_gr.write(byte(4));
  lcd_gr.write(byte(5));
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(7));

  delay( T );
  lcd_gr.clear();
  
}
