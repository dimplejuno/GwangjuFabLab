#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

#define led 13
#define rxPin 3
#define txPin 2

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            10

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      12

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

SoftwareSerial BT(rxPin, txPin); // RX, TX

int red,green,blue;


void setup(){
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  BT.begin(9600);
  pixels.begin();
  Serial.println("Start!");
}

 void loop() {
  // if there's any serial available, read it:
  while (BT.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
    red = BT.parseInt(); // 255,0,0
    
    // do it again:
    green = BT.parseInt(); 
    
    // do it again:
    blue = BT.parseInt(); 

    // fill strip
    //colorSet(pixels.Color(red, green, blue), 0); 

    // look for the newline. That's the end of your
    // sentence:
    if (BT.read() == '\n') {

      red = constrain(red, 0, 255);
      green = constrain(green, 0, 255);
      blue = constrain(blue, 0, 255);

      // fill strip
      colorSet(pixels.Color(red, green, blue), 0); 
      
      // send some data back
      Serial.println("received:"+String(red)+","+String(green)+","+String(blue));
    }
  }
}

// Fill strip with a color
void colorSet(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<pixels.numPixels(); i++) {
      pixels.setPixelColor(i, c);
  }
   pixels.show();
   delay(wait);
}

    
