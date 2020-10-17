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
    const static int current_a_pin = 39;
    float moving_average[10];
    int moving_average_count;
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
      // on average we have had a signal bigger than 0.1 over the past 10 measurements, which will most definitely be always true
      // when we have current, and always false when we don't.
      moving_average[(moving_average_count++)%10] = abs(centered);
      float sum = 0;
      for (int i = 0; i < 10 && i <= moving_average_count; i++) {
        sum += moving_average[i];
      }
      float avg = sum / ( moving_average_count > 10 ? 10 : moving_average_count + 1 );
      if (avg > 0.1) {
        state.actual_current = 1;
      } else {
        state.actual_current = 0;
      }
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
