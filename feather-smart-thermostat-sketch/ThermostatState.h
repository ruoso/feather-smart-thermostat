#ifndef INCLUDED_THERMOSTAT_STATE_H
#define INCLUDED_THERMOSTAT_STATE_H

#include <cmath>

namespace Thermostat {
  struct State {
    float actual_temperature;
    float actual_humidity;
    float actual_current;
    bool  relay_state;
    bool  wifi_online;
    bool  mqtt_online;
    bool  convert_temperature_to_f;
    float set_temperature = 12;
    float variance = 1;
    float temperature_on_last_state_set_to_idle = std::nanf("");
    float max_temperature_since_state_set_to_idle = std::nanf("");
    float temperature_on_last_state_set_to_heat = std::nanf("");
    float min_temperature_since_state_set_to_heat = std::nanf("");
    float ramp_up_buffer = 0;
    float cool_down_buffer = 0;
  };
}

#endif
