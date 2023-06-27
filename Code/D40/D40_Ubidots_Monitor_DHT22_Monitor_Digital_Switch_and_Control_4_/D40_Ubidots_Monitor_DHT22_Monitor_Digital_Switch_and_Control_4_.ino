#include <WiFi.h>
#include <PubSubClient.h>
#include "DHTesp.h"
const char *My_SSID = "It's bad day not a bad life";
const char *My_Pass = "0641453596";
const char *MQTT_Server = "industrial.api.ubidots.com";
const char *MQTT_User = "BBFF-RgUJDWTeZdrMKJmwvoxp5W6ePSMYif";
const char *MQTT_Pass = "BBFF-RgUJDWTeZdrMKJmwvoxp5W6ePSMYif";
const char *PTopic1 = "/v2.0/devices/test/BBFF-GaUujMiW5i0BBGT6g7gBLHEmkO7i3W/lv";
const char *STopic1 = "/v2.0/devices/test/humid";
const char *STopic2 = "/v2.0/devices/test/tempp";
const char *STopic3 = "/v2.0/devices/test/led1";
const char *STopic4 = "/v2.0/devices/test/led2";
const char *STopic5 = "/v2.0/devices/test/led3";
const char *STopic6 = "/v2.0/devices/test/led4";
const char *STopic7 = "/v2.0/devices/test/sw1";
const char *STopic8 = "/v2.0/devices/test/sw2";
#define MQTT_Port 1883
#define Test_LED1 19
#define Test_LED2 21
#define Test_LED3 22
#define Test_LED4 23
#define Test_SW1 2
#define Test_SW2 4
#define Pin_DHT22 15
DHTesp dht;
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
void Setup_Wifi() {
delay(10);
Serial.println();
Serial.print("Connecting to ");
Serial.println(My_SSID);
WiFi.begin(My_SSID, My_Pass);
while (WiFi.status() != WL_CONNECTED) {
delay(500); Serial.print(".");
}
randomSeed(micros());
Serial.println("");
Serial.println("WiFi connected");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
}
void reconnect()
{ while (!client.connected()) // Loop until we're reconnected
{ Serial.print("Attempting MQTT connection...");
String clientId = "ESP32 Client-";
clientId += String(random(0xffff), HEX); // Create a random client ID
if (client.connect(clientId.c_str(), MQTT_User, MQTT_Pass)) // Attempt to connect
{ Serial.println("connected"); // Once connected, publish an announcement...
client.subscribe(STopic1);
client.subscribe(STopic2);
client.subscribe(STopic3);
client.subscribe(STopic4);
client.subscribe(STopic5);
client.subscribe(STopic6);
client.subscribe(STopic7);
client.subscribe(STopic8);
} else
{ Serial.print("failed, rc=");
Serial.print(client.state());
Serial.println(" try again in 5 seconds");
delay(5000);
}
}
}
void callback(char *topic, byte *payload, unsigned int length)
{ Serial.print("Message arrived [");
Serial.print(topic);
Serial.print("] ");
for (int i = 0; i < length; i++)
{ Serial.print((char)payload[i]);
}
if (topic[24] == STopic3[24]) {
Serial.print(" -LED1->> ");
Serial.print((char)payload[10]);
if (payload[10] == '1')
digitalWrite(Test_LED1, HIGH);
else
digitalWrite(Test_LED1, LOW);
}
if (topic[24] == STopic4[24]) {
Serial.print(" -LED2->> ");
Serial.print((char)payload[10]);
if (payload[10] == '1')
digitalWrite(Test_LED2, HIGH);
else
digitalWrite(Test_LED2, LOW);
}
if (topic[24] == STopic5[24]) {
Serial.print(" -LED3->> ");
Serial.print((char)payload[10]);
if (payload[10] == '1')
digitalWrite(Test_LED3, HIGH);
else
digitalWrite(Test_LED3, LOW);
}
if (topic[24] == STopic6[24]) {
Serial.print(" -LED4->> ");
Serial.print((char)payload[10]);
if (payload[10] == '1')
digitalWrite(Test_LED4, HIGH);
else
digitalWrite(Test_LED4, LOW);
}
Serial.println();
}
void setup()
{ pinMode(Test_LED1, OUTPUT);
pinMode(Test_LED2, OUTPUT);
pinMode(Test_LED3, OUTPUT);
pinMode(Test_LED4, OUTPUT);
pinMode(Test_SW1, INPUT_PULLDOWN);
pinMode(Test_SW2, INPUT_PULLDOWN);
dht.setup(Pin_DHT22, DHTesp::DHT22);
Serial.begin(115200);
Setup_Wifi();
client.setServer(MQTT_Server, MQTT_Port);
client.setCallback(callback);
}
void loop()
{ if (!client.connected()) reconnect();
client.loop();
long now = millis();
if (now - lastMsg > 5000)
{ lastMsg = now;
float humidity = dht.getHumidity();
float temperature = dht.getTemperature();
int sw1 = 0;
int sw2 = 0;
if (digitalRead(Test_SW1)== HIGH) sw1 = 1;
else sw1 = 0;
if (digitalRead(Test_SW2)== LOW) sw2 = 1;
else sw2 = 0;
snprintf (msg, 75, "{ \"humid\" : %.2f, \"tempp\": %.2f, \"sw1\": %d, \"sw2\": %d }",
humidity, temperature, sw1, sw2);
Serial.print("Publish message: ");
Serial.println(msg);
client.publish(PTopic1, msg);
} }
