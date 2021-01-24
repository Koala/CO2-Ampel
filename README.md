# CO2-Ampel

## Diverse Dinge zum Thema CO2-Ampel.  

Der Code ist meist "irgendwie" zusammengefunden. Ein Teil wurde auch aus ardublock-IoT_V516 heraus erzeugt.  
Die Einbindung von ardublock-IoT_V516 in die Arduino Umgebung ist recht einfach, wenn man weiß, wie's geht :-)  


verwendete Hardware der Testumgebung:  
Grove Base Shield  
NodeMCU Amica  
SCD30  
LCD Grove-16x2 (Black on Yellow)  
Grove I2C-Hub  
Grove 4-Digit Display mit TM1637  


## Pin-Belegungen  
### I2C am NodeMCU  
I2C-1: D1 GPIO 5  
I2C-2: D2 GPIO 4  
I2C-3: 3,3 V  
I2C-4: GND  

### SCD30 am NodeMCU (I2C)  
VIN: 3,3 V  
GND: GND  
TX/SCL: D1 GIO5  
RX/SDA: D2 GIO4  
RDY: ?  
PWM: ?  
SEL: ?  

RDY, PWM, SEL nicht benutzt bei Verwendung mit dem Octopus.  







## ToDo
- Hardware-Quellen als Beispiel nennen (dies ist KEINE Werbung)  
- Beschreibung der Einbindung des Ardublock in die Aduino-IDE unter Linux  
- Hinweis auf PlatformIO (Alternative zur Arduino-IDE - aber eher für Auskenner!?)  
