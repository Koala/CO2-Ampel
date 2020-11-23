/* This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details. */
#include <Wire.h>
#include <rgb_lcd.h>
#include <SparkFun_SCD30_Arduino_Library.h>
#include <ESP8266WiFi.h>

//LCD RGB, 2013 Copyright (c) Seeed Technology Inc.   Author:Loovee
rgb_lcd lcd;

//Initialwerte vom Program gesetzt
String alarm = "" ;
int hum = 99 ;
int tmp = 99 ;
int co2 = 9999 ;

//Reading CO2, humidity and temperature from the SCD30 By: Nathan Seidle SparkFun Electronics 

//https://github.com/sparkfun/SparkFun_SCD30_Arduino_Library

SCD30 airSensorSCD30; // Objekt SDC30 Umweltsensor

void setup(){ // Einmalige Initialisierung
  WiFi.forceSleepBegin(); // Wifi off
  Serial.begin(115200);
  Wire.begin(); // ---- Initialisiere den I2C-Bus 

  if (Wire.status() != I2C_OK) Serial.println("Something wrong with I2C");

  lcd.begin(16, 2);// LCD Backlight initialisieren 

  if (airSensorSCD30.begin() == false) {
    Serial.println("The SCD30 did not respond. Please check wiring."); 
    while(1) {
      yield(); 
      delay(1);
    } 
  }

  airSensorSCD30.setAutoSelfCalibration(false); // Sensirion no auto calibration

  airSensorSCD30.setMeasurementInterval(2);     // CO2-Messung alle 5 s

  Wire.setClock(100000L);            // 100 kHz SCD30 
  Wire.setClockStretchLimit(200000L);// CO2-SCD30
}

void loop() { // Kontinuierliche Wiederholung
  co2 = airSensorSCD30.getCO2();
  tmp = airSensorSCD30.getTemperature();
  hum = airSensorSCD30.getHumidity();
  alarm = "      ";
  if (co2 > 900) alarm = "Alarm"; 
  lcd.setCursor(0,0);
  lcd.print(String(String(String(co2)))+"ppm co2       ");
  lcd.setCursor(0,1);
//  lcd.print(String("temperatura="+String(String(airSensorSCD30.getTemperature())))+"                ");
  // das Grad (°) Zeichen: \337
  lcd.print(String(String(String(tmp))+"\337 "+String(String(hum)))+"% "+String(String(alarm)));
  delay( 2000 );
}
