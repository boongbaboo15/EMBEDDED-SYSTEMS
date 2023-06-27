
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID           "TMPL6vwqBlOjf"
#define BLYNK_TEMPLATE_NAME         "Test"
#define BLYNK_AUTH_TOKEN            "oX3Ov2I9WArgv_lURrUoFKI11QUS3B-B"


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "It's bad day not a bad life";
char pass[] = "0641453596";

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
  Blynk.run();
}
