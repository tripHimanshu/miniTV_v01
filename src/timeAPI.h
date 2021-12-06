#ifndef _timeAPI_h
#define _timeAPI_h
#include "includes.h"

void updateTime()
{
    timeClient.update();
    formattedDate = timeClient.getFormattedDate();
    Serial.println(formattedDate); 
    // Extract date
    int splitT = formattedDate.indexOf("T");
    dayStamp = formattedDate.substring(0, splitT);
    Serial.print("DATE: ");
    Serial.println(dayStamp);
    // Extract time
    timeStamp = formattedDate.substring(splitT+1, formattedDate.length()-4);
    Serial.print("HOUR: ");
    Serial.println(timeStamp);
    display.setCursor(120,10); display.setTextColor(ILI9341_WHITE,ILI9341_BLACK); display.setTextSize(2);
    display.print(timeStamp); 
    display.setCursor(100,30); display.setTextColor(ILI9341_WHITE,ILI9341_BLACK); display.setTextSize(2);
    display.print(dayStamp); 
}


#endif