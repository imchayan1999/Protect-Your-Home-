#include "DHT.h"
#define Type DHT11
int sensePin = 2;
DHT HT(sensePin,Type);
float tempC;
float tempF;
int buzz = 12; 
int pirOutput = 5; 
int value = 0;
int pirState = LOW;

void setup() {
  Serial.begin(9600);
  HT.begin();
  delay(500);
  pinMode(buzz, OUTPUT);
  pinMode(pirOutput, INPUT);


  
}

void loop() {
  tempC=HT.readTemperature();
  tempF=HT.readTemperature(true);
  value = digitalRead(pirOutput);


  if (value == HIGH) {
    digitalWrite(buzz, HIGH);
    Serial.println("OK");
    delay(1000);
    Serial.println("ATD+919588264214;");
    delay(15000);
    Serial.println("ATH");
    delay(1000);

    if (pirState == LOW) {
      pirState = HIGH;
    }
  }else{
    digitalWrite(buzz, LOW);

    if(pirState == HIGH){
      pirState = LOW;
      }
    }
  if(tempC > 80.0) {
    digitalWrite(buzz, HIGH);
    Serial.println("OK");
    delay(1000);
    Serial.println("Yo");
    Serial.println("ATD+919588264214;");
    delay(15000);
    Serial.println("ATH");
    delay(1000);
  }
  else {
    digitalWrite(buzz, LOW);
  }
}
