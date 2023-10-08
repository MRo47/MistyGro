# LDR Calibration

The potentiometer on the PCB needs to be adjusted based on the LDR resistance. The aim is to get the LDR to have maximum swing in voltage or to center its potential.

## Steps

1. Connect the LDR and read analog voltage from the ESP32.
2. Adjust the potentiometer such that
    1. This analog voltage must not go under zero for maximum darkness (just block the ldr with you finger or a piece of tape).
    2. The value should not go above maximum analog voltage (saturation) when maximum light is incident on the LDR (maybe direct sun shining on the LDR).
3. Now set a certain brightness based on ambient light conditions under which voltage value the lights should come on and set this value as threshold voltage (ldr_thresh_v) in [Software/ESP32/include/utility.h](../Software/ESP32/include/utility.h)
