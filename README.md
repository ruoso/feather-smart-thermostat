# Feather smart thermostat

## Parts

 * a [feather huzzah](https://www.adafruit.com/product/3619)
 
 * a [2.13 e-ink monochrome](https://www.adafruit.com/product/4195)
   wing
 
 * a [I2C SHT31-D](https://www.adafruit.com/product/2857) temperature
   and humity sensor
 
 * a single channel relay
 
 * a current sensor
 
 * three push buttons
 
 * safety "temperature is too low" disc thermostat
 
 * safety "temperature is too high" disc thermostat

## Design Approach

### "Dumb" safety

Safety thermostats override the system to always turn on when it's
getting too cold and always turn off when it gets too hot. This will
be achieved by putting the "low temperature" thermostat in parallel
with the relay that is fed from the smart part of the thermostat, then
connect them both in serial with the "high termperature" thermostat.

Those are driven by fixed-temperature disc thermostats.

### Monitor Current

Since the safety thermostats may trigger the current on or off
independently of the "smart" logic, we will monitor and report the
themperature so we can tell what the real state is.

### Stand-alone device

The thermostat will work as a stand-alone device first, with three
push buttons to raise and lower the set temperature as well as utility
functions, such as changing from celsius to farenheight or forcing a
reset.

### MQTT integration

The "smart" part of the thermostat will be driven by MQTT integrations
via wifi, the thermostat will publish data for:

 * Actual temperature
 * Actual humidity
 * Actual current
 * Relay status
 * Set temperature

And the thermostat will receive command for:

 * Set temperature

The idea is that it should always be possible to override the current
set temperature from the local device, and that should be reflected to
the automation system, while at the same time it should be possible
for the automation system to override the manually set temperature.

### Configuration

This will read a json file named `thermostat.json` in the root of the sdcard.

The sample file below explains the expected format:

```
{
    "wifi": {
        "ssid": "",
        "password": ""
    },
    "mqtt": {
        "broker_host": "",
        "broker_port": 1883,
        "clientid": "",
        "username": "",
        "password": "",
        "topics": {
            "action": "",
            "actual_temperature": "",
            "actual_humidity": "",
            "actual_current": "",
            "target_temperature": "",
            "ramp_up_buffer": "",
            "cool_down_buffer": "",
            "temperature_command": ""
        }
    },
    "temperature": {
        "starting": 21,
        "variance": 1,
        "ramp_up_buffer": 0.1,
        "cool_down_buffer": 0.1
    }
}

```

Most items are self-explanatory. The temperature section requires some explanation:

 * `starting`: Value of target temperature on reset, such as when
   returning from a power outage.

 * `variance`: This configures how wide should the control allow the
   temperature to vary. For instance, if you have the target set to
   21, and a variance set to 1, the ambient temperature should vary
   between 20.5 and 21.5 degrees.

 * `ramp_up_buffer` (Optional): How many degrees before the low end of
   the variance to turn the heater on, such that we don't get below
   the target variance due to the ramp up time of the heater
   element. This is the initial value, which will be automatically
   adjusted over time.

 * `cool_down_buffer` (Optional): How many degrees before the high end
   of the variance to turn the heater off, such that we don't get
   above the target variance due to residual heat after we turn the
   heater element off. This is the initial value, which will be
   automatically adjusted over time.
