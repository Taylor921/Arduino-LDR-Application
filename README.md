# Arduino-LDR-Application
![Imgur](https://i.imgur.com/FVU1o2n.png)
## Description
This project utilizes the Arduino ESP32 Espressif to create a light-sensing IoT device to automatically upload sensor readings to an app. 

## Prerequisites
### Hardware
For this project, it is necessary to acquire a microcontroller which is programmable by the Arduino IDE and compatible with the [Espressif ESP32 Arduino Core](https://github.com/espressif/arduino-esp32) and wifi.

The device presented in this project is the Adafruit HUZZAH32 - ESP32 Feather.

A photoresistor is used in this example, but other sensors like a phototransistor or photodiode can be used depending on light reading requirements.

A resistor between 1000 Ohms and 10,000 Ohms is recommended for the voltage divider circuit. 

Our Parts List
* [Adafruit HUZZAH32 - ESP32 Feather](https://learn.adafruit.com/adafruit-huzzah32-esp32-feather/overview)
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

The [Arduino IDE](https://www.arduino.cc/en/Main/Software) will be needed in order to program the IoT device. Along with this, the [Thinger.io Arduino library](https://github.com/thinger-io/Arduino-Library) should be added.

Our Software
* Arduino IDE
* Thinger.io
* Autodesk Fusion360

## Autodesk Fusion360 

## thinger.io
[Thinger.io](https://thinger.io/) is a very user-friendly site which allows a person to upload recorded data from a device to be output to an app. To use the site, simply [sign up](https://console.thinger.io/#/signup) for an account, navigate to the "Devices page", and add your device.
![Imgur](https://i.imgur.com/DEgTWAZ.png)

## Programming
```
#include <WiFiClientSecure.h>
#include <ThingerESP32.h>
```
These lines are used to include the necessary libraries for this program. WiFiClientSecure contains the wifi functions which will be utilized to connect the device to Wi-Fi. ThingerESP32, previously described, allows the device to utilize the established Wi-Fi connection to upload information to the thinger.io platform.
```
#define USERNAME "your_user_name"
#define DEVICE_ID "your_device_id"
#define DEVICE_CREDENTIAL "your_device_credential"
```
To properly connect to the thinger.io platform, the above definitions are made using the Username and device parameters previously setup on the thinger.io platform. This provides a method for the device to output directly to the user's account. To set these, simply enter the Username, Device Id, and Device credentials between the quotation marks as they appear on the site.
```
#define SSID "your_wifi_ssid"
#define SSID_PASSWORD "your_wifi_ssid_password"
```
Defining the SSID and password for the Wi-Fi network is necessary to transmit data to the thinger.io platform. The SSID and password for this network can be entered between the quotation marks above.
```
int lightvalue = 0;
int photoRes=A4;
```
The light value of the sensor and the pin(A4) of the photoresistor must be listed as integers before the setup so that they are both defined. 
```
ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);
```
The above function calls the user information previously defined to properly link the ThingerESP32 library to the appropriate account.
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
Within the setup for the program is the ```Serial.begin()``` function, which begins serial data communications at the desired data rate (115200 bits per second or 115200 baud in this program). The photoresistor which was previously set as an integer is now configured as an input to be read by the microcontroller. Initialization of the Wi-Fi connection begins by using the thing.add_wifi function. Finally, light value (lightvalue) is output by the microcontroller via the Wi-Fi connection as a value with the name of "LUX".
```
void loop() {
  thing.handle();
  lightvalue=analogRead(photoRes);
  Serial.println(lightvalue);
}
```
The data set for the device is referenced by ```thing.handle()``` for the purpose of transmitting to the platform. The photoresistor is read by the ```analogRead()``` function and is finally printed via ```Serial.println()```.
