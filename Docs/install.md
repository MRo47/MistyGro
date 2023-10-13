# Installation

## Setting up the esp32 controller

### Setting up secrets

* Syncing timer with NTC will require WiFi credentials which can be set up following the instructions below.
* Firebase logging will also require firebase credentials. Which can be set up using [this](https://randomnerdtutorials.com/esp32-data-logging-firebase-realtime-database/) article from Random Nerd tutorials.
* Add a `secrets.h` file in `Software/esp32_firmware/include` and fill in the details.

```cpp
#ifndef _SECRETS_H_
#define _SECRETS_H_

#define WIFI_SSID ""
#define WIFI_PASSWORD ""
#define FIREBASE_TOKEN ""
#define FIREBASE_USER_EMAIL ""
#define FIREBASE_USER_PASSWORD ""
#define FIREBASE_URL ""

#endif
```

### Install

* **Build the project in Platform.io:**
Currently the `main.cpp`` file is selected in platformio.ini (commented out in the build_src_filter)
* **Upload to ESP32:**
Upload by clicking the upload button while press and holding the boot button on ESP32.

#### Test modules individually

Uncomment the `-<main.cpp>` line and comment out the test cpps for each module, one at a time. Then do the steps in install

## Phone

* Follow [this](https://firebase.google.com/docs/flutter/setup?platform=android) to register the android app. Switch to IOS if you have to set this up on IOS device.

>****NOTE**** This project has been only tested with an android app and I'm (MRo47) a noob at flutter or in general app development. So contributions are welcome here.

