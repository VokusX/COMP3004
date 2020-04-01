#ifndef CENTRALPROCESS_H
#define CENTRALPROCESS_H

#include "Program.h"


#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <unistd.h>

class CentralProcess {
  public:
    Program program; 
    int powerLevel, batteryLevel, timeOfTherapy, totalPower;
    void bioFeedbackLoop(bool isTouchingSkin, int painLevel);
    void checkBatteryLevel(bool &treatment);
    void end();
};

#endif