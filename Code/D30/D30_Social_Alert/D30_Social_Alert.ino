#include <WiFi.h>
#include <HTTPClient.h>
#define WIFI_SSID "It's bad day not a bad life"
#define WIFI_PASS "0641453596"
#define WebHooksKey "jSJmaCRRDH7ibUiNBL7rTf2ZQiPdCSaq7Xkckg0C9KJ"
#define WebHooksEventName "Social Alert"
#define testSwitchB 22
#define testSwitchC 23
void setup() {
Serial.begin(115200);
WiFi.begin(WIFI_SSID, WIFI_PASS);
Serial.println("Connecting");
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.print("Connected to WiFi network with IP Address: ");
Serial.println(WiFi.localIP());
pinMode(testSwitchB, INPUT_PULLUP);
pinMode(testSwitchC, INPUT_PULLUP);
randomSeed(analogRead(33));
}
void loop() {
if (digitalRead(testSwitchB) == LOW) {
String serverName = "http://maker.ifttt.com/trigger/" + String(WebHooksEventName) + "/with/key/" + String(WebHooksKey);
String httpRequestData = "value1=" + String("Door Open Alarm");
Serial.println("Server Name :" + serverName);
Serial.println("json httpRequestData :" + httpRequestData);
if (WiFi.status() == WL_CONNECTED) {
HTTPClient http;
http.begin(serverName);
http.addHeader("Content-Type", "application/x-www-form-urlencoded");
int httpResponseCode = http.POST(httpRequestData);
Serial.print("HTTP Response code: ");
Serial.println(httpResponseCode);
http.end();
if (httpResponseCode == 200)
Serial.println("Successfully sent");
else
Serial.println("Failed!");
}
else {
Serial.println("WiFi Disconnected");
}
}
if (digitalRead(testSwitchC) == LOW) {
String serverName = "http://maker.ifttt.com/trigger/" + String(WebHooksEventName) + "/with/key/" + String(WebHooksKey);
String httpRequestData = "value1=" + String("Intruders Alarm");
Serial.println("Server Name :" + serverName);
Serial.println("json httpRequestData :" + httpRequestData);
if (WiFi.status() == WL_CONNECTED) {
HTTPClient http;
http.begin(serverName);
http.addHeader("Content-Type", "application/x-www-form-urlencoded");
int httpResponseCode = http.POST(httpRequestData);
Serial.print("HTTP Response code: ");
Serial.println(httpResponseCode);
http.end();
if (httpResponseCode == 200)
Serial.println("Successfully sent");
else
Serial.println("Failed!");
}
else {
Serial.println("WiFi Disconnected");
}
} }
