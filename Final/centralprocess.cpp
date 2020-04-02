#include "centralprocess.h"

CentralProcess::CentralProcess() {
    /*  What this function does is simulates the device being booted, as we all know in real life, devices are not always
      at 100% battery when booted so this generates the starting battery level randomly between 50 and 100. */
    srand (time (0)); // Helps achieve "true randomness"
    int battery = rand() % 50 + 50;
    std::cout << "Device has been booted." << std::endl;
    sleep(1);
    std::cout << "..." << std::endl; // Theatrics we all love them
    sleep(1);
    std::cout << "Initial Battery Power: " << battery << "." << std::endl;
    sleep(1);
    powerLevel = 0;
    batteryLevel = battery;
    timeOfTherapy = 0;
    totalPower = 0;
    isActive = 0;
    checkBatteryLevel();

    Program d;
    d.name = "default";
    d.freq = 0;
    d.waveform = "default";
    program = d;

}

void CentralProcess::end() {
  sleep(1);
  std::cout << "Program has been stopped! " << std::endl;
  std::cout << "Time of Therapy: " << timeOfTherapy << std::endl;
  int avgT = totalPower / timeOfTherapy;
  std::cout << "Average Power level during Treatment: " << avgT << std::endl;

}


void CentralProcess::runSim() {
    std::cout << "... " << std::endl; // Adding theatrics
    std::cout << "Electrocurrent Biofeedback in progress..." << std::endl;
    std::cout << "Running Program " << program.name << " with Frequency: " << program.freq << "HZ releasing " << program.waveform << " electrocurrent waveforms." << std::endl;

    /* For pain level, I broke it down into 5 tiers based on information available in research.
      Pain level 1 = 5-20    Power Level
      Pain level 2 = 20-40   Power Level
      Pain level 3 = 40-60   Power Level
      Pain level 4 = 60-80   Power Level
      Pain level 5 = 80-100  Power Level */

    srand (time (0)); // Helps achieve "true randomness"
    switch (powerLevel) {
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

    // More power uses more battery
    srand (time (0)); // Helps achieve "true randomness"
    int x2 = rand() % 5; // 1 out of 4 odds that battery goes down

    if (x2 == 2 ) {
        if(powerLevel < 20) {
            batteryLevel -= 1;
        } else if (powerLevel < 40) {
            batteryLevel -= 2;
        } else if (powerLevel < 60) {
            batteryLevel -= 3;
        } else if (powerLevel < 80) {
            batteryLevel -= 4;
        }
    }


    totalPower += powerLevel;
    std::cout << "Current Power Level is: " << powerLevel << std::endl;
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
  sleep(3);



}

void CentralProcess::checkBatteryLevel() {
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
    }

}


void CentralProcess::reset() {
    powerLevel = 0;
    timeOfTherapy = 0;
    totalPower = 0;
    isActive = 0;

    Program d;
    d.name = "default";
    d.freq = 0;
    d.waveform = "default";
    program = d;

}
