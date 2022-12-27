//sending 30,000 byte data to esp32 with python socket
#include <WebServer.h>
#include <WiFi.h>
#include <WiFiUdp.h>
// #include <ESP32DMASPISlave.h>

// ESP32DMASPI::Slave slave;

// static const uint32_t BUFFER_SIZE = 24;
// uint8_t* spi_slave_tx_buf;
// uint8_t* spi_slave_rx_buf;

#include <ESP32SPISlave.h>

ESP32SPISlave slave;

static constexpr uint32_t BUFFER_SIZE {3000};
uint8_t spi_slave_tx_buf[BUFFER_SIZE];
uint8_t spi_slave_rx_buf[BUFFER_SIZE];


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
byte replyPacket[30000];

void setup()
{
  //connecting to internet setup
  Serial.begin(115200);
//  WiFi.softAP(ssid, password);
//  WiFi.softAPConfig(local_ip, gateway, subnet);
//  server.begin();

    // to use DMA buffer, use these methods to allocate buffer
    // spi_slave_tx_buf = slave.allocDMABuffer(BUFFER_SIZE);
    // spi_slave_rx_buf = slave.allocDMABuffer(BUFFER_SIZE);

    // set buffer data...
    // set_buffer();
    // slave device configuration
    slave.setDataMode(SPI_MODE0);
    // slave.setMaxTransferSize(BUFFER_SIZE);

    // begin() after setting
    slave.begin(VSPI);  // HSPI = CS: 15, CLK: 14, MOSI: 13, MISO: 12 -> default
                    // VSPI (CS:  5, CLK: 18, MOSI: 23, MISO: 19)

    
    pinMode(LED, OUTPUT);


}

void loop()
{



  while(0){

    // if there is no transaction in queue, add transaction
    if (slave.remained() == 0) {
        slave.queue(spi_slave_rx_buf, spi_slave_tx_buf, BUFFER_SIZE);

        Serial.println("aaaa");
        Serial.println(slave.remained());
    }

    // if transaction has completed from master,
    // available() returns size of results of transaction,
    // and buffer is automatically updated

    while (slave.available()) {
        // do something with received data: spi_slave_rx_buf


      printf("1th is : %d ", spi_slave_rx_buf[0]);
      delay(10);
      printf("2th is : %d ", spi_slave_rx_buf[1]);
      delay(10);


      // Serial.println(spi_slave_rx_buf[0]);
      // Serial.println(spi_slave_rx_buf[1]);
      // Serial.println(spi_slave_rx_buf[2]);
      // Serial.println(spi_slave_rx_buf[3]);
      // Serial.println(spi_slave_rx_buf[4]);
     

      slave.pop();
    }


  }




  while(1){






    // if there is no transaction in queue, add transaction
    if (slave.remained() == 0)
        slave.queue(spi_slave_rx_buf, spi_slave_tx_buf, BUFFER_SIZE);

    // if transaction has completed from master,
    // available() returns size of results of transaction,
    // and `spi_slave_rx_buf` is automatically updated
    while (slave.available()) {
        // do something with `spi_slave_rx_buf`
        // show received data
         Serial.print("Command Received: ");
         
        for(int i=0;i<BUFFER_SIZE;i++){Serial.println(spi_slave_rx_buf[i]);delay(1);}
        slave.pop();
        
    }
  }





   // block until the transaction comes from master
    slave.wait(spi_slave_rx_buf, spi_slave_tx_buf, BUFFER_SIZE);

    // if transaction has completed from master,
    // available() returns size of results of transaction,
    // and buffer is automatically updated
    char data;
    while (slave.available()) {
        // show received data
         Serial.print("Command Received: ");
         
         for(int i=0;i<BUFFER_SIZE;i++){Serial.println(spi_slave_rx_buf[i]);delay(1);}
         data = spi_slave_rx_buf[0];
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
     Serial.println("");

  


  Serial.write("h");
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
