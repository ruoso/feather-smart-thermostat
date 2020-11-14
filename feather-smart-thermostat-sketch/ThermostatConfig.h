#ifndef INCLUDED_THERMOSTAT_CONFIG_H
#define INCLUDED_THERMOSTAT_CONFIG_H

#include <string>

namespace Thermostat {

  struct Config {
    int loaded;
    std::string wifi_ssid;
    std::string wifi_password;
    std::string mqtt_broker_host;
    uint16_t mqtt_broker_port;
    std::string mqtt_client_id;
    std::string mqtt_username;
    std::string mqtt_password;
    std::string mqtt_topic_action;
    std::string mqtt_topic_actual_temperature;
    std::string mqtt_topic_actual_humidity;
    std::string mqtt_topic_actual_current;
    std::string mqtt_topic_ramp_up_buffer;
    std::string mqtt_topic_cool_down_buffer;
    std::string mqtt_topic_target_temperature;
    std::string mqtt_topic_temperature_command;
    int temperature_starting;
    float temperature_variance;
    float ramp_up_buffer;
    float cool_down_buffer;
  };
}

#endif
