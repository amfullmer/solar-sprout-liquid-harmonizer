# Solar Sprout Liquid Harmonizer

The SolarSprout Liquid Harmonizer is a zone-based, solar-powered irrigation system made with ESP32 WiFi boards, drip hosing, and multiple moisture meters.
The goal of this project is to provide automated, precision watering for a multitude of plants all through a IoT interface.

This project is still very much a work in progress!

# Project Overview

Currently, we are working on the C++ embedded code needed to operate the moisture sensors. These sensors will evaluate the moisture in the soil and then turn on a solenoid valve to water a specific zone. 

To start, we are using LEDs as a placeholder to test this design.

# Web CLient
Once we have the device working and communicating, we will implement a web client where users can:
- Monitor current moisture levels
- Manually control valves to water on demand
- See water rate over time (helpful to understand outdoor conditions)
- Compare monthly/yearly data with weather reporting to understand local ecosystem and watering needs based on zone

# Current Device Notes
We are currently using ESP32 Wifi boards connected to cheap moisture sensors. We're still in the breadboard phase, but will be adding:
- Solar power panels and battery
- Water proof chasis
- Relays
- Solenoid valves
- Drip lines (these will be different based on the amount of areas covered by the zone).


