#ifndef STARTTIME_H
#define STARTTIME_H

#include <Arduino.h>

class StartTime
{
  private:
    short int startMinute;
    short int startHour;
    short int stopMinute;
    short int stopHour;
    int days[7] = {0, 0, 0, 0, 0, 0, 0};
    int currentMinute;
    int currentHour;
    int currentDay;

  public:
    StartTime(int& _stopMinute, int& _stopHour, int* _days);
    ~StartTime();
    bool checkForStart(float& _temp);
    bool checkForStop();
    void setCurrentTime(int& _minute, int& _hour, int& _day);

  private:
    void setStartTime(short int _runHours, short int _runMinutes);
    void setStartHour(bool _hourOverflow, short int& _runHours);
};


#endif
