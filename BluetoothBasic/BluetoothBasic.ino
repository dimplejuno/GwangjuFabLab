#include <SoftwareSerial.h>

// hc-06 
#define rxPin 3
#define txPin 2

SoftwareSerial mySerial(rxPin, txPin); // RX, TX
char myChar ; 

const int led = 13;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;

void setup() {
  Serial.begin(9600);   
  Serial.println("Goodnight moon!");

  mySerial.begin(9600);
  mySerial.println("Hello? It's me");

  pinMode(led, OUTPUT);
}

void loop(){
  while(mySerial.available()){
    myChar = mySerial.read();

    if(myChar == 'O' || myChar == 'o') {
        digitalWrite(led, HIGH);
    } else if(myChar == 'F' || myChar == 'f') {
      digitalWrite(led, LOW);
    }
    // delay(1000);
    Serial.print(myChar);
    
}
