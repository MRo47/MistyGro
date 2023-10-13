# MistyGro

An aeroponics/fogponics planter to monitor and study crop growth and yeild. Has a Flutter based app to monitor daily stats.

- Made to be hacked
- Open source hardware and software with documentation

<img src="Images/system.jpg" alt="system" width="600"/>

## App

The app shows the current and a 24 hour history of the system. More details [here](Docs/app.md)

<p float="left">
  <img src="Images/app_main.jpg" width="200" />
  <img src="Images/app_analytics1.jpg" width="200" />
  <img src="Images/app_analytics2.jpg" width="200" />
</p>

## API documentation

C++ API documentation in arduino platform for the ESP32 controller can be found [here](https://mro47.github.io/MistyGro/annotated.html)

## Where stuff lives

**BOM:** Bill of materials for hardware.

**Circuit:** Circuit designs made using [Easy EDA](https://easyeda.com/). This should have the schematic as PDF, Easy EDA project file as json and the PCB zip.

**Docs:** Any literature or manuals related to this project.

**Images:** Any images related to this project.

**Software:** For controls and reading sensor data from hardware.
  - **app:** MistyGro App designed in Flutter.
  - **esp32_firmware:** Controller code based on arduino framework.

## System Architecture

<img src="Images/diagrams/block_diag.png" alt="system" width="600"/>

System hardware diagram

The system hardware consists of

## Sensors

### Photoresistor (LDR)

A photoresistor is used to measure ambient light which is then used to control the grow lights.

- In sunny conditions the grow lights will be switched off.
- No better source of light than the sun?

### Temperature sensor

A temperature sensor [DS18B20](https://www.adafruit.com/product/381) is used to measure the temperature of the nutrient reservoir or can also be used to measure ambient temperatures in case if that provides any insight into growth factors of any crop.

### EC and pH sensors (manual)

- The old design for this project included a [EC (Electrical conductivity) sensor]((https://wiki.keyestudio.com/KS0429_keyestudio_TDS_Meter_V1.0)) and  [pH sensor](https://wiki.seeedstudio.com/Grove-PH-Sensor-kit/) which are not part of the project anymore.
  - Long term submersion of the EC meter with exposed metal electrodes would affect its accuracy as it could corrode in a salt solution
  - Similarly for the pH sensor the glass electrode would leach ions across the barrier and be useless for measuring pH.
- These properties are now externally measured by using ph and ec meters which can be cheaply obtained from [amazon](https://amzn.eu/d/4d1FXgC) or elsewhere and don't need a complex calibration routine.
- The app has provisions to log this data to firebase (recommend at-least 1 reading everyday for both properties)

## Communication

### ESP32 WiFi

- Currently wifi is being used to log data and debug info to Firebase real time database (RTDB).

### LoRa module (unused)

- A LoRa interface is available on the PCB and can be used to log data over a long range incase the WiFi is unreachable in your den ;-).
  - Currently its unused so feel free to skip if you have a good wifi connection in you den.
  - The API needs to be designed too.

## Actuators

All devices are controlled via 5v relays.

### Ultrasonic misters

2 x [Ultrasonic misters](https://amzn.eu/d/a5XIISg) are used to atomize the nutrient solution.

### Grow lights

[Grow lights](https://amzn.eu/d/02rRoom) are wired up via relay and are switched on for a fixed time cycle from the ESP32 controller. Keeping the planter near a well lit window will switch off the lights when it gets bright (This can be set manually using the LDR voltage threshold).

The grow lamp was modified to a different configuration best suited for the planter.

## Design

Most of the system is designed from available parts in and around my house, I believe in up-cycling too. This could be improved for replicability with proper CAD designs and 3D printed mounts (not my forte, contributions welcome).

Each part design can be found in the links to documents below.

- ### Grow lamp

Grow lamp [design docs](Docs/grow_lamp_design.md)

<img src="Images/grow_lights.jpg" alt="grow lights" width="400"/>

- ### Reservoir

Reservoir [design docs](Docs/reservoir_design.md)

<img src="Images/tub.jpg" alt="tub" width="400"/>

- ### Circuit and Electronics enclosure

Circuit [design docs](Docs/circuit_design.md) and electronics enclosure [design docs](Docs/electronics_enclosure_design.md)

<img src="Images/pcb_enclosure.jpg" alt="pcb enclosure" width="400"/>

## Installation and use

Instructions in [Docs/install.md](Docs/install.md)

## Preparing nutrient solution

Instructions in [Docs/nutrient_solution.md](Docs/nutrient_solution.md)

## Contributing

Check issues page on [github](https://github.com/MRo47/MistyGro/issues) for things that need to be developed/fixed and open PRs.

## Part images

Images of parts used in this project are in [Docs/parts.md](Docs/parts.md)
