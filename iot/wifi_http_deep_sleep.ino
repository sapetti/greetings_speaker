
#include <WiFi.h>
#include <esp_wifi.h>
#include <HTTPClient.h>
#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  30        /* Time ESP32 will go to sleep (in seconds) */

static bool hasWifi = false;
const char* WIFI_SSID = "...";
const char* WIFI_PASS = "...";
const char* SERVER_URL = "http://192.168.1.99:3000/play-sound";
// const byte ledGpio = 2;

IPAddress localIP(192, 168, 1, 248);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);

static void connect() {
  int tries = 0;
  if (!WiFi.config(localIP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
    return;
  }
  Serial.println("Connecting...");
  // WiFi fix: https://github.com/esp8266/Arduino/issues/2186
  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED && tries < 5) {
    if (WiFi.status() != WL_CONNECTED) {
      tries = tries + 1;
      delay(1000);
      Serial.println(WiFi.status());
    }
  }
  if (WiFi.status() != WL_CONNECTED) {
    return;
  }
  hasWifi = true;
}

void sendRequest() {
  HTTPClient http;
  http.begin(SERVER_URL);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Accept", "application/json");
  int httpCode = http.GET();
  if (httpCode <= 0 || httpCode != HTTP_CODE_OK) {
      Serial.println("Failed...");
      return;
  }
  http.end();
}

void setup() {
  // pinMode(ledGpio, OUTPUT);
  // digitalWrite(ledGpio, HIGH);
  Serial.begin(115200);
  while (!Serial) {}
  
  esp_sleep_wakeup_cause_t wakeup_reason;
  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason) {
    case ESP_SLEEP_WAKEUP_TIMER :
      Serial.println("timer");
      esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, 1);
      break;
    default :
      Serial.println("Sensor");
      hasWifi = false;
      connect();
      if (hasWifi) {
        sendRequest();
        esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
      } 
      esp_wifi_stop();
      break;
  }
  esp_deep_sleep_start();
}

void loop(){}
