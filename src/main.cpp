#include "CoffeeScale.hpp" 

LCD_I2C lcd(0x27, 16, 2);
CoffeeScale coffeeScale(lcd);

void setup() {
  Serial.begin(9600);
  coffeeScale.initializeScale();
  coffeeScale.initializeWebserver();
  coffeeScale.initializeDisplay();
}
 
void loop() {
  coffeeScale.updateStateMachine();
  coffeeScale.runStateMachine();
  delay(100);
}
