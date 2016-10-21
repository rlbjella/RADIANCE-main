#include "microcontroller.h"

int main() {
  // Create object
  RADIANCE::Microcontroller RPi;
  // Initialize instruments
  RPi.initialize();
  // Run system loop
  RPi.startLoop();
    
}

