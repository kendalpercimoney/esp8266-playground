//working

#include "SSD1306Wire.h"
#include "ESP8266WiFi.h"
// Initialize the OLED display using Arduino Wire:
SSD1306Wire display(0x3c, D6, D5); // reversed!

void setup() {
  
  // Initialising the UI will init the display too.
  display.init();

  //display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 0, "beginning..." );
  display.display();
}


void loop() {
  // clear the display
  display.clear();
  int height = 10;
  
  display.drawString(0, 12, "Screen is working!");
  
  //String ssid = WiFi.SSID(i);
 
  //String line = ssid + ": " + rssi + " " + encryption;
  //    display.drawString(0, y, line);
      display.display();
  //    delay(10);
    
  

  // Wait a bit before scanning again
  delay(5000);
}
