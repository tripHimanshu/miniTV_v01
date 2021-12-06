#ifndef _pollutionAPI_h
#define _pollutionAPI_h

#include "includes.h"

String result_aqi;

void updateAQI()
{
  display.fillScreen(ILI9341_BLACK);
  if(client.connect(servername,80))
  {
    client.println("GET /data/2.5/air_pollution?lat="+latitude+"&lon="+longitude+"&appid="+APIKEY);
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
    result_aqi = result_aqi+c;
  }
  client.stop();
  result_aqi.replace('[',' ');
  result_aqi.replace(']',' ');
  Serial.println(result_aqi);
  char jsonArray[result_aqi.length()+1];
  result_aqi.toCharArray(jsonArray,sizeof(jsonArray));
  jsonArray[result_aqi.length()+1] = '\0';
  StaticJsonDocument<1024> doc;
  DeserializationError error = deserializeJson(doc,jsonArray);
  if(error)
  {
    Serial.print(F("deserializeJson() failed with code "));
    Serial.println(error.c_str());
    return;
  }
  float aqi = doc["list"]["main"]["aqi"];
  float co = doc["list"]["components"]["co"];
  float no = doc["list"]["components"]["no"];
  float no2 = doc["list"]["components"]["no2"];
  float o3 = doc["list"]["components"]["o3"];
  float so2 = doc["list"]["components"]["so2"];
  float pm2_5 = doc["list"]["components"]["pm2_5"];
  float pm10 = doc["list"]["components"]["pm10"];
  float nh3 = doc["list"]["components"]["nh3"];
  
  Serial.println();
  Serial.print("AQI ");Serial.println(aqi);
  Serial.print("CO ");Serial.println(co);
  // display on LCD
  
  if(aqi==1)
    {
        //display.fillScreen(ILI9341_GREEN);
        display.setCursor(40,20);display.setTextColor(ILI9341_GREEN);display.setTextSize(3);
        display.print("EXCELLENT AQI");
        display.setCursor(100,50);display.setTextColor(ILI9341_GREEN);display.setTextSize(3);
        display.print("[0 - 100]");
        display.println();
        display.setCursor(0,80);display.setTextColor(ILI9341_WHITE);display.setTextSize(1);
        display.print(" CO: ");display.println(co);
        display.print(" NO: ");display.println(no);
        display.print(" NO2: ");display.println(no2);
        display.print(" O3: ");display.println(o3);
        display.print(" SO2: ");display.println(so2);
        display.print(" PM2_5: ");display.println(pm2_5);
        display.print(" PM10: ");display.println(pm10);
        display.print(" NH3: ");display.println(nh3);
    }
    if(aqi==2)
    {
        display.setCursor(60,20);display.setTextColor(ILI9341_GREENYELLOW);display.setTextSize(3);
        display.print("GOOD AQI");
        display.setCursor(60,50);display.setTextColor(ILI9341_GREENYELLOW);display.setTextSize(3);
        display.print("[100 - 200]");
        display.println();
        display.setCursor(0,80);display.setTextColor(ILI9341_WHITE);display.setTextSize(2);
        display.print(" CO: ");display.println(co);
        display.print(" NO: ");display.println(no);
        display.print(" NO2: ");display.println(no2);
        display.print(" O3: ");display.println(o3);
        display.print(" SO2: ");display.println(so2);
        display.print(" PM2_5: ");display.println(pm2_5);
        display.print(" PM10: ");display.println(pm10);
        display.print(" NH3: ");display.println(nh3);

    }
    if(aqi==3)
    {
        display.setCursor(40,20);display.setTextColor(ILI9341_YELLOW);display.setTextSize(3);
        display.print("MODERATE AQI");
        display.setCursor(60,50);display.setTextColor(ILI9341_YELLOW);display.setTextSize(3);
        display.print("[200 - 300]");
        display.println();
        display.setCursor(0,80);display.setTextColor(ILI9341_WHITE);display.setTextSize(2);
        display.print(" CO: ");display.println(co);
        display.print(" NO: ");display.println(no);
        display.print(" NO2: ");display.println(no2);
        display.print(" O3: ");display.println(o3);
        display.print(" SO2: ");display.println(so2);
        display.print(" PM2_5: ");display.println(pm2_5);
        display.print(" PM10: ");display.println(pm10);
        display.print(" NH3: ");display.println(nh3);
    }
    if(aqi==4)
    {
        display.setCursor(60,20);display.setTextColor(ILI9341_ORANGE);display.setTextSize(3);
        display.print("POOR AQI");
        display.setCursor(60,50);display.setTextColor(ILI9341_ORANGE);display.setTextSize(3);
        display.print("[300 - 400]");
        display.println();
        display.setCursor(0,80);display.setTextColor(ILI9341_WHITE);display.setTextSize(2);
        display.print(" CO: ");display.println(co);
        display.print(" NO: ");display.println(no);
        display.print(" NO2: ");display.println(no2);
        display.print(" O3: ");display.println(o3);
        display.print(" SO2: ");display.println(so2);
        display.print(" PM2_5: ");display.println(pm2_5);
        display.print(" PM10: ");display.println(pm10);
        display.print(" NH3: ");display.println(nh3);

    }
    if(aqi==5)
    {
        //display.fillScreen(ILI9341_RED);
        display.setCursor(40,20);display.setTextColor(ILI9341_RED);display.setTextSize(3);
        display.print(" SEVERE AQI");
        display.setCursor(60,50);display.setTextColor(ILI9341_RED);display.setTextSize(3);
        display.print("[ > 400]");
        display.println();
        display.setCursor(0,80);display.setTextColor(ILI9341_WHITE);display.setTextSize(2);
        display.print(" CO: ");display.println(co);
        display.print(" NO: ");display.println(no);
        display.print(" NO2: ");display.println(no2);
        display.print(" O3: ");display.println(o3);
        display.print(" SO2: ");display.println(so2);
        display.print(" PM2_5: ");display.println(pm2_5);
        display.print(" PM10: ");display.println(pm10);
        display.print(" NH3: ");display.println(nh3);
    }
    //delay(5000);
    //display.fillScreen(ILI9341_BLACK);

}

#endif