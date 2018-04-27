# Arduino-LDR-Application
![Imgur](https://i.imgur.com/FVU1o2n.png)
## Description
This project utilizes the Arduino ESP32 Espressif to create a light-sensing IoT device to automatically upload sensor readings to an app. 

## Prerequisites
### Hardware
For this project, it is necessary to acquire a microcontroller which is programmable by the Arduino IDE and compatible with the [Espressif ESP32 Arduino Core](https://github.com/espressif/arduino-esp32) and wifi.

The device presented in this project is the [Adafruit HUZZAH32 - ESP32 Feather](https://learn.adafruit.com/adafruit-huzzah32-esp32-feather/overview).

A photoresistor is used in this example, but other sensors like a phototransistor or photodiode can be used depending on light reading requirements.

A resistor between 1000 Ohms and 10,000 Ohms is recommended for the voltage divider circuit. 

Our Parts List
* Adafruit HUZZAH32 - ESP32 Feather
* Eboot Photoresistor
* Adafruit 3.7v 2000mAh Litium Ion Battery
* 2"x3"x4" Precision 3D Printed Box
* 1000 ± 1% Ohm Elegoo Resistor
* Dupont Jumper Wires - 2 Male to Female, 4 Male to Male
* Breadboard - Self-Adhesive (2 power busses, 10 columns, 30 rows)



### Software
Arduino IDE

Thinger.io

Autodesk Fusion 360

The [Arduino IDE](https://www.arduino.cc/en/Main/Software) will be needed in order to program the IoT device. Along with this, the [Thinger.io](https://github.com/thinger-io/Arduino-Library) arduino library should be added.

Our Software
* Arduino IDE
* Thinger.io
* Autodesk Fusion360

## Programming
```
#include <WiFiClientSecure.h>
#include <ThingerESP32.h>
```

```
#define USERNAME "your_user_name"
#define DEVICE_ID "your_device_id"
#define DEVICE_CREDENTIAL "your_device_credential"
```

```
#define SSID "your_wifi_ssid"
#define SSID_PASSWORD "your_wifi_ssid_password"
```

```
int lightvalue = 0;
int photoRes=A4;
```

```
ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);
```

```
void setup() {
  Serial.begin(115200);
  pinMode(photoRes,INPUT);
  thing.add_wifi(SSID, SSID_PASSWORD);
  thing["LUX"] >> [](pson& out){
    out=lightvalue;
  };
}
```

```

void loop() {
  thing.handle();
  lightvalue=analogRead(photoRes);
  Serial.println(lightvalue);
}
```
