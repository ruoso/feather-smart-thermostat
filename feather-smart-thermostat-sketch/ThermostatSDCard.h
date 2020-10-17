#ifndef INCLUDED_THERMOSTAT_SDCARD_H
#define INCLUDED_THERMOSTAT_SDCARD_H

#include <SD.h>
#include <ArduinoJson.h>

namespace Thermostat {

  namespace {
    const static int max_size  = 2047;
    static uint8_t configuration_contents[max_size+1];
  }

  struct SDCard {
    const static int sd_cs     = 14;

    SDCard() {
    }

    void setup(Config &config) {
      config.loaded = 0;

      Serial.println("Will initialize SD card");

      if (!SD.begin(sd_cs)) {
        Serial.println("Failed to initialize sd card.");
        return;
      }

      Serial.println("SD Card initialized, checking for configuration file");

      std::string configuration_filename = "/thermostat.json";
      if (!SD.exists(configuration_filename.c_str())) {
        Serial.println("thermostat.json not found in sd card.");
        return;
      }
    
      Serial.println("Configuration file found, openning");

      File configuration_file = SD.open(configuration_filename.c_str(), FILE_READ);
      if (!configuration_file) {
        Serial.println("Failed to open thermostat.json.");
        return;
      }

      int configuration_size = configuration_file.size();
      if (configuration_size > max_size) {
        Serial.println("Configuration file too large.");
        return;
      } else if (configuration_size == 0) {
        Serial.println("Configuration file was empty.");
        return;
      }

      Serial.println("Will read the contents");

      memset(configuration_contents, 0, max_size+1);
      configuration_file.read(configuration_contents, max_size);

      Serial.println("Will parse the json");

      DynamicJsonDocument doc(max_size);
      DeserializationError error = deserializeJson(doc, String((char*)configuration_contents));
      if (error) {
        Serial.println("Invalid json in configuration file.");
        return;
      }

      Serial.println("Will load the configuration from the parsed json file");

      Serial.println("Reading wifi config");

      if (!doc.containsKey("wifi")) {
        Serial.println("Missing wifi configuration");
        return;
      }
      JsonVariant j_wifi = doc["wifi"];

      Serial.println("Reading wifi ssid config");

      if (j_wifi.containsKey("ssid")) {
        config.wifi_ssid = j_wifi["ssid"].as<char*>();
      } else {
        Serial.println("Missing configuration key: wifi.ssid");
        return;
      }
      
      Serial.println("Reading wifi password config");

      if (j_wifi.containsKey("password")) {
        config.wifi_password = j_wifi["password"].as<char*>();
      } else {
        Serial.println("Missing configuration key: wifi.password");
        return;
      }
 
      Serial.println("Reading mqtt config");

      if (!doc.containsKey("mqtt")) {
        Serial.println("Missing mqtt configuration");
        return;
      }
      JsonVariant j_mqtt = doc["mqtt"];

      if (j_mqtt.containsKey("broker_host")) {
        config.mqtt_broker_host = j_mqtt["broker_host"].as<char*>();
      } else {
        Serial.println("Missing configuration key: mqtt.broker_host");
        return;
      }
 
      if (j_mqtt.containsKey("mqtt_broker_port")) {
        int port = j_mqtt["broker_port"].as<int>();
        if (port < 0 || port >= 65536) {
          Serial.println("Invalid mqtt.broker_port");
          return;
        }
        config.mqtt_broker_port = port;
      } else {
        config.mqtt_broker_port = 1883;
      }

      if (j_mqtt.containsKey("clientid")) {
        config.mqtt_client_id = j_mqtt["clientid"].as<char*>();
      } else {
        Serial.println("Missing configuration key: mqtt.clientid");
        return;
      }
 
      if (j_mqtt.containsKey("username")) {
        config.mqtt_username = j_mqtt["username"].as<char*>();
      } else {
        Serial.println("Missing configuration key: mqtt.username");
        return;
      }

      if (j_mqtt.containsKey("password")) {
        config.mqtt_password = j_mqtt["password"].as<char*>();
      } else {
        Serial.println("Missing configuration key: mqtt.password");
        return;
      }

      Serial.println("Reading mqtt topics config");

      if (!j_mqtt.containsKey("topics")) {
        Serial.println("Missing mqtt.topics configuration");
        return;
      }
      JsonVariant j_topics = j_mqtt["topics"];

      if (j_topics.containsKey("action")) {
        config.mqtt_topic_action = j_topics["action"].as<char*>();
      } else {
        Serial.println("Missing configuration key: mqtt.topics.action");
        return;
      }

      if (j_topics.containsKey("actual_temperature")) {
        config.mqtt_topic_actual_temperature = j_topics["actual_temperature"].as<char*>();
      } else {
        Serial.println("Missing configuration key: mqtt.topics.actual_temperature");
        return;
      }

      if (j_topics.containsKey("actual_humidity")) {
        config.mqtt_topic_actual_humidity = j_topics["actual_humidity"].as<char*>();
      } else {
        Serial.println("Missing configuration key: mqtt.topics.actual_humidity");
        return;
      }

      if (j_topics.containsKey("actual_current")) {
        config.mqtt_topic_actual_current = j_topics["actual_current"].as<char*>();
      } else {
        Serial.println("Missing configuration key: mqtt.topics.actual_current");
        return;
      }

      if (j_topics.containsKey("target_temperature")) {
        config.mqtt_topic_target_temperature = j_topics["target_temperature"].as<char*>();
      } else {
        Serial.println("Missing configuration key: mqtt.topics.target_temperature");
        return;
      }

      if (j_topics.containsKey("temperature_command")) {
        config.mqtt_topic_temperature_command = j_topics["temperature_command"].as<char*>();
      } else {
        Serial.println("Missing configuration key: mqtt.topics.temperature_command");
        return;
      }

      Serial.println("Reading temperature config");

      if (!doc.containsKey("temperature")) {
        Serial.println("Missing temperature configuration");
        return;
      }
      JsonVariant j_temperature = doc["temperature"];
     
      if (j_temperature.containsKey("starting")) {
        config.temperature_starting = j_temperature["starting"].as<int>();
      } else {
        Serial.println("Missing configuration key: temperature.starting");
        return;
      }

      if (j_temperature.containsKey("variance")) {
        config.temperature_variance = j_temperature["variance"].as<int>();
      } else {
        Serial.println("Missing configuration key: temperature.variance");
        return;
      }

      Serial.println("Configuration loaded.");
      config.loaded = 1;

    }
  };
  
}

#endif
