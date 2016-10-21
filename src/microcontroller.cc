#include <iostream>
#include <unistd.h>
#include "microcontroller.h"
#include "tmp102.h"

namespace RADIANCE {
    TMP102 tempSensor;
  Microcontroller::Microcontroller() {};
  Microcontroller::~Microcontroller() {};

  void Microcontroller::initialize() {

  }

  void Microcontroller::startLoop() {
    bool running = true;
    int frame=0;
    while (running) {

      // // Main system loop
      // readInputs();
      // processData();
      // writeOutputs();
      
      frame++;
      usleep(1000000);
    }
  }
}
