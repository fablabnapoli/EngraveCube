
#include "EngraveCube.h"
// #include <string>


EngraveCube::EngraveCube() {

  // Inizializzo lo stepper X
  // Attenzione per il correttp punzionamento degli steppers la sequanza dei
  // pin da passare al costrutture deve essere:
  // PIN01  PIN03  PIN04
  _stepperX = AccelStepper(sx_Type, sx_in1, sx_in3, sx_in2, sx_in4);
  _stepperX.setMaxSpeed(defMaxSpeed);
  _stepperX.setCurrentPosition(0);

  // Inizializzo lo stepper Y
  // Attenzione per il correttp punzionamento degli steppers la sequanza dei
  // pin da passare al costrutture deve essere:
  // PIN01 PIN02 PIN03 PIN04
  _stepperY = AccelStepper(sy_Type, sy_in1, sy_in3, sy_in2, sy_in4);
  _stepperY.setMaxSpeed(defMaxSpeed);
  _stepperY.setCurrentPosition(0);

  // Imposto la velocità di movimento di default
  this->_speed = dflSpeed;

  // Imposto la modalità di calcolo dei movimenti.
  this->_positioning = dflPositioning;
}

boolean EngraveCube::isRunning() {
  // if (_stepperX.isRunning() || _stepperY.isRunning() ) {
  if (_stepperX.distanceToGo() || _stepperY.distanceToGo()) {
    return true;
  } else {
    return false;
  }

}

bool EngraveCube::setSpeed(float speed){

  if (speed < defMaxSpeed) {
    this->_speed = speed;
  } else {
    this->_speed = defMaxSpeed;
  }
  this->_stepperX.setSpeed(this->_speed);
  this->_stepperY.setSpeed(this->_speed);

}

bool EngraveCube::setAccel(float accel){

}

char* EngraveCube::parse(char cmdBuffer[], int cmdLng) {

  Serial.print("Debug: EngraveCube::parse - cmdLng:");
  Serial.println(cmdLng);
  Serial.print("Debug: EngraveCube::parse - cmdBuffer:");
  Serial.println(cmdBuffer);


  if (cmdLng >= 2 && cmdBuffer[0] == 'G') {
    /* Il comando fornito è un G-code*/

    char *outputTxt = "";

    // Salvo il comando e la sua lunghezza nelle var di stato
    this->_cmdBuffer = cmdBuffer;
    this->_cmdBufLng = cmdLng;

    // Recupero il numero del comando G-Code richiesto
    int codeNum = (int)strtod(&cmdBuffer[1], NULL);

    Serial.print("Debug: EngraveCube::parse - codeNum:");
    Serial.println(codeNum);

    switch(codeNum)
      {
        case 0: // Identificato il comando G0 - Movimento lineare rapido.
          outputTxt = this->cmdG0();
        break;
        case 28: // Identificato il comando G28 - Homing.
          outputTxt = this->cmdG28();
        break;
        case 90: // Identificato il comando G91 - Imposta pos. assoluto.
          outputTxt = this->cmdG90();
        break;
        case 91: // Identificato il comando G91 - Imposta pos. relativo.
          outputTxt = this->cmdG91();
        break;
        default:
          outputTxt = "Comando G-Code non implementato";
        break;
      }

        Serial.print("Debug: EngraveCube::parse - Posizione finale:");
        Serial.print(_stepperX.currentPosition());
        Serial.print(":");
        Serial.println(_stepperY.currentPosition());

        // Ripulisco il buffer di comando.
        // this->clearCmdBuf();
      return outputTxt;
  } else {
    return "Comando non valido.";
  }


}

void EngraveCube::goToXY(float x = NULL, float y = NULL, float speed = NULL){

  // Imposto la posizione X:Y di destinazione.
  if (x != NULL) {
    if (this->_positioning == RELATIVE )
      this->_stepperX.move(x);
    else if (this->_positioning == ABSOLUTE)
      this->_stepperX.moveTo(x);
  }

  if (y != NULL) {
    if (this->_positioning == RELATIVE )
      this->_stepperY.move(y);
    else if (this->_positioning == ABSOLUTE)
      this->_stepperY.moveTo(y);
  }

  // Imposto la velocità di movimento
  // La velocità non può essere > di dflMaxSpeed; il metodono
  // AccelStepper::setSpeed usa l'istruzione 'constrain' per vincolarla tra
  // +- dflMaxSpeed
  if (speed != NULL && speed > 0.0) {
    this->_speed = speed;
  }

  this->_stepperX.setSpeed(this->_speed);
  this->_stepperY.setSpeed(this->_speed);
}

void EngraveCube::runSpeed() {

  _stepperX.runSpeedToPosition();
  _stepperY.runSpeedToPosition();

}

boolean EngraveCube::getEndstopX() {
  return digitalRead(endStopX);
}

boolean EngraveCube::getEndstopY() {
  return digitalRead(endStopY);
}

boolean EngraveCube::getParamVal(char key, double* value){

  if (this->_cmdBuffer!= NULL && this->_cmdBufLng) {
    // Se è presente un comando valido.
    char *paramPointer;
    paramPointer = strchr(this->_cmdBuffer, key);

    if (paramPointer != NULL) // We found a key value
    {
      *value = (double)strtod(&this->_cmdBuffer[paramPointer - this->_cmdBuffer + 1], NULL);
      return true;
    }
  } else {
    return false;
  }
}

// Movimento lineare rapido
// Not all parameters need to be used, but at least one has to be used
// Xnnn The position to move to on the X axis
// Ynnn The position to move to on the Y axis
// Pnnn The amount to extrude between the starting point and ending point
// Fnnn The feedrate per minute of the move between the starting point and ending point (if supplied)
// Snnn Flag to check if an endstop was hit (S1 to check, S0 to ignore, S2 see note, default is S0)1
char* EngraveCube::cmdG0() {
  double xVal = NULL; // Coordinata X
  double yVal = NULL; // Coordinata Y
  double eVal = NULL; // Intensità del laser
  double fdVal = NULL; // velocità di movimento

  this->getParamVal('X', &xVal);
  this->getParamVal('Y', &yVal);

  if ( xVal || yVal ) {
    // Se è stato indicato uno spostamento da percorrere in X o Y
    Serial.print("Debug: EngraveCube::cmdG0 - xVal:");
    Serial.println(xVal);

    Serial.print("Debug: EngraveCube::cmdG0 - yVal:");
    Serial.println(yVal);

    // Recupero il valore dell'intensità del laser richiesta (se fornita)
    // Se non fornita il valore di default sarà 0
    if (this->getParamVal('E', &eVal)) {
      Serial.print("Debug: EngraveCube::cmdG0 - eVal:");
      Serial.println(eVal);

      // this->setLaserPwr((int)eVal);
    }

    // Recupero il valore della velocità di movimento (se fornita)
    this->getParamVal('F', &fdVal);

    // Imposto lo spostamento e la velocità
    this->goToXY(xVal, yVal, fdVal);

    // while (_stepperX.distanceToGo() || _stepperY.distanceToGo()) {
    while (this->isRunning()) {
      this->runSpeed();
    }

    // Spengo il laser (se acceso) appena completato il movimento.
    // this-setLaserPwr(0);

    return ">> G0 [OK].";

  } else {
    return ">> G0 [KO] Parametri insufficienti.";
  }

}

// Homing
char* EngraveCube::cmdG28(){

  // Comando una rotazione completa di entrambi i motori
  // Il punto di arresto (home) arriverà sicuramente prima di una
  // rotazione completa e sarà determinato dagli endstops
  this->goToXY(-1*sx_Dir*sx_sFullRot, -1*sy_Dir*sy_sFullRot, defMaxSpeed);

  Serial.print("Destination:");
  Serial.print(_stepperX.targetPosition());
  Serial.print(":");
  Serial.println(_stepperY.targetPosition());

  Serial.print("Speed:");
  Serial.print(_stepperX.speed());
  Serial.print(":");
  Serial.println(_stepperY.speed());
  Serial.println("--------------------");

  while (this->getEndstopX() || this->getEndstopY()){
    this->runSpeed();
  }


  _stepperX.setCurrentPosition(0);
  _stepperY.setCurrentPosition(0);

  this->goToXY(sx_Dir*zeroPartX, sy_Dir*zeroPartY, defMaxSpeed);

  Serial.print("Destination:");
  Serial.print(_stepperX.targetPosition());
  Serial.print(":");
  Serial.println(_stepperY.targetPosition());

  Serial.print("Speed:");
  Serial.print(_stepperX.speed());
  Serial.print(":");
  Serial.println(_stepperY.speed());
  Serial.println("--------------------");

  while (_stepperX.distanceToGo() || _stepperY.distanceToGo()){
    this->runSpeed();

    // Serial.print("Current Position:");
    // Serial.print(_stepperX.currentPosition());
    // Serial.print(":");
    // Serial.println(_stepperY.currentPosition());
  }

  _stepperX.setCurrentPosition(0);
  _stepperY.setCurrentPosition(0);

  return ">> G28 [OK]";
}

  // G90: Imposta posizionamento assoluto.
char* EngraveCube::cmdG90(){
  this->_positioning = ABSOLUTE;
  return ">> G90 [OK] - Absolute positioning.";
}

// G91: Imposta posizionamento relativo.
char* EngraveCube::cmdG91(){
  this->_positioning = RELATIVE;
  return ">> G91 [OK] - Relative positioning.";
}
