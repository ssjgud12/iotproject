#include <Wire.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <rgb_lcd.h>
#include <Keypad.h>
#define ROW_NUM     4 // four rows
#define COLUMN_NUM  3 // three columns
// Replace with your network credentials
const char* ssid = "iPhone";
const char* password = "Alvin123";
rgb_lcd lcd;
WiFiUDP ntpUDP;
// Create an NTPClient
NTPClient timeClient(ntpUDP, "ie.pool.ntp.org", 3600, 60000); // 3600 is the UTC offset in seconds
char keys[ROW_NUM][COLUMN_NUM] = {
 {'1', '2', '3'},
 {'4', '5', '6'},
 {'7', '8', '9'},
 {'*', '0', '#'}
};
byte pin_rows[ROW_NUM] = {18, 5, 17, 16}; // GPIO18, GPIO5, GPIO17, GPIO16 connect to the row pins
byte pin_column[COLUMN_NUM] = {4, 0, 2};  // GPIO4, GPIO0, GPIO2 connect to the column pins
Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );
const String PAssword = "7890"; // change your password here
String input_password;
const int buzz = 34;
const int trigPin = 15;
const int echoPin = 13;
const int led1 = 32;
const int led2 = 33;
const int led3 = 27;
int L;
int D;
#define sw1 23
int currentState;
long duration;
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701
float distanceCm;
float distanceInch;
const int C4 = 261;
const int D4 = 294;
const int E4 = 329;
const int F4 = 349;
const int G4 = 392;
const int B4 = 466;
const int C5 = 523;
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
    input_password.reserve(32); // maximum input characters is 33, change if needed
 }
 // Start the NTP client
 timeClient.begin();
 pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
 pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
 pinMode(buzz, OUTPUT);
 pinMode(led1, OUTPUT);
 pinMode(led2, OUTPUT);
 pinMode(sw1, INPUT_PULLUP);
 input_password.reserve(32); // maximum input characters
}
void loop() {
  digitalWrite(led2,HIGH);
  //char key = keypad.getKey();
  char key = '\0';
 timeClient.update();
 // Get the current time in formatted string
 String formattedTime = timeClient.getFormattedTime();
 // Get the current date from epoch time
 time_t rawTime = timeClient.getEpochTime();
 struct tm *timeInfo = localtime(&rawTime);
 // Format date and time correctly
 String formattedDate = String(timeInfo->tm_mday < 10 ? "0" : "") + String(timeInfo->tm_mday) + "/" +
                        String(timeInfo->tm_mon + 1 < 10 ? "0" : "") + String(timeInfo->tm_mon + 1) + "/" +
                        String(timeInfo->tm_year + 1900);
 // Display the formatted date and time on the LCD
 lcd.clear(); // Clear LCD screen before updating
 lcd.setCursor(0, 0);
 lcd.print("Time: " + formattedTime);  // Time like HH:MM:SS
 lcd.setCursor(0, 1);
 lcd.print("Date: " + formattedDate); // Date like DD/MM/YYYY
 delay(1); // Update every second
 // Clears the trigPin
 digitalWrite(trigPin, LOW);
 delay(2000);
 // Sets the trigPin on HIGH state for 2 seconds
 digitalWrite(trigPin, HIGH);
 delay(2000);
 digitalWrite(trigPin, LOW);
 // Reads the echoPin, returns the sound wave travel time in microseconds
 duration = pulseIn(echoPin, HIGH);
 // Calculate the distance
 distanceCm = duration * SOUND_SPEED / 2;
 // Convert to inches
 distanceInch = distanceCm * CM_TO_INCH;
currentState = digitalRead(sw1);
while(currentState == LOW)
{
    digitalWrite(led1,LOW);
    Serial.print("Distance (cm): ");
    Serial.println(distanceCm);
    Serial.print("Distance (inch): ");
    Serial.println(distanceInch);
    delay(10);

      // Security system is ON
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Security System");
      lcd.setCursor(0,1);
      lcd.print("Activated");
      delay (1000);
      L = 1;
      D = 1;
        break;
}
     
   if (L = 1)
   {
     digitalWrite(led1,HIGH);
    char key = keypad.getKey();
    if(key == '1')
    {
       digitalWrite(led1,LOW);
       digitalWrite(led2,HIGH);
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Security System");
       lcd.setCursor(0,1);
       lcd.print("Deactivated");
    }
   }
  digitalWrite(led2,LOW);
   }



