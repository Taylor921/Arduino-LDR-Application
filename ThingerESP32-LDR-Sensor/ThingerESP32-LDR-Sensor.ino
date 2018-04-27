#include <WiFiClientSecure.h>
#include <ThingerESP32.h>

#define USERNAME "your_user_name"
#define DEVICE_ID "your_device_id"
#define DEVICE_CREDENTIAL "your_device_credential"

#define SSID "your_wifi_ssid"
#define SSID_PASSWORD "your_wifi_ssid_password"

int lightvalue = 0;
int photoRes=A4;

ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  Serial.begin(115200);
  pinMode(photoRes,INPUT);
  thing.add_wifi(SSID, SSID_PASSWORD);
  thing["LUX"] >> [](pson& out){
    out=lightvalue;
  };
}

void loop() {
  thing.handle();
  lightvalue=analogRead(photoRes);
  Serial.println(lightvalue);
}
