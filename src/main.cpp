#include "CoffeeScale.hpp" 

CoffeeScale coffeeScale;

LCD_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  coffeeScale.initializeScale();
  coffeeScale.initializeWebserver();
  coffeeScale.initializeDisplay();

  // Display testing
  lcd.begin();
  delay(500);  // Wait for LCD initialization
  lcd.backlight();
  delay(200);  // Wait for backlight to activate
}
 
void loop() {
  coffeeScale.updateStateMachine();
  coffeeScale.runStateMachine();
  // LCD Display
  lcd.clear();
  lcd.print("Coffee Scale");
  lcd.setCursor(0, 1);
  lcd.print("Weight: ");
  //lcd.print(reading, 0);
  delay(100);
}
