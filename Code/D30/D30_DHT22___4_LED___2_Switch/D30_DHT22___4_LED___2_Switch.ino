#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID           "TMPL6vwqBlOjf"
#define BLYNK_TEMPLATE_NAME         "Test"
#define BLYNK_AUTH_TOKEN            "oX3Ov2I9WArgv_lURrUoFKI11QUS3B-B"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHTesp.h"
#define DHT22_Pin 15
#define sw1 18
#define sw2 19
char ssid[] = "It's bad day not a bad life";
char pass[] = "0641453596";
DHTesp dht;
//boolean btnState = false;
WidgetLED LED1(V2);
WidgetLED LED2(V3);
BlynkTimer timer;
void setup() {
Serial.begin(115200);
dht.setup(DHT22_Pin, DHTesp::DHT22); // Connect DHT sensor to GPIO 15
pinMode(sw1, INPUT_PULLDOWN);
pinMode(sw2, INPUT_PULLDOWN);
Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
timer.setInterval(1000L, myTimerEvent);
}
void myTimerEvent() {
float humidity = dht.getHumidity();
float temperature = dht.getTemperature();
Blynk.virtualWrite(V0, temperature);
Blynk.virtualWrite(V1, humidity);
if (digitalRead(sw1)) LED1.on();
else LED1.off();
if (digitalRead(sw2)) LED2.on();
else LED2.off();
Serial.print(" Temp('C) >> "); Serial.print(temperature, 1);
Serial.print(", Humidity(%) >> "); Serial.println(humidity, 1);
}
void loop()
{ Blynk.run();
timer.run(); // running timer every 250ms
}
