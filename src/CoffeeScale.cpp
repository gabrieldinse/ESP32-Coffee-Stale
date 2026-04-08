#ifndef COFFEE_SCALE_HPP
#define COFFEE_SCALE_HPP

#include "CoffeeScale.hpp"

CoffeeScale::CoffeeScale(LCD_I2C& display) : display(display) {}

void CoffeeScale::initializeDisplay() {
  display.begin();
  delay(500);
  display.backlight();
  delay(200);
  Serial.println("Display initialized");
}

void CoffeeScale::initializeScale() {
  currentState = State::Initializing; 
  Serial.println("HX711 Demo");
  loadcell.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  loadcell.set_scale(LOADCELL_DIVIDER);
  loadcell.tare(20);
  pinMode(TARE_BUTTON_PIN, INPUT_PULLUP);
  Serial.println("Insert the item to be weighed");
}

void CoffeeScale::renderWeightField() {
  if (hasDisplayedWeight && displayedWeight == currentWeight) {
    return;
  }

  display.setCursor(8, 1);
  String weightText = String(currentWeight) + "g";
  while (weightText.length() < 8) {
    weightText += " ";
  }
  display.print(weightText);

  displayedWeight = currentWeight;
  hasDisplayedWeight = true;
}

void CoffeeScale::runStateMachine() {
  const bool stateChanged = currentState != previousState;

  if (stateChanged) {
    display.clear();
  }

  switch (currentState) {
    case State::None:
      break;
    case State::Initializing:
      if (stateChanged) {
        display.print("Initializing...");
      }
      break;
    case State::TareButtonPressed:
      if (stateChanged) {
        display.print("Taring scale...");
      }
      break;
    case State::WaitingForJar:
      if (stateChanged) {
        display.print("Waiting for jar");
      }
      break;
    case State::CoffeeBrewing:
      if (stateChanged) {
        display.print("Brewing...");
      }
      break;
    case State::NoCoffee:
      if (stateChanged) {
        display.print("No coffee");
        display.setCursor(0, 1);
        display.print("Weight: ");
        hasDisplayedWeight = false;
      }
      renderWeightField();
      break;
    case State::HasCoffee:
      if (stateChanged) {
        display.print("Coffee ready");
        display.setCursor(0, 1);
        display.print("Weight: ");
        hasDisplayedWeight = false;
      }
      renderWeightField();
      break;
  }
  previousState = currentState;
}

void CoffeeScale::updateStateMachine() {
  // 1. Check if the tare button was pressed
  currentWeight = getWeight();
  Serial.println("currentWeight: " + String(currentWeight)  );
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