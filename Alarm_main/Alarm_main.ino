// Date and time functions using just software, based on millis() & timer

#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

//1440 minutes in a day
int analogPin = A0;
int alarmMinute = 0;
int alarmHour = 0;
int analogInput = 0;
int buttonPin = 2;
int pumpPin = 3;

int iVal = 0;

float timeHours = 0;
int timeIntHours = 0;
float timeMinutesDevided = 0;
int timeMinutes = 0;

RTC_Millis RTC;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup () {
    Serial.begin(9600);
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.begin(DateTime(__DATE__, __TIME__));
    lcd.init();
    lcd.backlight();
    pinMode(analogPin, INPUT);
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(pumpPin, OUTPUT);
    
}

void MTOHM () {
  analogInput = map(analogRead(analogPin), 0, 1023, 0, 1440);
  timeHours = float(analogInput) / 60;
  timeIntHours = analogInput / 60;

  timeMinutesDevided = timeHours - timeIntHours;

  timeMinutes = timeMinutesDevided * 60;

  
}

String addAZero(int iVal) {
  if (iVal < 10 && iVal >= 0) {
    return "0" + String(iVal);
  } else {
    return String(iVal);  // Return the original value if not < 10 and >= 0
  }
}

void button () {
  int sensorVal = digitalRead(buttonPin);
  
  if (sensorVal == LOW) {
    EEPROM.update(0, timeIntHours);
    EEPROM.update(1, timeMinutes);
    Serial.println("time set to " + String(timeIntHours) + ":" + addAZero(timeMinutes));
  } 
}

void loop () {
  lcd.clear();
  if (RTC.now().minute() == alarmMinute && RTC.now().hour() == alarmHour){
    Serial.println("Pump HIGH");
    lcd.println("pump high");
    digitalWrite(pumpPin, HIGH);
    //delay(30000);
    digitalWrite(pumpPin, LOW);
    Serial.println("pump low");
    lcd.clear();
    //delay(30000);
  }
  else {
    digitalWrite(pumpPin, LOW);
  }
  lcd.println(String(timeIntHours) + ":" + String(timeMinutes));

  MTOHM();

  button();

  alarmMinute = EEPROM.read(1);
  alarmHour = EEPROM.read(0);

  delay(100);
}