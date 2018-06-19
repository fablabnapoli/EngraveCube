#include "e3Utils.h"
#include "EngraveCube.h"
#include "config.h"


EngraveCube e3 = EngraveCube();

void setup() {
  delay(1000);

  // Inizializzo la comunicazione seriale
  Serial.begin(serialBoudRate);

  // Stampo un messaggio di benvenuto
  Serial.println("Engrave Cube V0.01");

  // Inizializzo i Pin
  setupPins();

}

void loop() {
  /* code */
  char cmdBuffer[80];

  int cmdLng = readline(Serial.read(), cmdBuffer, 80);

  if ( cmdLng > 0) {
    Serial.print("<< ");
    Serial.println(cmdBuffer);
    // Serial.print(">> ");
    Serial.println(e3.parse(cmdBuffer, cmdLng));
  }
}
