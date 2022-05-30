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
byte _29[8] = { B01000, B10101, B10011, B00001, B00011, B00000, B00000, B00000 };
byte _30[8] = { B11011, B00101, B00101, B00101, B11001, B00000, B00000, B00000 };
byte _31[8] = { B11010, B01010, B01010, B01010, B01101, B00000, B00000, B00000 };


#define    T    1000

void setup()
{
  lcd_gr.createChar(0, _00);
  lcd_gr.createChar(1, _01);
  lcd_gr.createChar(2, _02);
  lcd_gr.createChar(3, _03);
  lcd_gr.createChar(4, _16);
  lcd_gr.createChar(5, _17);
  lcd_gr.createChar(6, _18);
  lcd_gr.createChar(7, _19);
  
  lcd_gr.begin(16, 2); 
  lcd_gr.noAutoscroll();
  
  lcd_gr.setCursor(0, 0);
  lcd_gr.write(byte(0));
  lcd_gr.write(byte(1));
  lcd_gr.write(byte(2));
  lcd_gr.write(byte(3));
  
  lcd_gr.setCursor(0, 1);
  lcd_gr.write(byte(4));
  lcd_gr.write(byte(5));
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(7));

}

void loop()
{
  delay( T );

  lcd_gr.createChar(0, _01);
  lcd_gr.createChar(1, _02);
  lcd_gr.createChar(2, _03);
  lcd_gr.createChar(3, _04);
  lcd_gr.createChar(4, _17);
  lcd_gr.createChar(5, _18);
  lcd_gr.createChar(6, _19);
  lcd_gr.createChar(7, _20);
  
  delay( T );

  lcd_gr.createChar(0, _02);
  lcd_gr.createChar(1, _03);
  lcd_gr.createChar(2, _04);
  lcd_gr.createChar(3, _05);
  lcd_gr.createChar(4, _18);
  lcd_gr.createChar(5, _19);
  lcd_gr.createChar(6, _20);
  lcd_gr.createChar(7, _21);
  
  delay( T );

  lcd_gr.createChar(0, _03);
  lcd_gr.createChar(1, _04);
  lcd_gr.createChar(2, _05);
  lcd_gr.createChar(3, _06);
  lcd_gr.createChar(4, _19);
  lcd_gr.createChar(5, _20);
  lcd_gr.createChar(6, _21);
  lcd_gr.createChar(7, _22);
  
  delay( T );

  lcd_gr.createChar(0, _04);
  lcd_gr.createChar(1, _05);
  lcd_gr.createChar(2, _06);
  lcd_gr.createChar(3, _07);
  lcd_gr.createChar(4, _20);
  lcd_gr.createChar(5, _21);
  lcd_gr.createChar(6, _22);
  lcd_gr.createChar(7, _23);
  
  delay( T );

  lcd_gr.createChar(0, _05);
  lcd_gr.createChar(1, _06);
  lcd_gr.createChar(2, _07);
  lcd_gr.createChar(3, _08);
  lcd_gr.createChar(4, _21);
  lcd_gr.createChar(5, _22);
  lcd_gr.createChar(6, _23);
  lcd_gr.createChar(7, _24);
  
  delay( T );

  lcd_gr.createChar(0, _06);
  lcd_gr.createChar(1, _07);
  lcd_gr.createChar(2, _08);
  lcd_gr.createChar(3, _09);
  lcd_gr.createChar(4, _22);
  lcd_gr.createChar(5, _23);
  lcd_gr.createChar(6, _24);
  lcd_gr.createChar(7, _25);
  
  delay( T );

  lcd_gr.createChar(0, _07);
  lcd_gr.createChar(1, _08);
  lcd_gr.createChar(2, _09);
  lcd_gr.createChar(3, _10);
  lcd_gr.createChar(4, _23);
  lcd_gr.createChar(5, _24);
  lcd_gr.createChar(6, _25);
  lcd_gr.createChar(7, _26);
  
  delay( T );

  lcd_gr.createChar(0, _08);
  lcd_gr.createChar(1, _09);
  lcd_gr.createChar(2, _10);
  lcd_gr.createChar(3, _11);
  lcd_gr.createChar(4, _24);
  lcd_gr.createChar(5, _25);
  lcd_gr.createChar(6, _26);
  lcd_gr.createChar(7, _27);
  
  delay( T );

  lcd_gr.createChar(0, _09);
  lcd_gr.createChar(1, _10);
  lcd_gr.createChar(2, _11);
  lcd_gr.createChar(3, _12);
  lcd_gr.createChar(4, _25);
  lcd_gr.createChar(5, _26);
  lcd_gr.createChar(6, _27);
  lcd_gr.createChar(7, _28);
  
  delay( T );

  lcd_gr.createChar(0, _10);
  lcd_gr.createChar(1, _11);
  lcd_gr.createChar(2, _12);
  lcd_gr.createChar(3, _13);
  lcd_gr.createChar(4, _26);
  lcd_gr.createChar(5, _27);
  lcd_gr.createChar(6, _28);
  lcd_gr.createChar(7, _29);
  
  delay( T );

  lcd_gr.createChar(0, _11);
  lcd_gr.createChar(1, _12);
  lcd_gr.createChar(2, _13);
  lcd_gr.createChar(3, _14);
  lcd_gr.createChar(4, _27);
  lcd_gr.createChar(5, _28);
  lcd_gr.createChar(6, _29);
  lcd_gr.createChar(7, _30);
  
  delay( T );

  lcd_gr.createChar(0, _12);
  lcd_gr.createChar(1, _13);
  lcd_gr.createChar(2, _14);
  lcd_gr.createChar(3, _15);
  lcd_gr.createChar(4, _28);
  lcd_gr.createChar(5, _29);
  lcd_gr.createChar(6, _30);
  lcd_gr.createChar(7, _31);
  
  delay( T );

  lcd_gr.createChar(0, _13);
  lcd_gr.createChar(1, _14);
  lcd_gr.createChar(2, _15);
  lcd_gr.createChar(3, _00);
  lcd_gr.createChar(4, _29);
  lcd_gr.createChar(5, _30);
  lcd_gr.createChar(6, _31);
  lcd_gr.createChar(7, _16);
  
  delay( T );

  lcd_gr.createChar(0, _14);
  lcd_gr.createChar(1, _15);
  lcd_gr.createChar(2, _00);
  lcd_gr.createChar(3, _01);
  lcd_gr.createChar(4, _30);
  lcd_gr.createChar(5, _31);
  lcd_gr.createChar(6, _16);
  lcd_gr.createChar(7, _17);
  
  delay( T );

  lcd_gr.createChar(0, _15);
  lcd_gr.createChar(1, _00);
  lcd_gr.createChar(2, _01);
  lcd_gr.createChar(3, _02);
  lcd_gr.createChar(4, _31);
  lcd_gr.createChar(5, _16);
  lcd_gr.createChar(6, _17);
  lcd_gr.createChar(7, _18);
  
  delay( T );

  lcd_gr.createChar(0, _00);
  lcd_gr.createChar(1, _01);
  lcd_gr.createChar(2, _02);
  lcd_gr.createChar(3, _03);
  lcd_gr.createChar(4, _16);
  lcd_gr.createChar(5, _17);
  lcd_gr.createChar(6, _18);
  lcd_gr.createChar(7, _19);
  
}
