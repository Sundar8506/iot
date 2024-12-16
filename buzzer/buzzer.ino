/*
 * This ESP8266 NodeMCU code was developed by newbiely.com
 *
 * This ESP8266 NodeMCU code is made available for public use without any restriction
 *
 * For comprehensive instructions and wiring diagrams, please visit:
 * https://newbiely.com/tutorials/esp8266/esp8266-ultrasonic-sensor-piezo-buzzer
 */
#define D1 5 // Define D1 as pin 5
#define D2 4 // Define D1 as pin 5
#define D7 13 // Define D1 as pin 5
#define TRIG_PIN   D1 // The ESP8266 pin D1 connected to Ultrasonic Sensor's TRIG pin
#define ECHO_PIN   D2 // The ESP8266 pin D2 connected to Ultrasonic Sensor's ECHO pin
#define BUZZER_PIN D7 // The ESP8266 pin D7 connected to Piezo Buzzer's pin
#define DISTANCE_THRESHOLD 50 // centimeters

float duration_us, distance_cm;

void setup() {
  Serial.begin (9600);         // Initialize the Serial to communicate with the Serial Monitor.
  pinMode(TRIG_PIN, OUTPUT);   // Configure the ESP8266 pin to the output mode
  pinMode(ECHO_PIN, INPUT);    // Configure the ESP8266 pin to the input mode
  pinMode(BUZZER_PIN, OUTPUT); // Configure the ESP8266 pin to the output mode
}

void loop() {
  // Produce a 10-microsecond pulse to the TRIG pin.
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the pulse duration from the ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);
  // calculate the distance
  distance_cm = 0.017 * duration_us;

  if (distance_cm < DISTANCE_THRESHOLD)
    digitalWrite(BUZZER_PIN, HIGH);
       // turn on Piezo Buzzer
  else
    digitalWrite(BUZZER_PIN, LOW); 
   // turn off Piezo Buzzer

  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  delay(500);
}
