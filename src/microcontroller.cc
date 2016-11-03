#include "microcontroller.h"
#include "datahandler.h"
#include <chrono>
#include <thread>

namespace RADIANCE {
  Microcontroller::Microcontroller() {}
  Microcontroller::~Microcontroller() {}

  // Setup and configure sensors
  void Microcontroller::Initialize() {
    data_handler_.Initialize();
    // TODO(James): Setup sensors
  }

  // Steps one frame
  void Microcontroller::UpdateFrameCounter() {

    if (Microcontroller::frame_counter==59) {
      Microcontroller::frame_counter = 0;
    } else {
      Microcontroller::frame_counter++;
    }

  }

  // Start the system (infinite) loop 
  // General flow: Read -> Write -> Sleep;
  void Microcontroller::StartLoop() {

    // System loop
    while (true) {

      // Main system loop
      data_handler_.ReadSensorData(Microcontroller::frame_counter);
      
      // Write processed data to storage
      data_handler_.WriteMeasurementsToStorage(Microcontroller::frame_counter);

      // Step one frame
      UpdateFrameCounter();

      // Sleep for one second
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
  }
}
