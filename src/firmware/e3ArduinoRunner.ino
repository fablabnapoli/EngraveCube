#include "e3Utils.h"
#include "EngraveCube.h"
#include "config.h"

EngraveCube e3 = EngraveCube();

void setup() {

  delay(500);

  // Inizializzo la comunicazione seriale
  Serial.begin(serialBoudRate);

  // Inizializzo i Pin
  setupPins();

  // Stampo un messaggio di benvenuto
  Serial.println("Engrave Cube V0.01");
}

void loop() {
  /* code */
  static char cmdBuffer[80];

  if (e3.isRunning()) {
    e3.run();
  } else if (readline(Serial.read(), cmdBuffer, 80) > 0) {
    Serial.print("<< ");
    Serial.println(cmdBuffer);

    Serial.print(">> ");
    Serial.println(e3.parse(cmdBuffer));
  }
}
