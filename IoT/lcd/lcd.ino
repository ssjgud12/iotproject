#include <WiFi.h>

#include <NTPClient.h>

#include <WiFiUdp.h>

#include <rgb_lcd.h>

// Replace with your network credentials

const char* ssid = "testssid";

const char* password = "";

// Initialize LCD

rgb_lcd lcd;

WiFiUDP ntpUDP;

// Create an NTPClient

WiFiUDP ntpUDP;

void setup() {

  Serial.begin(115200);

  lcd.begin(16, 2); // Set the LCD size

  lcd.setRGB(255, 0, 0); // Set initial backlight color (red)

  // Connect to Wi-Fi

  WiFi.begin(ssid, password);

  Serial.println("\nConnecting to WiFi Network ..");

  while (WiFi.status() != WL_CONNECTED) {

    Serial.print(".");

    delay(100);

  }

  // Start the NTP client

  timeClient.begin();

}

void loop() {

  // Update the time from NTP server

  timeClient.update();

  // Get the current time in formatted string

  String formattedTime = timeClient.getFormattedTime();

  lcd.setCursor(0, 0);

  lcd.print("Time: " + formattedTime); // Display time on LCD

  // Get the current date

  time_t rawTime = timeClient.getEpochTime();

  struct tm *timeInfo = localtime(&rawTime);

  // Format date with leading zeros

  String formattedDate = String(timeInfo->tm_mday < 10 ? "0" : "") + String(timeInfo->tm_mday) + "/" +

                         String(timeInfo->tm_mon + 1 < 10 ? "0" : "") + String(timeInfo->tm_mon + 1) + "/" +

                         String(timeInfo->tm_year + 1900);

  lcd.setCursor(0, 1 );
}