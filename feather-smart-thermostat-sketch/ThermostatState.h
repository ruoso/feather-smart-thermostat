#ifndef INCLUDED_THERMOSTAT_STATE_H
#define INCLUDED_THERMOSTAT_STATE_H

#define SET_TEMPERATURE_AT_REBOOT 25

namespace Thermostat {
  struct State {
    float actual_temperature;
    float actual_humidity;
    float actual_current;
    bool  relay_state;
    bool  online;
    bool  convert_temperature_to_f;
    float set_temperature = SET_TEMPERATURE_AT_REBOOT;
  };
}

#endif
