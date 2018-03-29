#include "e3Utils.h"
#include "EngraveCube.h"
#include "config.h"
#include <SerialDebug.h>

#define DEBUG true
#define DEBUG_LEVEL NOTIFICATION


EngraveCube e3 = EngraveCube();
// SerialDebug debugger = SerialDebug();

void setup() {

  delay(500);

  // Inizializzo la comunicazione seriale


  Serial.begin(serialBoudRate);

  // Stampo un messaggio di benvenuto
  Serial.println("Engrave Cube V0.01");

  // Inizializzo i Pin
  setupPins();

}

void loop() {
  /* code */
  static char cmdBuffer[80];

  if (e3.isRunning()) {
    e3.run();
  } else if (readline(Serial.read(), cmdBuffer, 80) > 0) {
    Serial.print("<< ");
    Serial.println(cmdBuffer);
    // Serial.print(">> ");
    Serial.println(e3.parse(cmdBuffer));
  }
}
