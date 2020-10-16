
/***************************************************
 * Quote Display for Adafruit ePaper FeatherWings
 * For use with Adafruit tricolor and monochrome ePaper FeatherWings
 * 
 * Adafruit invests time and resources providing this open source code.
 * Please support Adafruit and open source hardware by purchasing
 * products from Adafruit!
 * 
 * Written by Dan Cogliano for Adafruit Industries
 * Copyright (c) 2019 Adafruit Industries
 * 
 * Notes: 
 * Update the secrets.h file with your WiFi details
 * Uncomment the ePaper display type you are using below.
 * Change the SLEEP setting to define the time between quotes
 */
#define BUSIO_USE_FAST_PINIO 1

#include "ThermostatState.h"
#include "ThermostatControl.h"
#include "ThermostatUI.h"

Thermostat::State state;
Thermostat::Control control;
Thermostat::UI ui;
int quiet_log_control = 0;

void setup() {
  Serial.begin(115200);
  delay(100);
  control.setup();
  ui.setup();
}

void loop() {
  control.update(state);
  delay(50);
  ui.update(state);
  control.update(state);
  delay(50);
  if (quiet_log_control++ % 100 == 0) {
    Serial.println("Temperature: " + String(state.actual_temperature) + ", Humidity: " + String(state.actual_humidity) + " Relay: "+String(state.relay_state)+" Set: "+String(state.set_temperature));
  }
}
