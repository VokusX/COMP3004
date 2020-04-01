#ifndef PROGRAM_H
#define PROGRAM_H

#include "Human.h"

#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <unistd.h>

class Program {
  public:
    std::string name; 
    int freq;
    std::string waveform;
};


#endif