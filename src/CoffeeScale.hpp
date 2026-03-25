#pragma once

#include <Arduino.h>
#include "HX711.h"

// HX711 circuit wiring
#define LOADCELL_DOUT_PIN 16  // D21 pin on board
#define LOADCELL_SCK_PIN 4   // D22 pin on board
#define TARE_BUTTON_PIN 15  // D23 pin on board

// TODO: Check the weight of the empty jar and set it here
#define JAR_WEIGHT 100 // grams
#define MIN_COFFEE_LEVEL 20 // grams

#define FIFTEEN_MINUTES 15 * 60 * 1000

// 2. Adjustment settings
// Coke: 380g grams
// Reading: ~152950
// 152950 / 380 = 424.86111111111111111111111111111
const float LOADCELL_DIVIDER = static_cast<float>(152950) / 380;

enum class State {
    None = 0,
    Initializing,
    TareButtonPressed,
    WaitingForJar,
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

    void updateStateMachine();
    void runStateMachine();

    bool isTareButtonPressed();
    int getWeight();
    bool isJarOnTheScale();
    bool hasCoffee();
private:
    State currentState = State::None;
    State previousState = State::None;
    int currentWeight = 0;
    unsigned long waitingForJarStartTime = 0;

    HX711 loadcell;
};