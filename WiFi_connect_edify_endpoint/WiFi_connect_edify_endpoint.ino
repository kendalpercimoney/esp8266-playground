#include "SSD1306Wire.h"
#include "ESP8266WiFi.h"
#include "ESP8266HTTPClient.h"
#include <ArduinoJson.h>

// Initialize the OLED display using Arduino Wire:
SSD1306Wire display(0x3c, D6, D5); // reversed!

const char *ssid = "eir19975071-2.4G";
const char *password = "eyksqz4k";
const char *endpoint = "http://firstiimpression.com/Edify/edifyAPI.php";

void setup() {
  // Initializing the UI will init the display too.
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 0, "Connecting to WiFi..." );
  display.display();

  Serial.begin(9600);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    display.clear();
    display.drawString(0, 0, "Connecting to WiFi..." );
    display.display();
  }

  display.clear();
  display.drawString(0, 0, "Connected to WiFi" );
  display.display();
  delay(2000);  // Display the message for 2 seconds
}

void loop() {
  // Make a request to the endpoint
  HTTPClient http;
  WiFiClient wifiClient;

  // Use ::begin(WiFiClient, url) instead
  http.begin(wifiClient, endpoint);

  int httpCode = http.GET();
  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println(payload);

    // Parse JSON
    const size_t capacity = JSON_OBJECT_SIZE(2) + 256;  // Adjust the size based on your JSON structure
    DynamicJsonDocument doc(capacity);
    deserializeJson(doc, payload);

    // Extract the verse
    const char* verse = doc["verse"];
    Serial.println(verse);

    // Display the verse on the OLED
    display.clear();
    display.drawStringMaxWidth(0, 3, 128, "Verse:");
    display.drawStringMaxWidth(0, 14, 128, verse);
    display.display();
  } else {
    display.clear();
    display.drawString(0, 12, "Failed to connect to endpoint");
    display.display();
  }

  http.end();

  delay(5000);  // Wait for 5 seconds before making the next request
}
