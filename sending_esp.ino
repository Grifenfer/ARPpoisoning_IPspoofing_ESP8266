#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

WiFiUDP udp;

#define LED D0 

const char* ssid = "TELECOM_AP";
const char* password = "TELECOM_AP1";
const char* ahostname = "IoTlab_MASTER";

IPAddress staticIP(192,168,0,212); //format *,*,*,*
IPAddress dest(192,168,0,213);
IPAddress gateway(192,168,0,254);
IPAddress subnet(255,255,255,0);

#define UDP_PORT 54321

void setup() {
  
  pinMode(LED, OUTPUT);
  
  Serial.begin(115200);
  delay(10);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.config(staticIP,gateway,subnet,gateway);
  WiFi.hostname(ahostname);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  Serial.print("\n");

}

void loop() {
  Serial.print("++ Sending 'ON' message ++");
  digitalWrite(LED, LOW); // turn the LED on.
  udp.beginPacket(dest, UDP_PORT);
  udp.write("ON");
  udp.endPacket(); 
  Serial.print("\n");
  delay(10000);

  Serial.print("++ Sending 'OFF' message ++");
  digitalWrite(LED, HIGH); // turn the LED off.
  udp.beginPacket(dest, UDP_PORT);
  udp.write("OFF");
  udp.endPacket(); 
  Serial.print("\n");
  Serial.print("\n");
  delay(10000);

}
