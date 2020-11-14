
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

#include "ThermostatConfig.h"
#include "ThermostatSDCard.h"
#include "ThermostatState.h"
#include "ThermostatControl.h"
#include "ThermostatUI.h"
#include "ThermostatNetworking.h"

Thermostat::State state;
Thermostat::Config config;
Thermostat::SDCard sdcard;
Thermostat::Control control;
Thermostat::UI ui;
Thermostat::Networking networking;
int quiet_log_control = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Starting configuration");
  try {
    sdcard.setup(config);
  } catch (...) {
    Serial.println("Unhandled exception when loading from sdcard");
  }
  if (config.loaded) {
    state.set_temperature = config.temperature_starting;
    state.variance = config.temperature_variance;
    state.ramp_up_buffer = config.ramp_up_buffer;
    state.cool_down_buffer = config.cool_down_buffer;

    Serial.println("Starting networking");
    networking.setup(config);
  }

  Serial.println("Starting control");
  control.setup();

  Serial.println("Starting UI");
  ui.setup();

  Serial.println("Setup complete");
}

void loop() {
  ui.input(state);
  control.update(state);
  ui.update(state);
  if (config.loaded) {
    networking.update(state);
  }
  if (quiet_log_control++ % 100 == 0) {
    Serial.println("Temperature: " + String(state.actual_temperature) + ", Humidity: " + String(state.actual_humidity) + " Relay: "+String(state.relay_state)+" Set: "+String(state.set_temperature));
  }
}
