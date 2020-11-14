#ifndef INCLUDED_THERMOSTAT_CONTROL_H
#define INCLUDED_THERMOSTAT_CONTROL_H

#include <cmath>

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
    const static int current_a_pin = 39;
    float moving_samples[10] = {0,0,0,0,0,0,0,0,0,0};
    int moving_samples_index = 0;
    Sensors() {
    }
    void setup() {
      pinMode(current_a_pin, INPUT);
      sht31.begin(0x44);
    }
    void update(State& state) {
      state.actual_temperature = sht31.readTemperature();
      state.actual_humidity = sht31.readHumidity();

      // 3. The module can measure the positive and negative 20 amps, corresponding to the analog output 100mV / A;
      // 4. There is no the detection current through, the output voltage is VCC / 2;
      // These analog input pins have 12-bit resolution. This means that when you read an analog input, its range may vary from 0 to 4095.
      int measured = analogRead(current_a_pin);
      float normalized = round(((measured * 3.2)/4096)*10)/10;
      float centered = normalized - 1.5;

      // The CPU is already too busy for us to be able to read AC and calculate it correctly. So instead we'll just check that
      // the variance we have had was bigger than 0.1 over the past 10 measurements, which will most definitely be always true
      // when we have current, and always false when we don't.
      moving_samples[moving_samples_index%10] = abs(centered);
      int sample_count = moving_samples_index > 9 ? 10 : moving_samples_index + 1;
      float sum = 0;
      for (int i = 0; i < 10 && i <= moving_samples_index; i++) {
        sum += moving_samples[i];
      }
      float avg = sum / sample_count;
      float variance = 0;
      for (int i = 0; i < 10 && i <= moving_samples_index; i++) {
        float difference = moving_samples[i] - avg;
        variance += difference * difference;
      }

      if (variance > 0.1) {
        state.actual_current = 1;
      } else {
        state.actual_current = 0;
      }

      moving_samples_index++;
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
      if (!std::isnan(state.max_temperature_since_state_set_to_idle)) {
        // let's record how high temperature went since the last cycle
        state.max_temperature_since_state_set_to_idle = std::max(state.actual_temperature, state.max_temperature_since_state_set_to_idle);
      }
      if (!std::isnan(state.min_temperature_since_state_set_to_heat)) {
        // let's record how low the temperature went since the last cycle
        state.min_temperature_since_state_set_to_heat = std::min(state.actual_temperature, state.min_temperature_since_state_set_to_heat);
      }
      if (state.relay_state == 0) {
        if (state.actual_temperature < ((state.set_temperature - state.variance/2)+state.ramp_up_buffer)) {
          if (!std::isnan(state.max_temperature_since_state_set_to_idle)) {
            // we went through a full cycle after turning it on, turning it off, so we now can
            // update the cool_down_buffer, based on the difference between the temperature set when we set to idle
            // versus the max temperature
            state.cool_down_buffer = state.max_temperature_since_state_set_to_idle - state.temperature_on_last_state_set_to_idle;
          }
          state.relay_state = 1;
          state.temperature_on_last_state_set_to_heat = state.actual_temperature;
          state.min_temperature_since_state_set_to_heat = state.actual_temperature;
        }
      } else {
        if (state.actual_temperature > ((state.set_temperature + state.variance/2)-state.cool_down_buffer)) {
          if (!std::isnan(state.min_temperature_since_state_set_to_heat)) {
            // we went through a full cycle after turning it off, turning it on, so we now can
            // update the ramp_up_buffer, based on the difference between the temperature set when we set to heat
            // versus the min temperature
            state.ramp_up_buffer = state.temperature_on_last_state_set_to_heat - state.min_temperature_since_state_set_to_heat;
          }
          state.relay_state = 0;
          state.temperature_on_last_state_set_to_idle = state.actual_temperature;
          state.max_temperature_since_state_set_to_idle = state.actual_temperature;
        }
      }
      output.update(state);
    }
  };

}

#endif
