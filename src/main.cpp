// main file 
// include the header files 
#include "includes.h"
#include "weatherAPI.h"
#include "pollutionAPI.h"
// global variables for external interrupt and timer operation
int function = 1;
int timeCount = 0;
// function to display AKGEC Logo on display 
void akgecLogoDisp()
{
  display.begin(); // start TFT display
  display.fillScreen(ILI9341_BLACK);  // fill display screen with black color
  display.setRotation(3); // rotate the display orientation  
  display.drawRGBBitmap(0,0,(uint16_t *)ALOGO,ALOGO_WIDTH,ALOGO_HEIGHT);
  delay(5000);
}
// function to display Idea Lab Logo
void ideaLogoDisp()
{
  display.fillScreen(ILI9341_BLACK);  // fill display screen with black color
  display.drawRGBBitmap(0,0,(uint16_t *)ILOGO,I_WIDTH,I_HEIGHT);
  delay(5000);
}
// display FDP message 
void fdpMsgDisp()
{
  display.fillScreen(ILI9341_NAVY);
  display.setCursor(30,26); display.setTextColor(ILI9341_RED); display.setTextSize(4);
  display.println("ADVANCE FDP");
  display.setCursor(35,70); display.setTextColor(ILI9341_YELLOW); display.setTextSize(5);
  display.println("IDEA LAB");
  display.setCursor(60,120); display.setTextColor(ILI9341_GREEN); display.setTextSize(6);
  display.println("AICTE");
  display.setCursor(40,180); display.setTextColor(ILI9341_CYAN); display.setTextSize(2);
  display.println("DEC 01 to 07, 2021");
  delay(5000);
}
// function to connect with wifi
void connectWiFi()
{
  display.fillScreen(ILI9341_BLACK);
  display.setCursor(40,50); display.setTextColor(ILI9341_WHITE); display.setTextSize(2);
  display.println("Connecting to WiFi");
  display.println("");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
  display.setCursor(40,100);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      display.print("*");
  }
  display.setTextSize(4); display.setCursor(30,150);
  display.println("CONNECTED");
}

// ISR for External Interrupt
void IRAM_ATTR change_display()
{
  function = 0;
  //Serial.println("interrupt occured");Serial.println(function);
}
// ISR for timer overflow
void IRAM_ATTR onTimer() 
{
  timeCount++;
  if(timeCount==60){interruptbool1=true;timeCount=0;}
  else{interruptbool1=false;}
}
// setup code
void setup()
{
  Serial.begin(115200);
  Serial.println("Code Execution Start..");
  akgecLogoDisp();
  ideaLogoDisp();
  fdpMsgDisp();
  connectWiFi();
  delay(1000);
  display.fillScreen(ILI9341_BLACK);
  // external interrupt pin is input pin with internal pull-up resistance
  pinMode(change_channel,INPUT_PULLUP);
  attachInterrupt(change_channel,change_display,FALLING);
  timer = timerBegin(0, 80, true);  //Begin timer with 1 MHz frequency (80MHz/80)
  timerAttachInterrupt(timer, &onTimer, true);  //Attach the interrupt to Timer1
  //Calculate the time interval between two readings, or more accurately, the number of cycles between two readings
  unsigned int timerFactor = 1000000/SamplingRate; 
  timerAlarmWrite(timer, timerFactor, true);  //Initialize the timer
  timerAlarmEnable(timer); 
  // check the wifi connectivity and display weather info
  updateWeatherInfo();
  
}
// loop
void loop() 
{
  if(interruptbool1){
    display.fillScreen(ILI9341_BLACK);
    if(WiFi.isConnected()){wifiIconDisp();}
    else{wifiIconDisconnect();reconnectWifi();if(WiFi.isConnected()){wifiIconDisp();}}
    updateWeatherInfo();
  }
  if(function==0)
  {
    updateAQI();delay(5000);
    function=1;display.fillScreen(ILI9341_BLACK);
    updateWeatherInfo();
  }
}