/*
 * Esempio di utilizzo del Character Generator su LCD1602
 * per creare un PAC-MAN che mangia dei pallini come se
 * fosse un display grafico, mediante la funzione createChar()
 * 
 * Visualizza l'esperienza di laboratorio completa: 
 * https://youtu.be/z1R0VC7QhMU
 *  
 */

#include <LiquidCrystal.h>

LiquidCrystal lcd_gr(7, 6, 5, 4, 3, 2);

byte pacman_1_dx[8] = {
  B00000,  
  B00000,   
  B01110,   
  B11111,   
  B11000,   
  B11111,   
  B01110,
  B00000
};

byte pacman_2_dx[8] = {
  B00000,  
  B00000,   
  B01110,   
  B11100,   
  B11000,   
  B11100,   
  B01110,
  B00000
};

byte pacman_3_dx[8] = {
  B00000,  
  B00000,   
  B01100,   
  B11000,   
  B11000,   
  B11000,   
  B01100,
  B00000
};


byte pacman_1_sx[8] = {
  B00000,  
  B00000,
  B01110,   
  B11111,   
  B00011,   
  B11111,   
  B01110, 
  B00000
};

byte pacman_2_sx[8] = {
  B00000,  
  B00000,   
  B01110,   
  B00111,   
  B00011,   
  B00111,   
  B01110,
  B00000
};

byte pacman_3_sx[8] = {
  B00000,  
  B00000,   
  B00110,   
  B00011,   
  B00011,   
  B00011,   
  B00110,
  B00000
};

byte pallino_grande[8] = {
  B00000,  
  B00000,   
  B00000,   
  B00100,   
  B01110,   
  B00100,   
  B00000,
  B00000
};

byte pallino_piccolo[8] = {
  B00000,  
  B00000,   
  B00000,   
  B00000,   
  B00100,   
  B00000,   
  B00000,
  B00000
};

int riga_pacman;
int colonna_pacman;
int frame_pacman;

void setup() {
  Serial.begin(9600);
  
  
  lcd_gr.createChar(0, pacman_1_dx);
  lcd_gr.createChar(1, pacman_2_dx);
  lcd_gr.createChar(2, pacman_3_dx);
  
  lcd_gr.createChar(3, pacman_1_sx);
  lcd_gr.createChar(4, pacman_2_sx);
  lcd_gr.createChar(5, pacman_3_sx);
  
  lcd_gr.createChar(6, pallino_piccolo);
  lcd_gr.createChar(7, pallino_grande);

  lcd_gr.begin(16, 2);  
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(7));
  
  lcd_gr.setCursor(0,1);
  lcd_gr.write(byte(7));
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(6));
  lcd_gr.write(byte(6));
 
  riga_pacman = 0;
  colonna_pacman = 0;
  frame_pacman = 0;

}

void loop() {
  
  /* disegna il pacman */
  if (riga_pacman == 0) {
    /* disegna il pacman che va a destra */
    
    lcd_gr.setCursor(colonna_pacman, riga_pacman);
    switch( frame_pacman ) {
      case 0 : 
        lcd_gr.write(byte(0)); 
        break;
      case 1 :
        lcd_gr.write(byte(1)); 
        break;
      case 2 :
        lcd_gr.write(byte(2)); 
        break;
      case 3 :
        lcd_gr.write(byte(1)); 
        break;
    }
    delay(100);
    frame_pacman ++; 
    if (frame_pacman > 3) { 
      frame_pacman = 0; 
      lcd_gr.setCursor(colonna_pacman, riga_pacman);
      lcd_gr.write(' '); 
      colonna_pacman ++;
      
      if (colonna_pacman >= 16) { 
        colonna_pacman = 15;
        riga_pacman = 1;
      }
    }
  }
  
  
  if (riga_pacman == 1) {
    /* disegna il pacman che va a sinistra */
    
    lcd_gr.setCursor(colonna_pacman, riga_pacman);
    switch( frame_pacman ) {
      case 0 : 
        lcd_gr.write(byte(3)); 
        break;
      case 1 :
        lcd_gr.write(byte(4)); 
        break;
      case 2 :
        lcd_gr.write(byte(5)); 
        break;
      case 3 :
        lcd_gr.write(byte(4)); 
        break;
    }
    delay(100);
    frame_pacman ++; 
    if (frame_pacman > 3) { 
      frame_pacman = 0;
      
      lcd_gr.setCursor(colonna_pacman, riga_pacman);
      lcd_gr.write(' '); 
      colonna_pacman --;
      
      if (colonna_pacman < 0) { 
        colonna_pacman = 0;
        riga_pacman = 2;
      }
    }
  }  

  if (riga_pacman == 2) {
      lcd_gr.clear();
      riga_pacman = 3;
  }
  
  if (riga_pacman == 3) {
  
      lcd_gr.setCursor(0, 0);
      lcd_gr.print("     IMPARA     ");
      lcd_gr.setCursor(0, 1);
      lcd_gr.print("    GIOCANDO    ");
  }  
}
