#include <WiFi.h>
const char* ssid = "It's bad day not a bad life";
const char* password = "0641453596";
int pin5Test = 5;
int pin18Test = 18;
WiFiServer server(80);
void setup() {
  Serial.begin(115200);
  pinMode(pin5Test, OUTPUT); // set the LED pin mode
  pinMode(pin18Test, OUTPUT);
  delay(10);
  Serial.print("\n\nConnecting to "); Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected."); Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); server.begin();
}
int value = 0;
bool LED1_Status = LOW;
bool LED2_Status = LOW;
void loop() {
  digitalWrite(pin5Test, LED1_Status);
  digitalWrite(pin18Test, LED2_Status);
  WiFiClient client = server.available(); // listen for incoming clients
  if (client) { // if you get a client,
    Serial.println("New Client."); // print a message out the serial port
    String currentLine = ""; // make a String to hold incoming data from the client
    while (client.connected()) { // loop while the client's connected
      if (client.available()) { // if there's bytes to read from the client,
        char c = client.read(); // read a byte, then
        Serial.write(c); // print it out the serial monitor
        if (c == '\n') { // if the byte is a newline character
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println("<html>");
            client.println("<body>");
            client.println("<h1>LED Status</h1>");
            client.println("<p>");
            if (LED1_Status == HIGH)
              client.println("LED1-On");
            else
              client.println("LED1-Off");
            if (LED2_Status == HIGH)
              client.println("LED2-On");
            else
            client.println("LED2-Off");
            //client.println("<a href = \"/ledon\"><button>LED On</button></a>");
            client.println("<br />");
            client.println("<a href=\"/led1on\"><button style = \"background-color: #f44336;\">LED1 On</button></a>"); 
            client.println("<a href=\"/led2on\"><button style = \"background-color: #f44336;\">LED2 On</button></a>");
            client.println("</p>");
            //client.println("<a href = \"/ledoff\"><button>LED Off</button></a>");
            client.println("<a href=\"/led1off\"><button style = \"background-color: #008CBA;\">LED1 Off</button></a>");
            client.println("<a href=\"/led2off\"><button style = \"background-color: #008CBA;\">LED2 Off</button></a>");
            client.println("<body>");
            client.println("<br />");
            client.println("<html>");
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
        //Led1
        if (currentLine.endsWith("GET /led1on")) LED1_Status = HIGH;
        if (currentLine.endsWith("GET /led1off")) LED1_Status = LOW;
        //Led2
        if (currentLine.endsWith("GET /led2on")) LED2_Status = HIGH;
        if (currentLine.endsWith("GET /led2off")) LED2_Status = LOW;
      }
    }
    client.stop(); // close the connection:
    Serial.println("Client Disconnected.");
  }
}
