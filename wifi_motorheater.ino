#include "user.h"

#include <SPI.h>
#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>

#include <TimeLib.h>
#include <WidgetRTC.h>

#define BLYNK_PRINT Serial

//Blynk colormap
#define BLYNK_GREEN     "#23C48E"
#define BLYNK_BLUE      "#04C0F8"
#define BLYNK_YELLOW    "#ED9D00"
#define BLYNK_RED       "#D3435C"
#define BLYNK_DARK_BLUE "#5F7CD8"

///////////////////////////////////////////////
//Objects
BlynkTimer timer;
WidgetRTC rtc;
User User1 = User("XXX", 7);
User User2 = User("XXX", 8);
Sensor tempSensor;
WidgetLED User1Led(V1);
WidgetLED User2Led(V2);
///////////////////////////////////////////////

///////////////////////////////////////////////
//Variables
bool user1ButtonState = false;
bool user2ButtonState = false;
bool norwegianReset = false;
///////////////////////////////////////////////

///////////////////////////////////////////////
//WI-FI settings
char auth[] = "XXX";
char ssid[] = "XXX";
char pass[] = "XXX";
///////////////////////////////////////////////

///////////////////////////////////////////////
//RTC
BLYNK_CONNECTED()
{
  //Synchronize time on connection
  rtc.begin();
}
///////////////////////////////////////////////

///////////////////////////////////////////////
//Set widget led state
void setUserLedState(WidgetLED& _UserXLed, User& _UserX) {
  if (_UserX.getRelayState()) {
    _UserXLed.setColor(BLYNK_GREEN);
    _UserXLed.on();
  }
  else if (_UserX.hasStartTime) {
    _UserXLed.setColor(BLYNK_YELLOW);
    _UserXLed.on();
  }
  else {
    //_UserXLed.setColor(BLYNK_RED);
    _UserXLed.off();
  }
}
///////////////////////////////////////////////

///////////////////////////////////////////////
//Get widget stop time
BLYNK_WRITE(V11) {
  //V11 is User1
  int tmp[7] = {0, 0, 0, 0, 0, 0, 0};
  TimeInputParam t(param);
  if (t.hasStartTime()) {
    for (int i = 1; i <= 7; i++) {
      if (t.isWeekdaySelected(i)) {
        tmp[i - 1] = i;
      }
      else
        tmp[i - 1] = 0;
    }
    int m = t.getStartMinute();
    int h = t.getStartHour();
    User1.setStopTime(m, h, tmp);
    Blynk.notify("XXX tid uppdaterad");
    setUserLedState(User1Led, User1);
  }
  else {
    User1.deleteStopTime();
    Blynk.notify("XXX tid borttagen");
    setUserLedState(User1Led, User1);
  }
}

BLYNK_WRITE(V12) {
  //V12 is User2
  int tmp[7] = {0, 0, 0, 0, 0, 0, 0};
  TimeInputParam t(param);
  if (t.hasStartTime()) {
    for (int i = 1; i <= 7; i++) {
      if (t.isWeekdaySelected(i))
        tmp[i - 1] = i;
      else
        tmp[i - 1] = 0;
    }
    int m = t.getStartMinute();
    int h = t.getStartHour();
    User2.setStopTime(m, h, tmp);
    Blynk.notify("XXX tid uppdaterad");
    setUserLedState(User2Led, User2);
  }
  else {
    User2.deleteStopTime();
    Blynk.notify("XXX tid borttagen");
    setUserLedState(User2Led, User2);
  }
}
///////////////////////////////////////////////

///////////////////////////////////////////////
//Get widget button state
BLYNK_WRITE(V21) //In Blynkworld BLYNK_WRITE is read
{
  //V21 is button User1
  //param.asInt() return 0 if button off and 1 if on.
  user1ButtonState = param.asInt();
  if (user1ButtonState && !User1.getRelayState()) {
    User1.relayOn();
    setUserLedState(User1Led, User1);
    Blynk.notify("XXX motorvärmare har startats");
  }
  else if (!user1ButtonState && User1.getRelayState()) {
    User1.relayOff();
    setUserLedState(User1Led, User1);
    Blynk.notify("XXX motorvärmare har stängts av");
  }
}

BLYNK_WRITE(V22)
{
  //V22 is button User2
  user2ButtonState = param.asInt();
  if (user2ButtonState && !User2.getRelayState()) {
    User2.relayOn();
    setUserLedState(User2Led, User2);
    Blynk.notify("XXX motorvärmare har startats");
  }
  else if (!user2ButtonState && User2.getRelayState()) {
    User2.relayOff();
    setUserLedState(User2Led, User2);
    Blynk.notify("XXX motorvärmare har stängts av");
  }
}
///////////////////////////////////////////////

///////////////////////////////////////////////
//Functions to loop
void setRelay() {
  if (Blynk.connected()) {

    if (!norwegianReset) {
      /*
         V0=temp
         V1=led user 1
         V2=led user 2
         V11=stop time user 1
         V12=strop time user 2
         V21=button user 1
         V22=button user 2
      */
      Blynk.syncVirtual(V0, V1, V2, V11, V12, V21, V22);
      norwegianReset = true;
    }

    int m = minute();
    int h = hour();
    int dayadjustment = -1;
    if (weekday() == 1) {
      dayadjustment = 6; // needed for Sunday Time library is day 1 and Blynk is day 7
    }
    int d = weekday() + dayadjustment;
    User1.setCurrentTime(m, h, d);
    User2.setCurrentTime(m, h, d);

    float _temp = tempSensor.getTemp();
    Blynk.virtualWrite(V0, _temp);

    //User1
    if (!user1ButtonState && !User1.getRelayState()) {
      if (User1.checkStartTime(_temp)) {
        User1.relayOn();
        Blynk.virtualWrite(V21, 1);
        setUserLedState(User1Led, User1);
        Blynk.notify("XXX motorvärmare har startats");
      }
    }
    else if (User1.checkStopTime()) {
      User1.relayOff();
      Blynk.virtualWrite(V21, 0);
      setUserLedState(User1Led, User1);
      Blynk.notify("XXX motorvärmare har stängts av");
    }

    //User2
    if (!user2ButtonState && !User2.getRelayState()) {
      if (User2.checkStartTime(_temp)) {
        User2.relayOn();
        Blynk.virtualWrite(V22, 1);
        setUserLedState(User2Led, User2);
        Blynk.notify("XXX motorvärmare har startats");
      }
    }
    else if (User2.checkStopTime()) {
      User2.relayOff();
      Blynk.virtualWrite(V22, 0);
      setUserLedState(User2Led, User2);
      Blynk.notify("XXX motorvärmare har stängts av");
    }
  }
}
///////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  setSyncInterval(10 * 60); //Sync interval for RTC in seconds (10 minutes)
  timer.setInterval(3 * 1000L, setRelay); //timer will run every third sec
}

void loop() {
  Blynk.run();
  timer.run();
}
