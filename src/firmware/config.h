
#define serialBoudRate 9600

// ===================== Coordinate di riferimento =======================

// Coordinata X dello "zero pezzo"
#define zeroPartX 815

// Coordinata Y dello "zero pezzo"
#define zeroPartY 900

// =================== Configurazione stepper motor X ====================

// Tipo stepper X
#define sx_Type AccelStepper::HALF4WIRE
// #define sx_Type AccelStepper::FULL4WIRE

// Pins Stepper X
#define sx_in1 2
#define sx_in2 3
#define sx_in3 4
#define sx_in4 5

// Direzione di rotazione positiva dello stepper. Può essere:
// - Oraria -> EngraveCube::DIR_CW
// - Antioraria -> EngraveCube::DIR_CCW
// #define sx_Dir EngraveCube::DIR_CW
#define sx_Dir -1

// Passi necessari ad una rotazione completa dello stepper
#define sx_sFullRot 5000

// =================== Configurazione stepper motor Y ====================

// Tipo stepper Y
#define sy_Type AccelStepper::HALF4WIRE
// #define sy_Type AccelStepper::FULL4WIRE

// Pins Stepper Y
#define sy_in1 6
#define sy_in2 7
#define sy_in3 8
#define sy_in4 9

// Direzione di rotazione positiva dello stepper. Può essere:
// - Oraria -> EngraveCube::DIR_CW
// - Antioraria -> EngraveCube::DIR_CCW
// #define sy_Dir EngraveCube::DIR_CW
#define sy_Dir 1

// Passi necessari ad una rotazione completa dello stepper
#define sy_sFullRot 5000

// ======== Configurazione Velocità/accelerazioni di default ===============
// E' la massima velocità (step/s) ammessa dall'elettronica/meccanica della E^3
#define defMaxSpeed 800.0
// E' la massima accelerazione ammessa dall'elettronica/meccanicadella E^3
#define defMaxAccel 500.0
// Velocità di rotazione di default
#define dflSpeed 300.0

// Modalità di calcolo dei movimenti.
#define dflPositioning ABSOLUTE


// =================== Configurazione Endstops ===========================

// Pin endsto Asse X
#define endStopX 11

// Pin endsto Asse Y
#define endStopY 13


// =================== Configurazione Laser ==============================
// Pin controllo laser
#define laserPin 12

// ================ Configurazione Reset/allert ==========================

// Pin per il reset della macchina
#define resetPin 14
