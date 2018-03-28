
#include "EngraveCube.h"
// #include <string>


EngraveCube::EngraveCube() {
  _stepperX = AccelStepper(AccelStepper::FULL4WIRE, s1_in1, s1_in2, s1_in3, s1_in4);
  _stepperY = AccelStepper(AccelStepper::FULL4WIRE, s2_in1, s2_in2, s2_in3, s2_in4);
}


boolean EngraveCube::isRunning() {
  if (_stepperX.isRunning() || _stepperY.isRunning() ) {
    return true;
  } else {
    return false;
  }

}

boolean EngraveCube::run() {
  _stepperX.run();
  _stepperY.run();
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
    return this->cmdG28(cmdBuffer);
  } else {
    return "Comando non valido"; // + pch + cmdBuffer;
  }

}

char* EngraveCube::cmdG0(char *cmdBuffer) {
  char* stepX
  while (pch != NULL) {
    printf ("%s\n",pch);
    pch = strtok (NULL, " ,.-");
  }
  return "Riconosciuto il comando G0";
}

char* EngraveCube::cmdG28(char *cmdBuffer){
  return "Riconosciuto il comando G28";
}
