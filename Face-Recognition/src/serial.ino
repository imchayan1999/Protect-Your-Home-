#define led 7
int data;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  digitalWrite(led, LOW);
  digitalWrite(LED_BUILTIN, LOW);

}

void loop() {
  while(Serial.available())
  {
    data = Serial.read();

    if (data == '1') {
      digitalWrite(led, HIGH);
      digitalWrite(LED_BUILTIN, HIGH);
    }

    else if (data == '0')
    {
      digitalWrite(led, LOW);
      digitalWrite(LED_BUILTIN, LOW); 
    }
  }

}
