/*
  SD card datalogger

  This example shows how to log data from three analog sensors
  to an SD card using the SD library.

  The circuit:
   analog sensors on analog ins 0, 1, and 2
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK  - pin 13
 ** CS   - pin 10

  created  24 Nov 2010
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

*/

#include <SPI.h>
#include <SD.h>

const int chipSelect = 10;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);

  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

void loop() {
  unsigned long tt, hh, mm, ss; 
  
  // make a string for assembling the data to log:
  String dataString = "";
  char str[32];
  tt = millis() % 86400000L; // timestamp ms del giorno
  ss = tt / 1000;
  mm = ss / 60;
  hh = mm / 60;

  ss = ss % 60;
  mm = mm % 60;

  sprintf(str, "%02d:%02d:%02d,", (int)hh, (int)mm, (int)ss);
  dataString += String(str);
  
  // read three sensors and append to the string:
  int sensor = analogRead( A0 );
  dataString += String(sensor);

  Serial.println(dataString);

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }

  delay(10000);
}
