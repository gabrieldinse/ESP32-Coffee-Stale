
#include "HX711.h"
 
#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

const int ledPin = 15; // Pin number for the LED

void setup() {

  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT); // Set the LED pin as an output
}

void loop() {
  int result = myFunction(2, 3);
  Serial.println(result);
  delay(1000);
  digitalWrite(ledPin, HIGH); // Turn the LED on
  delay(1000);
  digitalWrite(ledPin, LOW); // Turn the LED on
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}