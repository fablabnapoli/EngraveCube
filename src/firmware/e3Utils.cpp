#include "e3Utils.h"

int readline(int readch, char *buffer, int len)
{
  static int pos = 0;
  int rpos;

  if (readch > 0) {
    switch (readch) {
      case '\n': // Ignore new-lines
        break;
      case '\r': // Return on CR
        rpos = pos;
        pos = 0;  // Reset position index ready for next time
        return rpos;
      default:
        if (pos < len-1) {
          buffer[pos++] = readch;
          buffer[pos] = 0;
        }
    }
  }
  // No end of line has been found, so return -1.
  return -1;
}

void setupPins() {
  // Imposto il pin di controllo del laser
  pinMode(laserPin, OUTPUT);
  // Forzo ad OFF il laser
  digitalWrite(laserPin, LOW);

  pinMode(resetPin, INPUT);

  // Imposto il pin di controllo dell'end stop X
  // L'ednstop restituisce LOW/0 quado chiuso e HIGH/1 quando aperto
  // Usando la resistenza di PULLUP non è richiesta una resistenza fisica
  // esterna.
  pinMode(endStopX, INPUT_PULLUP);

  // Imposto il pin di controllo del'end stop Y
  // L'ednstop restituisce LOW/0 quado chiuso e HIGH/1 quando aperto
  // Usando la resistenza di PULLUP non è richiesta una resistenza fisica
  // esterna.
  pinMode(endStopY, INPUT_PULLUP);
}
