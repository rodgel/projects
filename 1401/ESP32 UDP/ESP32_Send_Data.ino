//sending 30,000 byte data to esp32 with python socket
#include <WebServer.h>
#include <WiFi.h>
#include <WiFiUdp.h>

// the IP of the machine to which you send msgs - this should be the correct IP in most cases (see note in python code)
#define CONSOLE_IP "192.168.1.2"
#define CONSOLE_PORT 4210

const char* ssid = "ESP32";
const char* password = "";

WiFiUDP Udp;
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
WebServer server(80);

//Definition of packages for ESP32
byte replyPacket[30000];

void setup()
{
  //connecting to internet setup
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  server.begin();
}

void loop()
{
  //dividing packeges 
    memset(replyPacket, 1, 3000);
    memset(replyPacket+3000, 2, 3000);
    memset(replyPacket+6000, 3, 3000);
    memset(replyPacket+9000, 4, 3000);
    memset(replyPacket+12000, 5, 3000);
    memset(replyPacket+15000, 6, 3000);
    memset(replyPacket+18000, 7, 3000);
    memset(replyPacket+21000, 8, 3000);
    memset(replyPacket+24000, 9, 3000);
    memset(replyPacket+27000, 0, 3000);

//sending packeges with 20ms delay
  Udp.beginPacket(CONSOLE_IP, CONSOLE_PORT);
  //sending packeges
  Udp.write(&replyPacket[0],3000);
  Udp.endPacket();
  delay(20);

  Udp.beginPacket(CONSOLE_IP, CONSOLE_PORT);
  Udp.write(&replyPacket[3000],3000);
  Udp.endPacket();
  delay(20);

  Udp.beginPacket(CONSOLE_IP, CONSOLE_PORT);
  Udp.write(&replyPacket[6000],3000);
  Udp.endPacket();
  delay(20);

  Udp.beginPacket(CONSOLE_IP, CONSOLE_PORT);
  Udp.write(&replyPacket[9000],3000);
  Udp.endPacket();
  delay(20);

  Udp.beginPacket(CONSOLE_IP, CONSOLE_PORT);
  Udp.write(&replyPacket[12000],3000);
  Udp.endPacket();
  delay(20);

  Udp.beginPacket(CONSOLE_IP, CONSOLE_PORT);
  Udp.write(&replyPacket[15000],3000);
  Udp.endPacket();
  delay(20);

  Udp.beginPacket(CONSOLE_IP, CONSOLE_PORT);
  Udp.write(&replyPacket[18000],3000);
  Udp.endPacket();
  delay(20);

  Udp.beginPacket(CONSOLE_IP, CONSOLE_PORT);
  Udp.write(&replyPacket[21000],3000);
  Udp.endPacket();
  delay(20);

  Udp.beginPacket(CONSOLE_IP, CONSOLE_PORT);
  Udp.write(&replyPacket[24000],3000);
  Udp.endPacket();
  delay(20);

  Udp.beginPacket(CONSOLE_IP, CONSOLE_PORT);
  Udp.write(&replyPacket[27000],3000);
  Udp.endPacket();
  delay(20);
}
