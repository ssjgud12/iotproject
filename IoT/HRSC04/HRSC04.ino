const int trigPin = 15;
const int echoPin = 13;
long duration;
float cms, inches;

void setup() {
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
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
}