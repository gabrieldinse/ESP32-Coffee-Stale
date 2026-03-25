#ifndef COFFEE_SCALE_HPP
#define COFFEE_SCALE_HPP

#include "CoffeeScale.hpp"

void CoffeeScale::initializeScale() {
  currentState = State::Initializing; 
  Serial.println("HX711 Demo");
  loadcell.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  loadcell.set_scale(LOADCELL_DIVIDER);
  loadcell.tare(20);
  pinMode(TARE_BUTTON_PIN, INPUT_PULLUP);
  Serial.println("Insert the item to be weighed");
}

void CoffeeScale::runStateMachine() {
  switch (currentState) {
    case State::None:
      break;
    case State::Initializing:
      break;
    case State::TareButtonPressed:
      break;
    case State::WaitingForJar:
      break;
    case State::CoffeeBrewing:
      break;
    case State::NoCoffee:
      break;
    case State::HasCoffee:
      break;
  }
  previousState = currentState;
}

void CoffeeScale::updateStateMachine() {
  // 1. Check if the tare button was pressed
  currentWeight = getWeight();
  if (isTareButtonPressed()) {
    currentState = State::TareButtonPressed;
  }

  if (isJarOnTheScale()){
    if(hasCoffee()) {
      currentState = State::HasCoffee;
    } else {
      currentState = State::NoCoffee;
    }
  } else {
    if (currentState != State::CoffeeBrewing) {
      if (currentState != State::WaitingForJar) {
        currentState = State::WaitingForJar;
        waitingForJarStartTime = millis();
      } else if (millis() - waitingForJarStartTime > FIFTEEN_MINUTES) {
        currentState = State::CoffeeBrewing;
      }
    }
  }
}

bool CoffeeScale::isTareButtonPressed() {
  if (digitalRead(TARE_BUTTON_PIN) == LOW) {
    return true;
  }
  return false;
}

int CoffeeScale::getWeight() {
  return loadcell.get_units(10);
}

bool CoffeeScale::isJarOnTheScale() {
  return currentWeight > JAR_WEIGHT;
}

bool CoffeeScale::hasCoffee() {
  return currentWeight > JAR_WEIGHT + MIN_COFFEE_LEVEL;
}
#endif // COFFEE_SCALE_HPP