#include <SoftwareSerial.h>
#include "U8glib.h"

// hc-06 
#define rxPin 3
#define txPin 2

SoftwareSerial mySerial(rxPin, txPin); // RX, TX
U8GLIB_SH1106_128X64 u8g(13, 11, 10, 9);

char myChar ; 

const int led = 13;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;
String commandString;

char inputStringBuf[20];

void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  
  //u8g.setFont(u8g_font_osb21);
  commandString.toCharArray(inputStringBuf, 20);
  u8g.drawStr( 0, 20, inputStringBuf);
}

void setupDisplay(void) {
  // 플립 : flip screen, if required
  // u8g.setRot180();
  
  // SPI 인터페이스가 충돌 날때사용함 
  // SPI backup: Avoid conflict between SW-SPI (u8glib) and HW-SPI (SD)
  //u8g.setHardwareBackup(u8g_backup_avr_spi);

  // assign default color value
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
}

void setup() {
  Serial.begin(9600);   
  Serial.println("Goodnight moon!");

  mySerial.begin(9600);
  mySerial.println("Hello? It's me");

  pinMode(led, OUTPUT);

  setupDisplay();
}

void loop(){
  while(mySerial.available()){
    myChar = mySerial.read();

/*
    if(myChar == 'O' || myChar == 'o') {
        digitalWrite(led, HIGH);
    } else if(myChar == 'F' || myChar == 'f') {
      digitalWrite(led, LOW);
    }
    // delay(1000);
    Serial.print(myChar);
    */

    // add it to the inputString:
    inputString += myChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (myChar == '\n') {
      stringComplete = true;
    } 
  }

  if (stringComplete) {
    commandString = inputString.substring(0, inputString.length() - 2);
    
    if(commandString.equals("On")){
      digitalWrite(led, HIGH);
    } else {
      digitalWrite(led, LOW);
    }// picture loop
  
  u8g.firstPage();  
  
  do {
    draw();
    } while( u8g.nextPage() );

    // clear the string:
    inputString = "";
    stringComplete = false;
  }

  
    
  // rebuild the picture after some delay
  delay(50);
  
}
