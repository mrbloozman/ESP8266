#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid     = "SSID";
const char* password = "PASS";
IPAddress ip(192,168,1,120);
IPAddress gateway(192,168,1,254);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

String webString="<html><body><form action='/on'><button type='submit'>ON</button></form><form action='/off'><button type='submit'>OFF</button></form></body></html>";
 
//void handle_root() {
//  server.send(200, "text/plain", "Hello from the esp8266");
//  delay(100);
//}
 
void setup(void)
{
  // You can open the Arduino IDE Serial Monitor window to see what the code is doing
  // Serial.begin(115200);  // Serial connection from ESP-01 via 3.3v console cable
  
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  WiFi.config(ip,gateway,subnet);
  // Serial.print("\n\r \n\rWorking to connect");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    // Serial.print(".");
  }
  
    // pin
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
   
  server.on("/", [](){
    server.send(200, "text/html", webString);
  });
  
  server.on("/on", [](){  // if you add this subdirectory to your webserver call, you get text below :)
    digitalWrite(2, LOW);
    server.send(200, "text/html", webString);            // send to someones browser when asked
  });

  server.on("/off", [](){  // if you add this subdirectory to your webserver call, you get text below :)
    digitalWrite(2, HIGH);
    server.send(200, "text/html", webString);               // send to someones browser when asked
  });
  
  server.begin();
  // Serial.println("HTTP server started");
}
 
void loop(void)
{
  server.handleClient();
} 


