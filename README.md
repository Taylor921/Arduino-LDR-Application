# Arduino-LDR-Application
## Summary
This project utilizes the Arduino ESP32 Espressif to create a light-sensing IoT device to automatically upload sensor readings to an app. The IoT device is intended for use in outdoor and greenhouse environments. By placing the device in an area of interest, the lighting levels can be recorded and uploaded to an app to determine the viability of life for specific plants. The form of light sensor chosen for this project is a photoresistor connected to an Adafruit HUZZAH32 - ESP32 Feather microcontroller. This device is programmed using the Arduino IDE (integrated development environment), a program developed for a variety of electronic and mechanical projects. A special library developed for this IDE is utilized to upload data to the thinger.io online platform, which can be connected to the thinger.io mobile application (on Android or iOS) for a more convenient viewing experience. The interval between readings can be set with this platform as well as the span of time in which a user wants to record readings. These recordings can be viewed for future use in determining ideal planting conditions.

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
* [100mmx75mmx50mm Precision 3D Printed Box](https://github.com/Taylor921/Arduino-LDR-Application/tree/readme-edits/IoT-CaseFile)
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
[Fusion 360](https://www.autodesk.com/products/fusion-360/students-teachers-educators) was used to create the design file for the 3D-printed light sensor IoT case. For this project, 100 mm x 75 mm x 50 mm dimensions were used, but slightly smaller dimensions would be acceptable. The case consisted of two parts, a base and a lid, that conjoined by means of snap connections on either side of the case. The case also had a hole for a micro-usb connection to the IoT, along with a hole for the photoresistor to record data. The design files for the case can be found [here](https://github.com/Taylor921/Arduino-LDR-Wireless-Application/tree/Files/IoT-CaseFile).
![Imgur](https://i.imgur.com/LfwjFG7.png)

## Thinger.io
[Thinger.io](https://thinger.io/) is a very user-friendly site which allows a person to upload recorded data from a device to be output to an app. To use the site, simply [sign up](https://console.thinger.io/#/signup) for an account, navigate to the "Devices page", and add your device.
![Imgur](https://i.imgur.com/DEgTWAZ.png)

Once a device is registerd, navigate to "Data Buckets" and 'add bucket' enable bucket data storage and for data source select 'from device resource.' The bucket allows data to be populated and saved from the data sent by the IoT device with these settings.
![Imgur](https://i.imgur.com/GKvue3m.png?1)

The "dashboard" allows for several differnt widgets that can be displayed on a web browser or mobile application. Two 'time series' widgets are added one to display data as it is being collected, which pulls data from the device and the other displaying old data which pulls data from the data bucket. A 'text/value' widget is also created pulling data from the IoT which gives a live feed of the light intensity being read. Depending on the desired results, many other widgets can easily be added. 
![Imgur](https://i.imgur.com/SFd9cEr.png?1)

In order to view the dashboard on a mobile device, a QR token key must be created. In order to do this navigate to 'access token.' Add, name, and enable a token. Navigate back to 'device' add another token directly to this device and select to populate a QR code, which can then be scanned by the mobile application.
![Imgur](https://i.imgur.com/SJIKS4G.png?1)

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

## Testing
Wifi testing of sending a 'hello world' text to thinger.io in order to determine if the Adafruit Huzzah32 was properly connected to the internet and to see if data was being transmitted. 

Photoresistor testing was used to determine if the voltage divider was working and if the Ardiuno code was written correctly. The device was tested in a dim room and a bright phone light was used to see if a higher value would be detected by the photoresistor.

Testing of the combination of the bluetooth and photorestistor code was necessary to get the data to read to Thinger.io. It was determined that using pin A4 was the best pin to use for transmitting data. Pin A3 and A2 also worked for reading the photoresistor. Pin A1 ans A0 caused an issue when data was being collected and trasmitted.

## Future Testing/Features
This IoT and the software it uploads data too, Thinger.io, can be utilized to do much more. Listed below are several ways that the IoT can be improved moving forward. 
* Within the Arduino code, certain light readings can create a notification for when a certain light level is reached. This could be very useful when setting up grow lights within a greenhouse.
* Within the Arduino code, certain light readings can create a notification for what type of plant is recommended based on the amount of light is being detected.
* Other sensors can be built into the IoT such as a thermometer, humidity reader, etc. which can give significantly more data. Introduction of more sensors would be fairly cheap and would mostly require more time writing code and rebuilding the circuit. 
* The current light sensor is not set up for personal use, so by building in more automation and user input through Thinger.io personal use could be possible. 
* The device could also be programmed to store data and then transmitted over bluetooth. By using bluetooth, the device could be used in areas where there is no wifi, such as a large field. The current model requires wifi to continuously upload data to Thinger.io
* The device could be designed to be waterproof, so that there woudl be no worry of damage from rain or sprinklers.
* The device could be designed to be powered by a photovoltaic cell, so that it could run for several days.
