const int buzzerPin = 11;
const int flamePin = 9;
int Flame = HIGH;
int led = 13;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(flamePin, INPUT);
  Serial.begin(9600);

}

void loop() {
  Flame = digitalRead(flamePin);
  if (Flame == LOW)
  {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(led, HIGH);
  }
  else 
  {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(led, LOW);
  }
}
