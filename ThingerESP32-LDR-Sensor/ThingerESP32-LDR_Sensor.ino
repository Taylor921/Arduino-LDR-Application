#include <WiFiClientSecure.h>
#include <ThingerESP32.h>

#define USERNAME "NickBaumann"
#define DEVICE_ID "esp32"
#define DEVICE_CREDENTIAL "esp321"

#define SSID "ukyedu"
#define SSID_PASSWORD ""

int lightvalue = 0;
int photoRes=A2;

ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  Serial.begin(115200);
  pinMode(photoRes,INPUT);
  thing.add_wifi("ukyedu", "");
  thing["LUX"] >> [](pson& out){
    out=lightvalue;
  };
}

void loop() {
  thing.handle();
  lightvalue=analogRead(photoRes);
  Serial.println(lightvalue);
}
