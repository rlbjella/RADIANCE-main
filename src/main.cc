#include "microcontroller.h"
#include "framedata.h"

int main() {
  // Create object and start the system loop
  RADIANCE::Microcontroller raspberry_pi;
  raspberry_pi.Initialize();
  raspberry_pi.StartLoop();

}

