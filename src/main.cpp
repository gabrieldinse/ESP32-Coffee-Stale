#include "HX711.h"
#include <Arduino.h>

// 1. HX711 circuit wiring
//#define LOADCELL_DOUT_PIN 11 // D21
//#define LOADCELL_SCK_PIN 14 // D22
#define LOADCELL_DOUT_PIN 21  // D21 pin on board
#define LOADCELL_SCK_PIN 22   // D22 pin on board

// 2. Adjustment settings
//const long LOADCELL_OFFSET = 50682624;
//const long LOADCELL_DIVIDER = 5895655;

HX711 loadcell;
 
void setup() {
  // // 3. Initialize library
  // loadcell.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  // loadcell.set_scale(LOADCELL_DIVIDER);
  // loadcell.set_offset(LOADCELL_OFFSET);

  // // 4. Acquire reading
  // Serial.print("Weight: ");
  // Serial.println(loadcell.get_units(10), 2);

  Serial.begin(9600);
  Serial.println("HX711 Demo");
  loadcell.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);  // ✅ REQUIRED !!!

  // Acquire reading without blocking
  //if (loadcell.wait_ready_timeout(5000)) {
  //    long reading = loadcell.get_units(10);
  //    Serial.print("Weight: ");
  //    Serial.println(reading, 2);
  //} else {
  //    Serial.println("Batata HX711 not found.");
  //}
 
  loadcell.tare(20);                // Fixa o peso como tara
  Serial.println("Insira o item para Pesar"); 
}
 
void loop() {
  Serial.print("Reading: ");
  Serial.println(loadcell.get_value(10),0);
  delay(100);
}
