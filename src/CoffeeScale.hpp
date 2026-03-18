#pragma once

#include <Arduino.h>
#include "HX711.h"

// HX711 circuit wiring
#define LOADCELL_DOUT_PIN 16  // D21 pin on board
#define LOADCELL_SCK_PIN 4   // D22 pin on board

// 2. Adjustment settings
// Coke: 380g grams
// Reading: ~152950
// 152950 / 380 = 424.86111111111111111111111111111
const float LOADCELL_DIVIDER = static_cast<float>(152950) / 380;

enum class States {
    None = 0,
    Initializing,
    NoJar,
    CoffeeBrewing,
    NoCoffee,
    HasCoffee,
};

class CoffeeScale {
public:
    void initializeScale();
    void initializeWebserver() {
        Serial.println("Webserver initialized");
    }
    void initializeDisplay() {
        Serial.println("Display initialized");
    }

    void updateStateMachine() {}
    void runStateMachine();

private:
    HX711 loadcell;
};