int smoke = A0;
int buzzer = 11;
int led = 13;
float sensorValue;
void setup() {
  pinMode(buzzer,OUTPUT);
  pinMode(led,OUTPUT);
  pinMode(smoke,INPUT);
   Serial.begin(9600); // sets the serial port to 9600
  Serial.println("Gas sensor warming up!");
  delay(20000); // allow the MQ-6 to warm up
 
  
}

void loop() {
  sensorValue=analogRead(smoke);
  if(sensorValue > 400)
  {
    Serial.print(" | Smoke detected!");
    digitalWrite(buzzer,HIGH);
    digitalWrite(led,HIGH);
  }
  else
  {
     Serial.print(" | Smoke  not detected!");
     digitalWrite(buzzer,LOW);
     digitalWrite(led,LOW);
  
  }
  delay(2000); // wait 2s for next reading
}
