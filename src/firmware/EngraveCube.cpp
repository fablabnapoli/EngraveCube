
#include "EngraveCube.h"
// #include <string>


EngraveCube::EngraveCube() {

  // Inizializzo lo stepper X
  _stepperX = AccelStepper(sx_Type, sx_in1, sx_in2, sx_in3, sx_in4);
  _stepperX.setMaxSpeed(sx_MaxSpeed);
  _stepperX.setAcceleration(sx_Accel);

// Inizializzo lo stepper Y
  _stepperY = AccelStepper(sy_Type, sy_in1, sy_in2, sy_in3, sy_in4);
  _stepperY.setMaxSpeed(sy_MaxSpeed);
  _stepperY.setAcceleration(sy_Accel);
}


boolean EngraveCube::isRunning() {
  if (_stepperX.isRunning() || _stepperY.isRunning() ) {
    return true;
  } else {
    return false;
  }

}

void EngraveCube::run() {
  _stepperX.run();
  _stepperY.run();
}

void EngraveCube::runSpeed() {
  _stepperX.runSpeed();
  _stepperY.runSpeed();
}


char* EngraveCube::parse(char *cmdBuffer) {
  char *pch;
  // std::string pch2 ="";

  // Serial.print("Hai digitato: >");
  // Serial.print(cmdBuffer);
  // Serial.println("<");

  pch = strtok (cmdBuffer," ");

  // Serial.print("Il comando è: >");
  // Serial.print(pch);
  // Serial.println("<");

  if (strcmp(pch, "G0") == 0) {
    return this->cmdG0(cmdBuffer);
  } else if (strcmp(pch, "G28") == 0) {
    return this->cmdG28();
  } else {
    return "Comando non valido"; // + pch + cmdBuffer;
  }

}

boolean EngraveCube::getEndstopX() {
  return digitalRead(endStopX);
}

boolean EngraveCube::getEndstopY() {
  return digitalRead(endStopY);
}

char* EngraveCube::cmdG0(char *cmdBuffer) {
  char* stepX;
  // while (pch != NULL) {
  //   printf ("%s\n",pch);
  //   pch = strtok (NULL, " ,.-");
  // }
  return ">> G0 [OK]";
}

char* EngraveCube::cmdG28(){

  _stepperX.setSpeed(sx_MaxSpeed);
  _stepperY.setSpeed(sy_MaxSpeed);

  _stepperX.move(-1*sx_Dir*sx_sFullRot);
  _stepperY.move(-1*sy_Dir*sy_sFullRot);

  while (this->getEndstopX() || this->getEndstopY()){
    this->run();
  }

  _stepperX.move(sx_Dir*zeroPartX);
  _stepperY.move(sy_Dir*zeroPartY);

  while (_stepperX.isRunning() || _stepperY.isRunning()){
    this->run();
    // this->runSpeed();
  }

  _stepperX.setCurrentPosition(0);
  _stepperY.setCurrentPosition(0);

  return ">> G28 [OK]";
}
