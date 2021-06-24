#include <Servo.h>
#include <LiquidCrystal.h>
#include <Keypad.h>
#include <EEPROM.h>
#define passwordLength 5

Servo ServoMotor;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {6, 7, 8, 9};
byte colPins[COLS] = {A1, A2, A3, A4};

char Pass[passwordLength];
char PassNew[passwordLength];
char Stored[passwordLength];
byte passCount = 0, storedCount = 0;
char key;
byte keyState = 0;
char lastPressedKey;
byte mode = 0;
int cnt=0;

long time_old = 0;
bool just_allowed_pass = 0;

char initialPassword[] = {'1', '2', '3', '4'};


Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(9600);
  checkEEPROM();

  lcd.begin(16, 2);

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  ServoMotor.attach(10);
  pinMode(A0,OUTPUT);

}

void loop()
{
  key = keypad.getKey();
  keyState = keypad.getState();

  if (key) {
    lastPressedKey = key;
    Serial.println(key);
  }
  


  if ( mode == 3) {
    if (lastPressedKey == '#' && keyState == 2) {
      mode = 1;
    }
    if (lastPressedKey == '*' && keyState == 2) {
      mode = 0;
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("LOCKED");
      digitalWrite(13, LOW);
      delay(2000);
      ServoMotor.write(11);
    }
  }

  if (mode == 0) {
    ServoMotor.write(11);
    digitalWrite(13, LOW);
    lcd.setCursor(1, 0);
    lcd.print("Enter Password");

  } else if (mode == 1) {
    lcd.setCursor(0, 0);
    lcd.print("Set New Password");
  } else if (mode == 2) {
    lcd.setCursor(0, 0);
    lcd.print("Password Again");
  } else if (mode == 3) {
    lcd.setCursor(4, 0);
    lcd.print("UNLOCKED");
  }


  if (key && key != '#' && mode != 3)
  {
    collectKey();
  }

  if (passCount == passwordLength - 1)
  {
    if (mode == 0) {
      lcd.clear();
      if (!strcmp(Pass, Stored)) {
        lcd.setCursor(2, 0);
        lcd.print("WELCOME BACK");
        just_allowed_pass = 1;
        time_old = millis();

        digitalWrite(13, HIGH);

        delay(2000);
        ServoMotor.write(90);
        mode = 3;
      } else {
        lcd.setCursor(2, 0);
        lcd.print("INCORRECT !");
        lcd.setCursor(4, 1);
        lcd.print("PASSWORD");
        delay(2000);
        cnt++;
        if(cnt>2) {
  digitalWrite(A0,HIGH);
  delay(5000);
  digitalWrite(A0,LOW);
          delay(5000);
          cnt=0;
}

      }
      delay(1000);
      lcd.clear();
      clearData();

      
    } else if ( mode == 1) {
      lcd.clear();
      mode = 2;
      for (int i = 0; i < passwordLength; i = i + 1) {
        PassNew[i] = Pass[i];
      }
      clearData();
    } else if (mode == 2) {
      if (!strcmp(Pass, PassNew)) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("New Password is ");
        lcd.setCursor(4, 1);
        lcd.print(Pass);
        delay(2000);
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("Saving...");
        for (int i = 0; i <= 100; i =  i + 10) {
          lcd.setCursor(4, 1);
          lcd.print(i);
          lcd.setCursor(7, 1);
          lcd.print("%");
          delay(200);
        }
        EEPROM.put(0, Pass);
        EEPROM.get(0, Stored);
        delay(500);
      } else {
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("PASSWORD");
        lcd.setCursor(3, 1);
        lcd.print("DIDN'T MATCH!");
        delay(2000);
      }
      mode = 3;
      clearData();
      lcd.clear();
    }
  }
}

void collectKey() {
  Pass[passCount] = key;
  lcd.setCursor(4 + passCount, 1);
  lcd.print("*");
  passCount++;
}

void clearData()
{
  while (passCount != 0)
  {
    Pass[passCount--] = 0;
  }
}


void checkEEPROM() {
  EEPROM.get(0, Stored);
  if (Stored[0] == 0 && Stored[1] == 0 && Stored[2] == 0 && Stored[3] == 0) {
    Serial.println("No EEPROM PASSWORD FOUND");
    EEPROM.put(0, initialPassword);
    EEPROM.get(0, Stored);
  }
}
