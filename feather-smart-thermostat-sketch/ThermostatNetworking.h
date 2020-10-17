#ifndef INCLUDED_THERMOSTAT_WIFI_H
#define INCLUDED_THERMOSTAT_WIFI_H

#include "ThermostatConfig.h"
#include "ThermostatState.h"

namespace Thermostat {

  struct Networking {
    void setup(Config& config);
    void update(State& state);
  };

}

#endif
