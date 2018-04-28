# Arduino-LDR-Application
## Description
This project utilizes the Arduino ESP32 Espressif to create a light-sensing IoT device to automatically upload sensor readings to an app. 

## Prerequisites
### Hardware
For this project, it is necessary to acquire a microcontroller which is programmable by the Arduino IDE and compatible with the [Espressif ESP32 Arduino Core](https://github.com/espressif/arduino-esp32) and wifi.

The microcontroller presented in this project is the Adafruit HUZZAH32 - ESP32 Feather.

A photoresistor is used in this example, but other sensors like a phototransistor or photodiode can be used depending on light reading requirements.

A resistor between 1k Ohm and 10k Ohms is recommended for the voltage divider circuit. 

Our Parts List
* [Adafruit HUZZAH32 - ESP32 Feather](https://learn.adafruit.com/adafruit-huzzah32-esp32-feather/overview)
* [Eboot Photoresistor](https://www.amazon.com/gp/product/B01N7V536K/ref=oh_aui_detailpage_o09_s00?ie=UTF8&psc=1&pldnSite=1)
* [Adafruit 3.7v 2000mAh Litium Ion Battery](https://www.amazon.com/gp/product/B0137ITW46/ref=oh_aui_detailpage_o02_s00?ie=UTF8&psc=1&pldnSite=1)
* [2"x3"x4" Precision 3D Printed Box](https://github.com/Taylor921/Arduino-LDR-Application/tree/readme-edits/IoT-CaseFile)
* [1k ± 1% Ohm Elegoo Resistor](https://www.amazon.com/gp/product/B072BL2VX1/ref=oh_aui_detailpage_o00_s00?ie=UTF8&psc=1&pldnSite=1)
* [Dupont Jumper Wires - 2 Male to Female, 4 Male to Male](https://www.amazon.com/Multicolored-Breadboard-Dupont-Jumper-wires/dp/B073X7P6N2/ref=sr_1_1_sspa?ie=UTF8&qid=1510091779&sr=8-1-spons&keywords=wire+jumpers&psc=1)
* [Breadboard - Self-Adhesive (2 power busses, 10 columns, 30 rows)](https://www.sparkfun.com/products/12002)

### Software
The Arduino IDE will be needed in order to program the IoT device. Along with this, the [thinger.io Arduino library](https://github.com/thinger-io/Arduino-Library) should be added.

Our Software
* [Arduino IDE](https://www.arduino.cc/en/Main/Software)
* [thinger.io](https://thinger.io/)
* [Autodesk Fusion 360](https://www.autodesk.com/products/fusion-360/overview)

## Autodesk Fusion360 
[Fusion 360](https://www.autodesk.com/products/fusion-360/students-teachers-educators) was used to create the design file for the 3D-printed light sensor IoT case. For this project, 100 mm x 75 mm x 50 mm dimensions were used, but slightly smaller dimensions would be acceptable. The case consisted of two parts, a base and a lid, that conjoined by means of snap connections on either side of the case. The case also had a hole for a micro-usb connection to the IoT, along with a hole for the photoresistor to record data. 
![Imgur](https://i.imgur.com/LfwjFG7.png)
The design files for the case can be found [here](https://github.com/Taylor921/Arduino-LDR-Wireless-Application/tree/Files/IoT-CaseFile).

## thinger.io
[Thinger.io](https://thinger.io/) is a very user-friendly site which allows a person to upload recorded data from a device to be output to an app. To use the site, simply [sign up](https://console.thinger.io/#/signup) for an account, navigate to the "Devices page", and add your device.
![Imgur](https://i.imgur.com/DEgTWAZ.png)

## Building the circuit
![Imgur](https://i.imgur.com/FVU1o2n.png)
A simple voltage divider circuit is utilized to measure the incoming readings from the photoresistor. The photoresistor is connected to the voltage source of the microcontroller. As the light available to the photoresistor increases, its resistance decreases allowing a higher voltage to pass through. A voltage drop is created by the 1k Ohm resistor between the analog pin and ground, which allows the voltage to be detected by the analog pin. 

When constructing the circuit, it is important to keep the following points in mind:
*The analog pin used could have an impact on whether the proper readings are sent via Wi-Fi. Pins A0 and A1 should be avoided, as these have higher-priority functions which could mask the sensor function. Pin A4 is the recommended analog pin as it typically does not have other functions to disrupt the readings.
*The microcontroller must be connected to a power source to function properly. A micro-usb connection will suffice while the device is connected to a computer for programming and testing, but using the lithium ion polymer battery previously described for everyday use is recommended.
*A 1 kOhm (recommended lower limit) resistor  was used in this project, but a resistor up to 10 kOhms is acceptable. A lower resistance will yield a greater range of light readings, but with lower sensitivity.

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
