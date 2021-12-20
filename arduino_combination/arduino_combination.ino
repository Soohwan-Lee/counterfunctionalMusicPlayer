#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <SPI.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
//#include <WiFiNINA.h>
//#include <WiFiUdp.h>
//
//int status = WL_IDLE_STATUS;
//#include "arduino_secrets.h"
/////////please enter your sensitive data in the Secret tab/arduino_secrets.h
//char ssid[] = SECRET_SSID;        // your network SSID (name)
//char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
//int keyIndex = 0;            // your network key Index number (needed only for WEP)
//
//unsigned int localPort = 12000;      // local port to listen on
//
//char packetBuffer[256]; //buffer to hold incoming packet
//
//WiFiUDP Udp;

#define PIN 5

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();


//네오픽셀을 사용하기 위해 객체 하나를 생성한다.
//첫번째 인자값은 네오픽셀의 LED의 개수
//두번째 인자값은 네오픽셀이 연결된 아두이노의 핀번호
//세번째 인자값은 네오픽셀의 타입에 따라 바뀌는 flag
Adafruit_NeoPixel strip = Adafruit_NeoPixel(22, PIN, NEO_GRB + NEO_KHZ800);

////define color code
uint32_t mainColor = strip.Color(70, 0, 255);
uint32_t red = strip.Color(255, 0, 0);

//// 0~11 (1~12), 12: play, 13: pause, 14: heart
uint8_t shape[15][8] =
{{
    B00011000,
    B00111000,
    B00111000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B01111110
  }, {
    B00111100,
    B01111110,
    B01000110,
    B00001100,
    B00110000,
    B01100000,
    B01111110,
    B01111110
  }, {
    B00111100,
    B01100110,
    B00000110,
    B00011100,
    B00011110,
    B00000110,
    B01100110,
    B00111100
  }, {
    B00001100,
    B00011100,
    B00101100,
    B01001100,
    B01111110,
    B01111110,
    B00001100,
    B00001100
  }, {
    B01111110,
    B01100000,
    B01100000,
    B01111100,
    B00000110,
    B00000110,
    B01100110,
    B00111100
  }, {
    B00111100,
    B01100010,
    B01100000,
    B01111100,
    B01100110,
    B01100110,
    B01100110,
    B00111100
  }, {
    B01111110,
    B01100110,
    B00000110,
    B00001100,
    B00011000,
    B00011000,
    B00011000,
    B00011000
  }, {
    B00111100,
    B01100110,
    B01100110,
    B00111100,
    B01100110,
    B01100110,
    B01100110,
    B00111100
  }, {
    B00111100,
    B01100110,
    B01100110,
    B01100110,
    B00111110,
    B00000110,
    B01100110,
    B00111100
  }, {
    B01000110,
    B11001001,
    B01001001,
    B01001001,
    B01001001,
    B01001001,
    B01001001,
    B11100110
  }, {
    B01000010,
    B11000110,
    B01000010,
    B01000010,
    B01000010,
    B01000010,
    B01000010,
    B11100111
  }, {
    B01000110,
    B11001001,
    B01000001,
    B01000110,
    B01001000,
    B01001000,
    B01001000,
    B11101111
  }, {
    B00000000,
    B01100000,
    B01111000,
    B01111110,
    B01111110,
    B01111000,
    B01100000,
    B00000000
  }, {
    B00000000,
    B01100110,
    B01100110,
    B01100110,
    B01100110,
    B01100110,
    B01100110,
    B00000000
  }, {
    B00000000,
    B01100110,
    B11111111,
    B11111111,
    B11111111,
    B01111110,
    B00111100,
    B00011000
  }
};

boolean pausing = true;
boolean play = false;
boolean power = false;
boolean movement = false;
//int month = 0;
int temp = 1;
int cycle = 2;
int numfiles = cycle * 12;
int month = 0;


void setup() {
  strip.begin(); //네오픽셀을 초기화하기 위해 모든LED를 off시킨다
  strip.show();
  matrix.begin(0x70);  // pass in the address (dot matrix)
  //play();
  Serial.begin(9600);
  mp3_set_serial (Serial);      // DFPlayer-mini mp3 module 시리얼 세팅
  delay(1);                     // 볼륨값 적용을 위한 delay
  mp3_set_volume (15);          // 볼륨조절 값 0~30

  //  while (!Serial) {
  //    ; // wait for serial port to connect. Needed for native USB port only
  //  }

  //  // check for the WiFi module:
  //  if (WiFi.status() == WL_NO_MODULE) {
  //    Serial.println("Communication with WiFi module failed!");
  //    // don't continue
  //    while (true);
  //  }
  //
  //  String fv = WiFi.firmwareVersion();
  //  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
  //    Serial.println("Please upgrade the firmware");
  //  }
  //
  //  while (status != WL_CONNECTED) {
  //    Serial.print("Attempting to connect to SSID: ");
  //    Serial.println(ssid);
  //    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  //    status = WiFi.begin(ssid, pass);
  //
  //    // wait 10 seconds for connection:
  //    delay(10000);
  //  }
  //  Serial.println("Connected to wifi");
  //  printWifiStatus();
  //
  //  Serial.println("\nStarting connection to server...");
  //  // if you get a connection, report back via serial:
  //  Udp.begin(localPort);
}

void loop() {
  //  //UDP Receiver
  //  // if there's data available, read a packet
  //  int packetSize = Udp.parsePacket();
  //  if (packetSize) {
  //    Serial.print("Received packet of size ");
  //    Serial.println(packetSize);
  //    Serial.print("From ");
  //    IPAddress remoteIp = Udp.remoteIP();
  //    Serial.print(remoteIp);
  //    Serial.print(", port ");
  //    Serial.println(Udp.remotePort());
  //
  //    // read the packet into packetBufffer
  //    int len = Udp.read(packetBuffer, 255);
  //    if (len > 0) {
  //      packetBuffer[len] = 0;
  //    }
  //    Serial.println("Contents:");
  //    Serial.println(packetBuffer);
  //
  //    // send a reply, to the IP address and port that sent us the packet we received
  //    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
  //    //Udp.write(ReplyBuffer);
  //    Udp.endPacket();
  //  }




  //  int month = 0;
  if (Serial.available()) {
    month = Serial.read();
    if (month == 13) {
      if (power == true) {
        power = false;
        mp3_pause();
        //movement= false;
        deviceOFF();
      } else if (power == false) {
        power = true;
        deviceON();
        steady();
      }
    }
  }

  if (power == true) {
    if (pausing == true) {
      //      if (Serial.available()) {
      //        month = Serial.read();    //14 is 'PAUSE' (There is no 14월)
      if (month < 13) {
        temp = month;
        pausing = false;
        play = true;
      }
      //      }
    } else if (pausing == false) {
      if (play == true) {
        //playing();
        showMonth();
        mp3_play(temp);
        //temp += 12;
        play = false;
        movement = true;
      }


      //      if (Serial.available()) {
      //        month = Serial.read();
      if (month > 13) {
        //mp3_pause();
        tempStop();
        mp3_stop();
        pausing = true;
        movement = false;
      }

      
      if (movement == true) {
        playing();
      }
      
      //      }
    }
  }
}


/////UDP WIFI Status Information
//void printWifiStatus() {
//  // print the SSID of the network you're attached to:
//  Serial.print("SSID: ");
//  Serial.println(WiFi.SSID());
//
//  // print your board's IP address:
//  IPAddress ip = WiFi.localIP();
//  Serial.print("IP Address: ");
//  Serial.println(ip);
//
//  // print the received signal strength:
//  long rssi = WiFi.RSSI();
//  Serial.print("signal strength (RSSI):");
//  Serial.print(rssi);
//  Serial.println(" dBm");
//}
