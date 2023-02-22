/*
  DIYLESS OpenTherm Thermostat Flasher
  https://diyless.com/product/opentherm-thermostat
  
  1. Install Arduino core for the ESP32 using Board Manager
  2. Select board ESP32 Dev Module
  3. Select partition scheme Minimal SPIFFS
  4. Select port
  5. Update sketch, specify WIFI_SSID, WIFI_PASSWORD and ACTIVATION_CODE if your module has not been registered earlier
  6. Upload sketch and wait several minutes until sketch downloads the firmware
*/

#include <WiFiMulti.h>
#include <HTTPUpdate.h>

const char* WIFI_SSID = "WIFI_SSID";
const char* WIFI_PASSWORD = "WIFI_PASSWORD";
const char* ACTIVATION_CODE = "ACTIVATION_CODE";

const char* FIRMWARE_URL = "https://diyless.com/firmware/thermostat/";
String url = String(FIRMWARE_URL) + "?code=" + ACTIVATION_CODE;

WiFiMulti WiFiMulti;
char* flash_mode = "SKETCH";

void setup() {
  Serial.begin(9600);
  Serial.println("OpenTherm Thermostat Flasher");

  Serial.println("Connecting to WiFi ...");
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  Serial.println("SketchMD5: " + ESP.getSketchMD5());
  Serial.println(url);
}

void update_started() {
  Serial.printf("[%s] Update process started\n", flash_mode);
}

void update_finished() {
  Serial.printf("[%s] Update process finished\n", flash_mode);
}

void update_progress(int cur, int total) {
  Serial.printf("[%s] Update process at %d of %d bytes...\n", flash_mode, cur, total);
}

void update_error(int err) {
  Serial.printf("[%s] Update fatal error code %d\n", flash_mode, err);
}

void print_flash_result(t_httpUpdate_return ret)
{
  switch (ret) {
    case HTTP_UPDATE_FAILED:
      Serial.printf("[%s] HTTP_UPDATE_FAILED Error (%d): %s\r\n", flash_mode, httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
      break;  
    case HTTP_UPDATE_NO_UPDATES:
      Serial.printf("[%s] HTTP_UPDATE_NO_UPDATES\n", flash_mode);
      break;    
    case HTTP_UPDATE_OK:
      Serial.printf("[%s] HTTP_UPDATE_OK\n", flash_mode);
      break;
  }
}

void loop() {
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    WiFiClientSecure client;
    client.setInsecure();

    httpUpdate.setLedPin(2, LOW);
    httpUpdate.onStart(update_started);
    httpUpdate.onEnd(update_finished);
    httpUpdate.onProgress(update_progress);
    httpUpdate.onError(update_error);

    t_httpUpdate_return ret = httpUpdate.update(client, url);
    print_flash_result(ret);
  }
}
