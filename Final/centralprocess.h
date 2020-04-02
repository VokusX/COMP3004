#ifndef CENTRALPROCESS_H
#define CENTRALPROCESS_H

#include "program.h"


#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <unistd.h>

class CentralProcess {
  public:
    CentralProcess();
    Program program;
    int powerLevel, batteryLevel, timeOfTherapy, totalPower, isActive;
    void bioFeedbackLoop(bool isTouchingSkin, int painLevel);
    void checkBatteryLevel();
    void end();
    void reset();
    void runSim();
};

#endif
