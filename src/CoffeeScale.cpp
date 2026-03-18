#ifndef COFFEE_SCALE_HPP
#define COFFEE_SCALE_HPP

#include "CoffeeScale.hpp"

void CoffeeScale::initializeScale() {
  Serial.println("HX711 Demo");
  loadcell.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  loadcell.set_scale(LOADCELL_DIVIDER);
  loadcell.tare(20);
  Serial.println("Insert the item to be weighed"); 
}

void CoffeeScale::runStateMachine() {
  Serial.print("Reading: ");
  Serial.println(loadcell.get_units(10), 0);
  delay(100);
}

#endif // COFFEE_SCALE_HPP