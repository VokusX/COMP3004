#include <iostream>

using namespace std;

#include "Simulation.h"


void Simulation::simulateTreatment(int timeOfTherapy, int &battery) {
  /* This is where things get interesting, I would like the odds of a treatment ending to get greater as it progresses
    similar to how a real life treatmnent would work, I also want the device's power level to respond dynamically to the 
    "inflamation level" aka the pain level we have, I also want the battery to respond to the power level and the treatment
    length to only add up when the device is touching the skin */

  srand (time (0)); // Helps achieve "true randomness"
  int x = rand() % 100; // Random Number out of one hundred.
  switch (human.painLevel) { // Since Pain and power level are correlated, just use use pain Level
    // More power uses more battery
      case 1:
        battery -= 1;
        break;
      case 2:
        battery -= 1;
        break;
      case 3:
        battery -= 2;
        break;
      case 4:
        battery -= 2;
        break;
      case 5:
        battery -= 3;
        break;
      default:
        battery -= 2;
      }

  if((x > 0) && (x < timeOfTherapy)) {
    treatmentActive = false;
    human.deviceOnSkin = false;
    std::cout << "User has decided to end treatment." << std::endl;
  } else {
    human.deviceOnSkin = true; //
  }

  // Deal with battery level
  switch (human.painLevel) { // Since Pain and power level are correlated, just use use pain Level
    // More power uses more battery
      case 1:
        battery -= 1;
        break;
      case 2:
        battery -= 1;
        break;
      case 3:
        battery -= 2;
        break;
      case 4:
        battery -= 2;
        break;
      case 5:
        battery -= 3;
        break;
      default:
        battery -= 2;
      }


}

int Simulation::bootDevice() {
  /*  What this function does is simulates the device being booted, as we all know in real life, devices are not always
  at 100% battery when booted so this generates the starting battery level randomly between 50 and 100. */
    srand (time (0)); // Helps achieve "true randomness"
    int battery = rand() % 50 + 50;
    std::cout << "Device has been booted." << std::endl;
    sleep(2);
    std::cout << "..." << std::endl; // Theatrics we all love them
    sleep(1);
    std::cout << "Initial Battery Power: " << battery << "." << std::endl;
    sleep(1);
    return battery;
}

void Simulation::initializeHuman() {
  /* Here I am going to set a persons pain level between 1 and 5 to help determine how much power to use. */
  human.deviceOnSkin = false;

  srand (time (0)); // Helps achieve "true randomness"
  int r = rand() % 2 + 4; // Random between 1 and 3
  human.painLevel = r;
}

Program Simulation::selectProgram() {
  /* Here we offer 3 programs based off the Denas patent:
  1. Back pain: 215hz;
  2. Bloating: 5hz;
  3. Constipation: 140hz; */
  Program program;
  std::cout << "User is picking a program..." << std::endl;
  sleep(2);
  std::cout << "Person has a pain level of: " << human.painLevel << "." << std::endl;
  sleep(2);
  srand (time (0)); // Helps achieve "true randomness"
  int p = rand() % 2 + 1; // Random between 1 and 3

  if (p == 1) {
    std::cout << "User has selected program 1: Back pain." << std::endl;
    program.name = "Back Pain";
    program.freq = 215;
    program.waveform = "sinusoidal";
  } else if (p == 2) {
    std::cout << "User has selected program 2: Bloating." << std::endl;
    program.name = "Bloating";
    program.freq = 5;
    program.waveform = "sinusoidal";

  } else if (p == 3) {
    std::cout << "User has selected program 3: Constipation." << std::endl;
    program.name = "Constipation";
    program.freq = 140;
    program.waveform = "sinusoidal";
  }
  sleep(3);

  std::cout << "User has activated program." << std::endl;

  sleep(2);

  return program;
}