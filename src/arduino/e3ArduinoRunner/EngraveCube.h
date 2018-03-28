
#ifndef EngraveCube_h
#define EngraveCube_h
#endif

#include <stdlib.h>
#include <AccelStepper.h>
#include "config.h"

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#include <wiring.h>
#endif

class EngraveCube {

public:
  EngraveCube();

  char* parse(char *cmdBuffer);

  boolean isRunning();

  boolean run();


private:

  char* cmdG0(char *cmdBuffer);

  char* cmdG28(char *cmdBuffer);

  AccelStepper _stepperX;
  AccelStepper _stepperY;

};
