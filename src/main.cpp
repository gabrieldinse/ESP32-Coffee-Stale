#include "CoffeeScale.hpp" 

CoffeeScale coffeeScale;

void setup() {
  Serial.begin(9600);
  coffeeScale.initializeScale();
  coffeeScale.initializeWebserver();
  coffeeScale.initializeDisplay();
}
 
void loop() {
  coffeeScale.updateStateMachine();
  coffeeScale.runStateMachine();
}
