#ifndef INCLUDED_THERMOSTAT_CONTROL_H
#define INCLUDED_THERMOSTAT_CONTROL_H

#include <Adafruit_SHT31.h>
#include "ThermostatState.h"

namespace Thermostat {

  struct Output {
    const static int pin = 21;
    Output() {
    }
    void setup() {
      pinMode(pin, OUTPUT);
    }
    void update(const State& state) {
      digitalWrite(pin, state.relay_state);
    }
  };

  struct Sensors {
    Adafruit_SHT31 sht31;
    Sensors() {
    }
    void setup() {
      sht31.begin(0x44);
    }
    void update(State& state) {
      state.actual_temperature = sht31.readTemperature();
      state.actual_humidity = sht31.readHumidity();
    }
  };
  
  struct Control {
    Output output;
    Sensors sensors;
    Control() {
    }
    void setup() {
      output.setup();
      sensors.setup();
    }
    void update(State& state) {
      sensors.update(state);
      if (state.actual_temperature < state.set_temperature) {
        state.relay_state = 1;
      } else {
        state.relay_state = 0;
      }
      output.update(state);
    }
  };

}

#endif
