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


