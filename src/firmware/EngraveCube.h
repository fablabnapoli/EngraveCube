
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

  typedef enum name {
    DIR_CW = 1,
    DIR_CCW = -1
  } DIRECTION;
  EngraveCube();

  char* parse(char *cmdBuffer);

  boolean isRunning();

  void run();

  void EngraveCube::runSpeed();

  boolean getEndstopX();

  boolean getEndstopY();

  char* cmdG0(char *cmdBuffer);

  char* cmdG28();

private:


  AccelStepper _stepperX;
  AccelStepper _stepperY;

};
