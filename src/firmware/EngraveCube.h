
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

    // typedef enum name {
    //   DIR_CW = 1,
    //   DIR_CCW = -1
    // } DIRECTION;

    // Nomi simbolici per le modalità di calcolo dei movimenti.
    // ABSOLUTE: i comandi di movimento saranno interpretati in maniera maniera
    //           assoluta (rispetto all'origine degli assi).
    // RELATIVE: i comandi di movimento saranno interpretati in maniera maniera
    //           relativa (rispetto alla posizione attuale).
    typedef enum {
      ABSOLUTE = 1,
      RELATIVE = 0
    } positioningMode;

    EngraveCube();

    char* parse(char cmdBuffer[], int cmdLng);

    boolean isRunning();

    void run();

  private:

    void EngraveCube::goToXY(float x, float y, float speed = NULL);

    bool EngraveCube::setSpeed(float speed);

    bool EngraveCube::setAccel(float accel);

    bool EngraveCube::setLaserPwr(int lsrPwr);

    void EngraveCube::runSpeed();

    boolean getEndstopX();

    boolean getEndstopY();

    // Recupera il valore di un parametro G-Code se specificato nel comando
    // Es. Per il comando 'G0 X100 Y200' la chiamata getParamVal('X', valX)
    // Restituisce TRUE ed imposta valX a 100.0
    boolean getParamVal(char key, double* value);

    /*===========================================================
                            Comandi G-Code implementati.
    =============================================================*/

    // G0: Movimento lineare rapido
    char* EngraveCube::cmdG0();

    // G28: Homing
    char* EngraveCube::cmdG28();

    // G90: Imposta posizionamento assoluto.
    char* EngraveCube::cmdG90();

    // G91: Imposta posizionamento relativo.
    char* EngraveCube::cmdG91();


    /*===========================================================
                              Variabili di stato.
    =============================================================*/

    // Posizione in steps dello stepper X
    AccelStepper _stepperX;

    // Posizione in steps dello stepper Y
    AccelStepper _stepperY;

    // Ultima velocità impostata
    float _speed;

    // Ultimo comando
    char *_cmdBuffer;

    // Lunghezza (in caratteri) del comando in elaborazione.
    int _cmdBufLng;

    // Modalità di calcolo dei movimenti (ABSOLUTE/Relative).
    bool _positioning;

};
