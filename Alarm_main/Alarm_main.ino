// Date and time functions using just software, based on millis() & timer

#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

int alarmMinute = 0;
int alarmHour = 0;

RTC_Millis RTC;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup () {
    Serial.begin(9600);
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.begin(DateTime(__DATE__, __TIME__));
    lcd.init();
    lcd.backlight();
    pinMode(A6, INPUT);
}

void loop () {
  lcd.clear();
  if (RTC.now().minute() == alarmMinute && RTC.now().hour() == alarmHour){
    Serial.println("Pump HIGH");
    lcd.println("pump high");
  }
  Serial.println(digitalRead(A6));
  lcd.println(digitalRead(A6));
  delay(1000);
}