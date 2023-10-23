# neaControl
ESP32 based control of an emergency power system
#### Features
* uses W5500 PHY/MAC for 100Base-T ethernet
* uses ADS1115 16Bit ADC with transformer
* measures peak voltage, rms voltage and frequency
* Web UI
* simple HTTP polling interface
#### GPIO W5500 (SPI)
* GPIO 23 - MOSI
* GPIO 19 - MISO
* GPIO 18 - CLK
* GPIO  5 - CS
* GPIO 26 - INT
* GPIO 27 - RST
#### GPIO ADS1115 (I2C)
* GPIO 21 - SDA
* GPIO 22 - SCL
* GPIO 25 - ALRT
#### Schematic
![IMAGE ALT TEXT HERE](documentation/neaControl.png)
