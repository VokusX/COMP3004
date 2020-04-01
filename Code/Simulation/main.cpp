#include "Simulation.h"
#include <iostream>
/* int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

*/

int main(int argc, char *argv[]) {

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

  }
  centralProcess.end();


  return 0;
}
