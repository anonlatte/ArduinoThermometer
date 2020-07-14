#include <Arduino.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define DHTPIN 2
#define DHTTYPE DHT22
#define UPDATE_DELAY 5000

const char degreesSymbol = 223;

LiquidCrystal_I2C lcd(0x27, 20, 4);
DHT dht(DHTPIN, DHTTYPE);

bool isDataValid(float *humidity, float *temperature) {
  return isnan(*humidity) || isnan(*temperature);
}

void displayData(float *humidity, float *temperature) {
  lcd.print("Humidity:" + String(*humidity) + '%');
  lcd.setCursor(0, 1);
  lcd.print("Temp: " + String(*temperature) + degreesSymbol + "C");
}

void displayError() {
  lcd.clear();
  lcd.print("Data error in ");
  lcd.setCursor(0, 1);
  lcd.print("DHT sensor!");
}

void setup() {
  lcd.init();
  lcd.backlight();
  dht.begin();
}

void loop() {

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  lcd.home();

  if (isDataValid(&humidity, &temperature)) {
    displayError();
    return;
  }

  displayData(&humidity, &temperature);

  delay(UPDATE_DELAY);
}
