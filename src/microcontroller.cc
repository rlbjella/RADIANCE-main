#include "microcontroller.h"
#include "datahandler.h"
#include <chrono>
#include <iostream>
#include <thread>

namespace RADIANCE {
  Microcontroller::Microcontroller() {}
  Microcontroller::~Microcontroller() {}

  // Setup and configure sensors
  void Microcontroller::Initialize() {
    //DEBUG
    std::cout << "Initializing" << std::endl;
    data_handler_.Initialize();
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

      //DEBUG 
      std::chrono::high_resolution_clock::time_point begin,end;
      begin = std::chrono::high_resolution_clock::now();

      // Main system loop
      data_handler_.ReadSensorData(Microcontroller::frame_counter);
      
      // Write processed data to storage
      data_handler_.WriteMeasurementsToStorage(Microcontroller::frame_counter);

      // Step one frame
      UpdateFrameCounter();

      // Calculate time taken
      end = std::chrono::high_resolution_clock::now();

      std::chrono::duration<float> fs = end - begin;
      std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(fs);
      std::cout << "Milliseconds taken: " << ms.count() << std::endl;

      // Sleep, if necessary
      if (ms < std::chrono::milliseconds(1000)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)-ms);
      } else{
        std::cout << "Could not finish in 1 second" << std::endl;
      }


    }
  }
}
