#include <pigpio.h>
#include "microcontroller.h"

int main() {
  // Initialize GPIO library (spelled Initialise rather than Initialize)
  gpioInitialise();

  // Create object and start the system loop
  RADIANCE::Microcontroller raspberry_pi;
  raspberry_pi.StartLoop();

}

