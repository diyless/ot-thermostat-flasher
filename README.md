# DIYLESS OpenTherm Thermostat Flasher  
https://diyless.com/product/opentherm-thermostat  

## Firmware setup
1. Install Arduino core for the ESP32 **(version 2.0.5 only)** using Board Manager  
2. Select board ESP32 Dev Module  
3. Select partition scheme Minimal SPIFFS  
4. Select port  
5. Update sketch, specify WIFI_SSID, WIFI_PASSWORD and ACTIVATION_CODE if your module has not been registered earlier  
6. Upload sketch and wait several minutes until sketch downloads the firmware. You can open Serial Monitor from Arduino IDE to check firmware flashing progress (use 9600bps baud rate).  
Please contact us to get the activation code https://diyless.com/contact  
If you bought the thermostat from https://diyless.com/ web shop you can re-flash the firmware without activation code (just left it as is).

## Temperature sensor options:
- Built-in. Connect DS18B20 sensor using wires to avlid heat impact from ESP32 chip.
- Bluetooth. The thermostat can be paired with Mi Temperature and Humidity Sensor 2, but with custom firmware only.
You can flash it using this page https://pvvx.github.io/ATC_MiThermometer/TelinkMiFlasher.html
- MQTT. To use MQTT sensor you need to publish current room temperature (float value) every 1 minute to topic:
diyless_thermostat/cmnd/things/thermostat/properties/temperature


## Configuration
https://diyless.com/blog/opentherm-thermostat-cfg-overview
