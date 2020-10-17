#include "ThermostatNetworking.h"

#include <WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

using namespace Thermostat;

static Config *config;
static State *state;

static unsigned long last_wifi_attempt;
static unsigned long count_wifi_attempt;
static unsigned long wifi_online;
static unsigned long last_mqtt_attempt;
static unsigned long count_mqtt_attempt;
static unsigned long mqtt_online;

static WiFiClient *wificlient;
static Adafruit_MQTT_Client *mqttclient;

template <typename T>
struct publishing_helper {
  unsigned long time;
  T value;
  Adafruit_MQTT_Publish *topic;
  int publish_count;
  bool always_publish;
  bool should_publish(T newval) {
    unsigned long now = millis();
    if (!publish_count || (value != newval && (always_publish || (now - time > 60000))) || now - time > 600000) {
      publish_count++;
      value = newval;
      time = now;
      return true;
    }
    return false;
  }
  void publish(T newval) {
    if (should_publish(newval)) {
      if (topic->publish(newval)) {
        Serial.println("Published new data to MQTT");
      } else {
        Serial.println("Failed to publish new data to MQTT");
      }
    }
  }
};

static publishing_helper<const char*> ph_action;
static publishing_helper<float> ph_actual_temperature;
static publishing_helper<float> ph_actual_humidity;
static publishing_helper<float> ph_actual_current;
static publishing_helper<float> ph_target_temperature;

static  Adafruit_MQTT_Subscribe *mqtt_topic_temperature_command;

static void attempt_wifi_connection() {
  last_wifi_attempt = millis();
  count_wifi_attempt++;
  Serial.println("Attempting WiFi connection");
  WiFi.begin(config->wifi_ssid.c_str(), config->wifi_password.c_str());
  if (WiFi.status() == WL_CONNECTED) {
    if (wifi_online == 0) {
      Serial.println("Connected to wifi");
    }
    wifi_online = 1;
  } else {
    wifi_online = 0;
  }
}

static void attempt_mqtt_connection() {
  last_mqtt_attempt = millis();
  count_mqtt_attempt++;
  Serial.println("Attempting MQTT connection");
  mqttclient->connect();
  if (mqttclient->connected()) {
    if (mqtt_online == 0) {
      Serial.println("Connected to mqtt");
    }
    mqtt_online = 1;
  } else {
    mqtt_online = 0;
  }
}

static bool   target_temperature_received_new;
static double target_temperature_received_val;
static void target_temperature_callback(double newval) {
  target_temperature_received_new = true;
  target_temperature_received_val = newval;
  Serial.println("Received from subscription");
}

void Networking::setup(Config& config_in) {
  config = &config_in;

  wificlient = new WiFiClient();
  mqttclient = new Adafruit_MQTT_Client(
    wificlient,
    config->mqtt_broker_host.c_str(),
    config->mqtt_broker_port,
    config->mqtt_client_id.c_str(),
    config->mqtt_username.c_str(),
    config->mqtt_password.c_str()
  );
  
  ph_action.topic = new Adafruit_MQTT_Publish(mqttclient, config->mqtt_topic_action.c_str());
  ph_action.always_publish = 1;
  ph_actual_temperature.topic = new Adafruit_MQTT_Publish(mqttclient, config->mqtt_topic_actual_temperature.c_str());
  ph_actual_humidity.topic = new Adafruit_MQTT_Publish(mqttclient, config->mqtt_topic_actual_humidity.c_str());
  ph_actual_current.topic = new Adafruit_MQTT_Publish(mqttclient, config->mqtt_topic_actual_current.c_str());
  ph_target_temperature.topic = new Adafruit_MQTT_Publish(mqttclient, config->mqtt_topic_target_temperature.c_str());
  ph_target_temperature.always_publish = 1;
  mqtt_topic_temperature_command = new Adafruit_MQTT_Subscribe(mqttclient, config->mqtt_topic_temperature_command.c_str());
  mqtt_topic_temperature_command->setCallback(target_temperature_callback);
  mqttclient->subscribe(mqtt_topic_temperature_command);

  count_wifi_attempt = 0;
  count_mqtt_attempt = 0;
  attempt_wifi_connection();
  if (WiFi.status() == WL_CONNECTED) {
    attempt_mqtt_connection();
  }
}

static void publish_updates(State& state) {
  ph_action.publish(state.relay_state ? "\"heating\"" : "\"idle\"");
  ph_actual_temperature.publish(state.actual_temperature);
  ph_actual_humidity.publish(state.actual_humidity);
  ph_actual_current.publish(state.actual_current);
  ph_target_temperature.publish(state.set_temperature);
}

void Networking::update(State& state) {
  if (WiFi.status() == WL_CONNECTED) {
    if (mqttclient->connected()) {
      mqttclient->processPackets(100);
      publish_updates(state);
      if (target_temperature_received_new) {
        target_temperature_received_new = 0;
        state.set_temperature = target_temperature_received_val;
      }
    } else {
      if (mqtt_online == 1) {
        Serial.println("Lost mqtt connection");
      }
      mqtt_online = 0;
      if (millis() - last_mqtt_attempt > 60000) {
        count_mqtt_attempt = 0;
      }
      if (count_mqtt_attempt < 10) {
        attempt_mqtt_connection();
      }
    }
  } else {
    mqtt_online = 0;
    if (wifi_online == 1) {
      Serial.println("Lost wifi connection");
    }
    if (millis() - last_wifi_attempt > 60000) {
      count_wifi_attempt = 0;
    }
    if (count_wifi_attempt < 10) {
      attempt_wifi_connection();
    }
  }  
}
