// main header file including other header files and global variables 
#ifndef _includes_h
#define _includes_h
// project header files 
#include <WiFi.h>
#include<Arduino.h>
#include<ArduinoJson.h>
#include<Adafruit_ILI9341.h>
#include<Adafruit_I2CDevice.h>
#include<time.h>
#include<NTPClient.h>
// header files for images used in project 
#include "Akgec_Logo.h"
#include "wifiDark.h"
#include "ideaLabImage.h"
#include "wifiDisconnect.h"
// pin connections of ILI9341 TFT LCD display and ESP32 Devkit Module
#define TFT_MISO 19   // Master In Slave Out 
#define TFT_MOSI 23   // Master Out Slave In 
#define TFT_CLK 18    // Serial Clock
#define TFT_CS  15    // Chip select control pin
#define TFT_DC  4    // Data/Command control pin
#define TFT_RST 2     // Reset Pin
//Create object for TFT Display from Adafruit_ILI9431 Library
Adafruit_ILI9341 display = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
// create object for UDP connection with NTP server
WiFiUDP ntpUDP;
// object for NTPClient
NTPClient timeClient(ntpUDP,"my.pool.ntp.org",19800,60000);
// global variables for time and date display
String formattedDate;
String dayStamp;
String timeStamp;
//object for WiFi Client 
WiFiClient client;
// credential for wifi connection 
// replace the ssid and password according to your connection
const char* ssid = "your ssid";
const char* password = "your password";
// API key from openweathermap.org
// replace the API key with yours API key
String APIKEY = "your api key";
// City ID, latitude and longitude (for Ghaziabad, India); replace this for your city
String CityID = "your city ID";
String latitude = "latitude of your city";
String longitude = "longitude of your city";
//global variable for http connection 
bool id = false;
char servername[] = "api.openweathermap.org";
// Pin for External Interrupt connection 
#define change_channel 22
// timer pointer 
hw_timer_t * timer = NULL; 
// timer interrupt variables
volatile bool interruptbool1 = false;
int SamplingRate = 1; //Read 1 values in one second.
// function to display wifi icon 
void wifiIconDisp()
{
  display.drawRGBBitmap(260,10,(uint16_t *)WF_LOGO,WF_WIDTH,WF_HEIGHT);
}
// function to display wifi disconnect icon 
void wifiIconDisconnect()
{
  display.drawRGBBitmap(260,10,(uint16_t *)WFD_LOGO,WFD_WIDTH,WFD_HEIGHT);
}
// function to reconnect with wifi
void reconnectWifi()
{
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {delay(500);}
}
#endif