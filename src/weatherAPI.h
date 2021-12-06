#ifndef _weatherAPI_h
#define _weatherAPI_h

#include "includes.h"
#include "timeAPI.h"
String result;
void updateWeatherInfo()
{
  // check the wifi connectivity and display weather info
  if(WiFi.isConnected()){wifiIconDisp();}
  else{wifiIconDisconnect();reconnectWifi();if(WiFi.isConnected()){wifiIconDisp();}}
  updateTime();
  if(client.connect(servername,80))
  {
    client.println("GET /data/2.5/weather?id="+CityID+"&units=metric&appid="+APIKEY);
    client.println("HOST: api.openweathermap.org");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();
  }
  else
  {
    Serial.println("connection failed");
    Serial.println();
  }
  while(client.connected() && !client.available())
  {
    delay(1);
  }
  while(client.connected() || client.available())
  {
    char c = client.read();
    result = result+c;
  }
  client.stop();
  result.replace('[',' ');
  result.replace(']',' ');
  Serial.println(result);
  char jsonArray[result.length()+1];
  result.toCharArray(jsonArray,sizeof(jsonArray));
  jsonArray[result.length()+1] = '\0';
  StaticJsonDocument<1024> doc;
  DeserializationError error = deserializeJson(doc,jsonArray);
  if(error)
  {
   Serial.print(F("deserializeJson() failed with code "));
   Serial.println(error.c_str());
   return;
  }
  String location = doc["name"];
  String country = doc["sys"]["country"];
  int temperature = doc["main"]["temp"];
  int humidity = doc["main"]["humidity"];
  float pressure = doc["main"]["pressure"];
  //int id = doc["id"];
  float Speed = doc["wind"]["speed"];
  //int degree = doc["wind"]["deg"];
  //float longitude = doc["coord"]["lon"];
  //float latitude = doc["coord"]["lat"];
  // printing data on serial port for debugging purpose
  //display.fillScreen(ILI9341_BLACK);
  // Serial.print("City: "); Serial.println(location);
  // Serial.print("Country: "); Serial.println(country);
  // Serial.print("Temp: "); Serial.println(temperature);
  // Serial.print("Humidity: "); Serial.println(humidity);
  // Serial.print("Pressure: "); Serial.println(pressure);
  // Serial.print("Speed: "); Serial.println(Speed);
  
  display.setCursor(200,60); display.setTextColor(ILI9341_YELLOW,ILI9341_BLACK); display.setTextSize(2);
  display.print(location); 
  display.setCursor(280,80); display.setTextColor(ILI9341_YELLOW,ILI9341_BLACK); display.setTextSize(2);
  display.print(country);
  display.setCursor(20,60); display.setTextColor(ILI9341_YELLOW); display.setTextSize(6);
  display.print(temperature); display.fillCircle(110,70,9,ILI9341_YELLOW); display.println(" C");
  display.setCursor(140,120); display.setTextColor(ILI9341_CYAN,ILI9341_BLACK); display.setTextSize(2); display.print("Humidity: ");
  display.print(humidity); display.print(" %");
  display.setCursor(60,140); display.setTextColor(ILI9341_PINK,ILI9341_BLACK); display.setTextSize(2); display.print("Pressure: ");
  display.print(pressure); display.print(" hpa");
  display.setCursor(70,160); display.setTextColor(ILI9341_MAGENTA,ILI9341_BLACK); display.setTextSize(2);
  display.print("Wind Speed: "); display.print(Speed);display.println(" m/s");
  display.setCursor(90,180); display.setTextColor(ILI9341_GREEN,ILI9341_BLACK); display.setTextSize(2);
  display.print("Longitude: "); display.print(longitude);
  display.setCursor(110,200); display.setTextColor(ILI9341_GREENYELLOW,ILI9341_BLACK); display.setTextSize(2);
  display.print("Latitude: "); display.print(latitude);
}
#endif