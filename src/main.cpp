#include <Arduino.h>
#include <SoftwareSerial.h>

#define BLUE_LED 9
#define GREEN_LED 11

SoftwareSerial HM10(2, 3); // RX = 2, TX = 3
char appData;  
String inData = "";

void setup()
{
  Serial.begin(9600);
  Serial.println("HM10 serial started at 9600");
  HM10.begin(9600); // set HM10 serial at 9600 baud rate
  pinMode(BLUE_LED, OUTPUT); 
  digitalWrite(BLUE_LED, LOW);
  pinMode(GREEN_LED, OUTPUT);
  digitalWrite(GREEN_LED, LOW); 
}

void loop()
{
  HM10.listen();
  while (HM10.available() > 0) {
    appData = HM10.read();
    inData = String(appData);
    Serial.write(appData);
    Serial.println("Data received: " + inData);
  }

  if (Serial.available()) {
    delay(10);
    HM10.write(Serial.read());
  }

  if ( inData == "B") {
    Serial.println("BLUE");
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
    delay(500);
    digitalWrite(BLUE_LED, HIGH);
    delay(500);
  }

  if ( inData == "G") {
    Serial.println("GREEN");
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    delay(500);
    digitalWrite(GREEN_LED, LOW);
    delay(500);
  }
}

