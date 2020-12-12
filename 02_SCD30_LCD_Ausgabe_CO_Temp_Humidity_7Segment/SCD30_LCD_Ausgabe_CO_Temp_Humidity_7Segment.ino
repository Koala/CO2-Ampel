/* This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details. */
#include <Wire.h>
#include <TM1637.h>
#include <rgb_lcd.h>
#include <SparkFun_SCD30_Arduino_Library.h>
#include <ESP8266WiFi.h>

// Definition of the Grove 4-digit display pins (CLK and DIO) and 
// initialization of its library (TM1637 library):
// defined for NodeMCU pins D3 and D5 !!!
#define CLK D3  // define TM1637 clock pin
#define DIO D5  // define TM1637 data pin
// initialize the TM1637 library
TM1637 tm1637(CLK, DIO);

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

  // initialize the TM1637 display
  tm1637.init();
  // set display brightness (from 0 to 7)
  tm1637.set(3);
//  tm1637.write(2, 0x63);  // print ° on 2nd digit (0 is most left digit)


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

  displayNumber(co2);

  delay( 2000 );
}

void displayNumber(int num){   
    tm1637.display(3, num % 10);   
    tm1637.display(2, num / 10 % 10);   
    tm1637.display(1, num / 100 % 10);   
    tm1637.display(0, num / 1000 % 10);
}
