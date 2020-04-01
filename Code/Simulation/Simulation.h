#ifndef SIMULATION_H
#define SIMULATION_H

#include "CentralProcess.h"

#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <unistd.h>

class Simulation {
  public: 
    int initial_battery_power;
    Program selectProgram();
    Human human;
    int selectClientPainLevel();
    void simulateTreatment(int timeOfTherapy, int &battery);
    bool treatmentActive;
    int bootDevice();
    void initializeHuman();
};

#endif