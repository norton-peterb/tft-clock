#include <Arduino.h>
#include <TFT.h>
#include <SPI.h>
#include <math.h>
#include "SparkFunDS1307RTC.h"

#define CS 53
#define DC 9
#define RST 8

TFT TFTscreen = TFT(CS,DC,RST);

uint8_t hour = 0;
uint8_t minute = 0;

void setup() {
  TFTscreen.begin();
  TFTscreen.background(0x00,0x00,0x00);
  rtc.begin();
  rtc.set24Hour(false);
  rtc.writeSQW(SQW_SQUARE_1);
}

void drawHand(uint16_t angle, uint16_t length, uint16_t color) {
  double x = length * cos((angle * (PI / 180)));
  double y = length * sin((angle * (PI / 180)));
  TFTscreen.drawLine(80,64,80 + x,64 + y,color);
}

void loop() {
  delay(1000);
  TFTscreen.stroke(0xFF,0xFF,0xFF);
  TFTscreen.circle(80,64,60);
  uint8_t readHour = rtc.getHour();
  uint8_t readMinute = rtc.getMinute();
  if(readHour != hour || readMinute != minute) 
  {
    drawHand((hour * 30) + (minute / 2),29,0x0000);
    drawHand(minute * 6,58,0x0000);
    drawHand((readHour * 30) + (readMinute / 2),29,0x0AFF);
    drawHand(readMinute * 6,58,0x008F);
    hour = readHour;
    minute = readMinute;
  }
}