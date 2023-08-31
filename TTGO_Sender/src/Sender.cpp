#include<Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>

#include "C:\Users\Hi\OneDrive - The University of Technology\Arduino\TTGO_Sender\src\SSD1306\images.h"
#include "C:\Users\Hi\OneDrive - The University of Technology\Arduino\TTGO_Sender\src\SSD1306\SSD1306.h"

#define SCK     5    // GPIO5  -- SX1278's SCK
#define MISO    19   // GPIO19 -- SX1278's MISnO
#define MOSI    27   // GPIO27 -- SX1278's MOSI
#define SS      18   // GPIO18 -- SX1278's CS
#define RST     23   // GPIO14 -- SX1278's RESET
#define DI0     26   // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define BAND  868E6

unsigned int counter = 0;

SSD1306 display(0x3c, 21, 22);
String rssi = "--";
String packSize = "--";
String packet ;

int delay_time=0;
 

void setup() {
  pinMode(16,OUTPUT);
  pinMode(2,OUTPUT);
  
  digitalWrite(16, LOW);    // set GPIO16 low to reset OLED
  delay(50); 
  digitalWrite(16, HIGH); // while OLED is running, must set GPIO16 in high
  
  Serial.begin(9600);
  while (!Serial);
  Serial.println();
  Serial.println("LoRa Sender Test");
  
  SPI.begin(SCK,MISO,MOSI,SS);
  LoRa.setPins(SS,RST,DI0);
  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  //LoRa.onReceive(cbk);
//  LoRa.receive();
  Serial.println("init ok");
  display.init();
  display.flipScreenVertically();  
  display.setFont(ArialMT_Plain_10);
   
  delay(1500);
}

void loop() {

  // send packet
  LoRa.beginPacket();
  while(!LoRa.available())
  {
    delay_time++;
    if(delay_time==10000){
      delay_time=0;
      Serial.println("Connect fail");
      Serial.println("Restart");
      setup();
    }
  }
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;
  digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(2, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}