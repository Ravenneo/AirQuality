# AirQuality
Lab AirQuality sensor

REQUIRES the following Arduino libraries:
 - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
 - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
 - MQ135 Library https://github.com/Ravenneo/CO2-sensor/tree/master/MQ135
 - Arduino Firmware circuito.io For I2C LCD Screen (I am using the screen with 3.3V pin): https://www.circuito.io/static/reply/index.html?solutionId=5ca9f8dc984b7f00308a37a9&solutionPath=storage.circuito.io

For MQ135 Calibration:
- Before you can use the sensor, it has to be calibrated check MQ135 Library> https://hackaday.io/project/3475-sniffing-trinket/log/12363-mq135-arduino-library

- For calibration check also: Trends in Atmospheric Carbon Dioxide> https://www.esrl.noaa.gov/gmd/ccgg/trends/gl_trend.html
- You can look into my other repository as the MQ135 code is the same https://github.com/Ravenneo/CO2-sensor
