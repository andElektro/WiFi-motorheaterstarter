#include "startTime.h"

StartTime::StartTime(int& _stopMinute, int& _stopHour, int* _days)
  : stopMinute(_stopMinute), stopHour(_stopHour)
{
  for (int i = 0; i < 7; i++) {
    days[i] = _days[i];
  }
  currentMinute = 99;
  currentHour = 99;
  currentDay = 99;
}

StartTime::~StartTime()
{
}

bool StartTime::checkForStart(float& _temp) {
  if (_temp <= 10) {
    for (int d : days) {
      if (d == currentDay) {
        if (_temp <= 10 && _temp > 5)
        {
          //40min
          setStartTime(0, 40);
          if (currentHour == startHour && currentMinute == startMinute)
          {
            return true;
          }
        }
        else if (_temp <= 5 && _temp > -5)
        {
          //1h10min
          setStartTime(1, 10);
          if (currentHour == startHour && currentMinute == startMinute)
          {
            return true;
          }
        }
        else if (_temp <= -5 && _temp > -10)
        {
          //1h40min
          setStartTime(1, 40);
          if (currentHour == startHour && currentMinute == startMinute)
          {
            return true;
          }
        }
        else if (_temp <= -10 && _temp > -20)
        {
          //2h10min
          setStartTime(2, 10);
          if (currentHour == startHour && currentMinute == startMinute)
          {
            return true;
          }
        }
        else if (_temp <= -20)
        {
          //3h10min
          setStartTime(3, 10);
          if (currentHour == startHour && currentMinute == startMinute)
          {
            return true;
          }
        }
      }
    }
  }
  return false;
}

bool StartTime::checkForStop() {
  if (currentHour == stopHour && currentMinute == stopMinute) {
    return true;
  }
  return false;
}

void StartTime::setCurrentTime(int& _minute, int& _hour, int& _day) {
  currentMinute = _minute;
  currentHour = _hour;
  currentDay = _day;
}

void StartTime::setStartTime(short int _runHours, short int _runMinutes)
{
  if (stopMinute - _runMinutes < 0)
  {
    startMinute = 60 - abs(stopMinute - _runMinutes);
    setStartHour(true, _runHours);
  }
  else
  {
    startMinute = stopMinute - _runMinutes;
    setStartHour(false, _runHours);
  }
}

void StartTime::setStartHour(bool _hourOverflow, short int& _runHours)
{
  if (_hourOverflow)
  {
    if (startHour - _runHours < 0)
    {
      startHour = 24 - abs(stopHour - _runHours) - 1;
    }
    else
    {
      startHour = stopHour - _runHours - 1;
    }
  }
  else
  {
    if (startHour - _runHours < 0)
    {
      startHour = 24 - abs(stopHour - _runHours);
    }
    else
    {
      startHour = stopHour - _runHours;
    }
  }
}
