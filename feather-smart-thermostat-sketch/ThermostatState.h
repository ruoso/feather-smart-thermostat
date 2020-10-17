#ifndef INCLUDED_THERMOSTAT_STATE_H
#define INCLUDED_THERMOSTAT_STATE_H

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
  };
}

#endif
