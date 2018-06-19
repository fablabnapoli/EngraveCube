#ifndef e3Utils_h
#define e3Utils_h


#include <stdlib.h>
// #include <AccelStepper.h>
#include "config.h"

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#include <wiring.h>
#endif

int readline(int readch, char *buffer, int len);

void setupPins();

#endif
