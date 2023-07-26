// Date and time functions using just software, based on millis() & timer

#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

//1440 minutes in a day
int analogPin = A0;
int alarmMinute = 0;
int alarmHour = 0;
int analogInput = 0;
 
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
    
}

void MTOHM () {
  analogInput = map(analogRead(analogPin), 0, 1023, 0, 1440);
  timeHours = float(analogInput) / 60;
  timeIntHours = analogInput / 60;

  timeMinutesDevided = timeHours - timeIntHours;

  timeMinutes = timeMinutesDevided * 60;
}

void loop () {
  lcd.clear();
  if (RTC.now().minute() == alarmMinute && RTC.now().hour() == alarmHour){
    Serial.println("Pump HIGH");
    lcd.println("pump high");
  }
  lcd.println(String(timeIntHours) + ":" + String(timeMinutes));

  MTOHM();
  Serial.println(String(timeIntHours) + ":" + String(timeMinutes));
  delay(100);
}