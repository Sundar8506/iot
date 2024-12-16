/*
 * This ESP8266 NodeMCU code was developed by newbiely.com
 *
 * This ESP8266 NodeMCU code is made available for public use without any restriction
 *
 * For comprehensive instructions and wiring diagrams, please visit:
 * https://newbiely.com/tutorials/esp8266/esp8266-ultrasonic-sensor-piezo-buzzer
 */

#include "pitches.h"

#define D1 5 // Define D1 as pin 5
#define D2 4 // Define D1 as pin 5
#define D7 13 // Define D1 as pin 5
#define TRIG_PIN   D1 // The ESP8266 pin D1 connected to Ultrasonic Sensor's TRIG pin
#define ECHO_PIN   D2 // The ESP8266 pin D2 connected to Ultrasonic Sensor's ECHO pin
#define BUZZER_PIN D7 // The ESP8266 pin D7 connected to Piezo Buzzer's pin
#define DISTANCE_THRESHOLD 50 // centimeters

float duration_us, distance_cm;

// notes in the melody:
int melody[] = {
  NOTE_E7, NOTE_E5, NOTE_E7,
  NOTE_E5, NOTE_E7, NOTE_E5,
  NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
  NOTE_E5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_E7, NOTE_E7, NOTE_E5, NOTE_E5,
  NOTE_E7, NOTE_D7, NOTE_D7, NOTE_E7,
  NOTE_D7, NOTE_G5
};

// note durations: 4 = quarter note, 8 = eighth note, etc, also called tempo:
int noteDurations[] = {
  8, 8, 4,
  8, 8, 4,
  8, 8, 8, 8,
  2,
  8, 8, 8, 8,
  8, 8, 8, 16, 16,
  8, 8, 8, 8,
  4, 4
};

void setup() {
  pinMode(TRIG_PIN, OUTPUT);   // Configure the ESP8266 pin to the output mode
  pinMode(ECHO_PIN, INPUT);    // Configure the ESP8266 pin to the input mode
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
    buzzer(); // play a song

  delay(500);
}

void buzzer() {
  // iterate over the notes of the melody:
  int size = sizeof(noteDurations) / sizeof(int);

  for (int thisNote = 0; thisNote < size; thisNote++) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(BUZZER_PIN, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // The note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(BUZZER_PIN);
  }
}
