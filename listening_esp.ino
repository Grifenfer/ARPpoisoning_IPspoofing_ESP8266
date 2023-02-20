#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define LED D0            // Led in NodeMCU at pin GPIO16 (D0).

const char* ssid = "TELECOM_AP";
const char* password = "TELECOM_AP1";
const char* ahostname = "IoTlab_slave";

IPAddress staticIP(192,168,0,213); //format *,*,*,*
IPAddress dest(192,168,0,212);
IPAddress gateway(192,168,0,254);
IPAddress subnet(255,255,255,0);

// UDP
WiFiUDP udp;
char packet[255];
char reply[] = "Packet received!";


#define UDP_PORT 54321

void setup() {
  pinMode(LED, OUTPUT);    // LED pin as output.
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

  // Begin listening to UDP port
  udp.begin(UDP_PORT);
  Serial.print("Listening on UDP port ");
  Serial.println(UDP_PORT);
}

void loop() {



  // If packet received...
  int packetSize = udp.parsePacket();
  if (packetSize) {
    Serial.print("Received packet! Size: ");
    Serial.println(packetSize);
    Serial.print("\n"); 
    int len = udp.read(packet, 255);
    if (len > 0)
    {
      Serial.print("MAC Address: ");
      Serial.print(WiFi.macAddress());
      Serial.print("--- IP Address: ");
      Serial.println(WiFi.localIP());
      Serial.print("\n");
      packet[len] = '\0';
      Serial.print("Packet received: ");
      Serial.println(packet);
      Serial.print(" from ");
      Serial.print(udp.remoteIP());
      Serial.print("\n");

      if (udp.remoteIP() == dest){
        if (packet[0] == 'O' && packet[1] == 'N'){
          delay(1000);
          digitalWrite(LED, LOW); // turn the LED on.
          Serial.print("LED LOW");
        } else if (packet[0] == 'O' && packet[1] == 'F' && packet[2] == 'F'){
          delay(1000);
          digitalWrite(LED, HIGH); // turn the LED off.
          Serial.print("LED HIGH");
        }
      }
      
      Serial.print("\n");
    }
  }
}
