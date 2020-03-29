/* COMP 3004 MICROCURRENT BIOFEEDBACK DEVICE TEAM 8
  Skylar Bruce 101032049 */


#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <unistd.h>


class Human {
  public:
    bool deviceOnSkin;
    int painLevel;
};

class Program {
  public:
    std::string name; 
    int freq;
    std::string waveform;
};

class CentralProcess {
  public:
    Program program; 
    int powerLevel, batteryLevel, timeOfTherapy, totalPower;
    void bioFeedbackLoop(bool isTouchingSkin, int painLevel);
    void checkBatteryLevel(bool &treatment);
    void end();
};

void CentralProcess::end() {
  sleep(1);
  std::cout << "Program has come to a stop." << std::endl;
  std::cout << "Time of Therapy: " << timeOfTherapy << " cycles." << std::endl;
  int avgT = totalPower / timeOfTherapy;
  std::cout << "Average Power level during Treatment: " << avgT << " volts." << std::endl;

}

void CentralProcess::bioFeedbackLoop(bool isTouchingSkin, int painLevel) {
  std::cout << "... " << std::endl; // Adding theatrics
  std::cout << "Electrocurrent Biofeedback in progress..." << std::endl;
  std::cout << "Running Program " << program.name << " with Frequency: " << program.freq << "HZ releasing " << program.waveform << " electrocurrent waveforms." << std::endl;
  /* For pain level, I broke it down into 5 tiers based on information available in research.
    Pain level 1 = 5-20    Power Level
    Pain level 2 = 20-40   Power Level
    Pain level 3 = 40-60   Power Level
    Pain level 4 = 60-80   Power Level
    Pain level 5 = 80-100  Power Level */

  if(isTouchingSkin) {
      timeOfTherapy += 1; // Only add if it is touching the skin.
      srand (time (0)); // Helps achieve "true randomness"
      switch (painLevel) {
      case 1:
        powerLevel = rand() % 15 + 5;
        break;
      case 2:
        powerLevel = rand() % 20 + 20;
        break;
      case 3:
        powerLevel = rand() % 20 + 40;
        break;
      case 4:
        powerLevel = rand() % 20 + 60;
        break;
      case 5:
        powerLevel = rand() % 20 + 80;
        break;
      default:
        powerLevel = 50;
      }
  } else {
    std::cout << "Alert: Device is not on skin" << std::endl;
    powerLevel = 50;
  }

  /* One in three odds = Freq stays same, or goes up or goes down to dynamically alter freq so body does not become accustumed to it */
  srand (time (0)); // Helps achieve "true randomness"
  int x = rand() % 2;

  switch (x) {
      case 0:
        program.freq += 2;
        break;
      case 1:
        program.freq -= 2;
        break;
      default:
        program.freq += 0;
      }

  totalPower += powerLevel;
  std::cout << "Current Power Level is: " << powerLevel << std::endl;



}

void CentralProcess::checkBatteryLevel(bool &treatment) {
  if ((batteryLevel  < 60) && (batteryLevel > 40)) {
      std::cout << "Alert: Battery under 60, please watch carefully." << std::endl;
    }
  if ((batteryLevel  < 40) && (batteryLevel > 20)) {
      std::cout << "Alert: Battery under 40, please watch carefully." << std::endl;
    }
  if ((batteryLevel  < 20) && (batteryLevel > 10)) {
      std::cout << "Alert: Battery under 20, please watch carefully." << std::endl;
    }
  if ((batteryLevel  < 10) && (batteryLevel > 1)) {
      std::cout << "Alert: Battery under 10, please watch carefully." << std::endl;
    }
  if (batteryLevel  < 1) {
      std::cout << "Alert: Battery has died." << std::endl;
      treatment = false;
    }

}

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


int main() {

  CentralProcess centralProcess;

  Simulation sim;

  // Lets initialize our lovely human.
  sim.initializeHuman();

  centralProcess.timeOfTherapy = 0;
  centralProcess.totalPower = 0;
  centralProcess.batteryLevel = sim.bootDevice(); // Let's determine the initial battery power.

      // centralProcess.checkBatteryLevel();

  // Now the user wants to select a program;
  centralProcess.program = sim.selectProgram();
  // The program is selected so user decides to start treatment, begin biofeedback loop.
  sim.treatmentActive = true;

  while(sim.treatmentActive) {
    sim.simulateTreatment(centralProcess.timeOfTherapy, centralProcess.batteryLevel);
    centralProcess.bioFeedbackLoop(sim.human.deviceOnSkin, sim.human.painLevel);
    centralProcess.checkBatteryLevel(sim.treatmentActive);
    sleep(3);

  }
  centralProcess.end();


  return 0;
}