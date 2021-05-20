#include "user.h"

unsigned short int User::numUsers = 0;

User::User(String _userName, short int _pin)
  :  Relay(_pin), userName(_userName)
{
  numUsers++;
}

User::~User()
{
  numUsers--;
}

//Time
void User::setStopTime(int& _stopMinute, int& _stopHour, int* _days) {
  if (timePtr != nullptr) {
    delete timePtr;
    timePtr = new StartTime(_stopMinute, _stopHour, _days);
  }
  else
    timePtr = new StartTime(_stopMinute, _stopHour, _days);

  hasStartTime = true;
}

void User::deleteStopTime() {
  delete timePtr;
  timePtr = nullptr;
  hasStartTime = false;
}

bool User::checkStartTime(float& _temp) {
  if (timePtr != nullptr) {
    return timePtr->checkForStart(_temp);
  }
  else
    return false;
}

bool User::checkStopTime() {
  if (timePtr != nullptr) {
    return timePtr->checkForStop();
  }
  else
    return false;
}

void User::setCurrentTime(int& _minute, int& _hour, int& _day) {
  if (timePtr != nullptr) {
    timePtr->setCurrentTime(_minute, _hour, _day);
  }
}
