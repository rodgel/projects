//sending 30,000 byte data to esp32 with python socket
#include <WebServer.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#include <ESP32DMASPISlave.h>

ESP32DMASPI::Slave slave;

static const uint32_t BUFFER_SIZE = 10000;
uint8_t* spi_slave_tx_buf;
uint8_t* spi_slave_rx_buf;



// the IP of the machine to which you send msgs - this should be the correct IP in most cases (see note in python code)
#define CONSOLE_IP "192.168.1.2"
#define CONSOLE_PORT 4210
#define LED 2


const char* ssid = "ESP32";
const char* password = "";

WiFiUDP Udp;
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
WebServer server(80);

//Definition of packages for ESP32
//byte replyPacket[50000];


void setup() {

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  server.begin();

    Serial.begin(115200);

    // to use DMA buffer, use these methods to allocate buffer
    spi_slave_tx_buf = slave.allocDMABuffer(BUFFER_SIZE);
    spi_slave_rx_buf = slave.allocDMABuffer(BUFFER_SIZE);

    // set buffer data...

    // slave device configuration
    slave.setDataMode(SPI_MODE0);
    slave.setMaxTransferSize(BUFFER_SIZE);

    // begin() after setting
    slave.begin(VSPI);  // HSPI = CS: 15, CLK: 14, MOSI: 13, MISO: 12 -> default
                    // VSPI (CS:  5, CLK: 18, MOSI: 23, MISO: 19)
    
      pinMode(LED, OUTPUT);
}

int data=100;
void loop(){


    // if there is no transaction in queue, add transaction
    if (slave.remained() == 0) {
        slave.queue(spi_slave_rx_buf, spi_slave_tx_buf, BUFFER_SIZE);
    }

    // if transaction has completed from master,
    // available() returns size of results of transaction,
    // and buffer is automatically updated

    while (slave.available()) {
      
        // do something with received data: spi_slave_rx_buf
        Serial.print("Command Received: ");
        // for(int i=0;i<BUFFER_SIZE;i++){Serial.println(spi_slave_rx_buf[i]);delay(1);}
            //sending packeges with 20ms delay
        Udp.beginPacket(CONSOLE_IP, CONSOLE_PORT);
        //sending packeges
        Udp.write(&spi_slave_rx_buf[0],10000);
        Udp.endPacket();

        slave.pop();
  }

    if(data == 1 )
    {
        Serial.println("Setting LED active HIGH ");
        digitalWrite(LED, HIGH);
    }
    else if(data == 0 )
    {
        Serial.println("Setting LED active LOW ");
        digitalWrite(LED, LOW);
    }
    //  Serial.println("");

  
  //dividing packeges 
    // memset(replyPacket, 1, 3000);
    // memset(replyPacket+3000, 1, 3000);
    // memset(replyPacket+6000, 1, 3000);
    // memset(replyPacket+9000, 1, 3000);
    // memset(replyPacket+12000, 1, 3000);
    // memset(replyPacket+15000, 1, 3000);
    // memset(replyPacket+18000, 1, 3000);
    // memset(replyPacket+21000, 1, 3000);
    // memset(replyPacket+24000, 1, 3000);
    // memset(replyPacket+27000, 1, 3000);


   // delay(5000);

  // Udp.beginPacket(CONSOLE_IP, CONSOLE_PORT);
  // Udp.write(&replyPacket[3000],3000);
  // Udp.endPacket();
  // delay(20);

  // Udp.beginPacket(CONSOLE_IP, CONSOLE_PORT);
  // Udp.write(&replyPacket[6000],3000);
  // Udp.endPacket();
  // delay(20);

  // Udp.beginPacket(CONSOLE_IP, CONSOLE_PORT);
  // Udp.write(&replyPacket[9000],3000);
  // Udp.endPacket();
  // delay(20);

  // Udp.beginPacket(CONSOLE_IP, CONSOLE_PORT);
  // Udp.write(&replyPacket[12000],3000);
  // Udp.endPacket();
  // delay(20);

  // Udp.beginPacket(CONSOLE_IP, CONSOLE_PORT);
  // Udp.write(&replyPacket[15000],3000);
  // Udp.endPacket();
  // delay(20);

  // Udp.beginPacket(CONSOLE_IP, CONSOLE_PORT);
  // Udp.write(&replyPacket[18000],3000);
  // Udp.endPacket();
  // delay(20);

  // Udp.beginPacket(CONSOLE_IP, CONSOLE_PORT);
  // Udp.write(&replyPacket[21000],3000);
  // Udp.endPacket();
  // delay(20);

  // Udp.beginPacket(CONSOLE_IP, CONSOLE_PORT);
  // Udp.write(&replyPacket[24000],3000);
  // Udp.endPacket();
  // delay(20);

  // Udp.beginPacket(CONSOLE_IP, CONSOLE_PORT);
  // Udp.write(&replyPacket[27000],3000);
  // Udp.endPacket();
  // delay(20);
}
