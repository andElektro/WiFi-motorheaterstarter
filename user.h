#ifndef USER_H
#define USER_H

#include "relay.h"
#include "startTime.h"
#include "sensor.h"

class User : public Relay
{
  private:
    static unsigned short int numUsers;
    String userName;
    StartTime* timePtr = nullptr;

  public:
    bool hasStartTime = false;

  public:
    User(String _userName, short int _pin);
    ~User();
    //Time
    void setStopTime(int& _stopMinute, int& _stopHour, int* _days);
    void deleteStopTime();
    bool checkStartTime(float& _temp);
    bool checkStopTime();
    void setCurrentTime(int& _minute, int& _hour, int& _day);
};

#endif
