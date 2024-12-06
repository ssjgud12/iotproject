#include <Keypad.h>
#include <WiFi.h>

#include <NTPClient.h>

#include <WiFiUdp.h>

#include <rgb_lcd.h>

#define ROW_NUM     4 // four rows
#define COLUMN_NUM  3 // three columns


const int trigPin = 15;
const int echoPin = 13;
long duration;
float cms, inches;
const char* ssid = "testssid";

const char* password = "";

rgb_lcd lcd;

WiFiUDP ntpUDP;

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte pin_rows[ROW_NUM] = {18,5,17,16}; // GPIO18, GPIO5, GPIO17, GPIO16 connect to the row pins
byte pin_column[COLUMN_NUM] = {4,0,2};  // GPIO4, GPIO0, GPIO2 connect to the column pins

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

NTPClient timeClient(ntpUDP, "ie.pool.ntp.org", 3600, 60000); // 3600 is the UTC offset in seconds


void setup() {
 Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  
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
  digitalWrite(trigPin,LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);



duration = pulseIn(echoPin,HIGH);

cms = (duration/2) / 29.1;
inches = (duration/2) / 74;


Serial.print(inches);
Serial.print("in ");
Serial.print(cms);
Serial.print("cm");
Serial.println();

  delay(250);

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
