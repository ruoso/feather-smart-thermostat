#ifndef INCLUDED_THERMOSTAT_CONTROL_H
#define INCLUDED_THERMOSTAT_CONTROL_H

#include <Adafruit_SHT31.h>
#include "ThermostatState.h"
#include "ThermostatConfig.h"

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
    float temp_on_last_change;
    Control() {
    }
    void setup() {
      output.setup();
      sensors.setup();
    }
    void update(State& state) {
      sensors.update(state);
      if (state.relay_state == 0) {
        if (state.actual_temperature < state.set_temperature - state.variance/2) {
          state.relay_state = 1;
        }
      } else {
        if (state.actual_temperature > state.set_temperature + state.variance/2) {
          state.relay_state = 0;
        }
      }
      output.update(state);
    }
  };

}

#endif
