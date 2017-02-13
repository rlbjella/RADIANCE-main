#include <math.h>
#include <chrono>
#include <iostream>
#include <thread>
#include <stdexcept>
#include "microcontroller.h"
#include "datahandler.h"
#include "controls/heatercontrol.h"

namespace RADIANCE {

  // Setup and configure sensors by calling Data Handler instance
  void Microcontroller::Initialize() {
    data_handler_.Initialize();
  }

  // Steps one frame. Resets if frame counter is zero
  // frame_counter should always be between 0 and 60
  void Microcontroller::UpdateFrameCounter() {

    if (Microcontroller::frame_counter<59) {
      Microcontroller::frame_counter++;
    } else if (Microcontroller::frame_counter==59) {
      Microcontroller::frame_counter = 0;
    } else {
      // This should never happen
      throw std::out_of_range("frame_counter out of range");;
    }

  }

  // Sets heater output based on the information in frame_data
  void Microcontroller::SetThermalControl(DataHandler::frame_data_type frame_data) {

    // Spectrometer heating
    if (frame_data.spectrometer_temperature <= 1 && !spectrometer_heater_.IsHeaterOn()){
      spectrometer_heater_.CommandHeaterOn();
    } else if (frame_data.spectrometer_temperature >= 3 && spectrometer_heater_.IsHeaterOn()) {
      spectrometer_heater_.CommandHeaterOff();
    }

    // Battery heating
    // First average the two battery temperatures
    float avg_battery_temperature = (frame_data.upper_battery_temperature + frame_data.lower_battery_temperature)/2;
    if (avg_battery_temperature <= 1 && !battery_heater_.IsHeaterOn()){
      battery_heater_.CommandHeaterOff();
    } else if (avg_battery_temperature >= 3 && battery_heater_.IsHeaterOn()) {
      battery_heater_.CommandHeaterOn();
    }

  }

  // Start the system (infinite) loop 
  // System process is the following: Read -> Write -> Sleep; time
  // taken is also calculated
  void Microcontroller::StartLoop() {

    // System loop
    while (true) {

      //DEBUG 
      std::chrono::high_resolution_clock::time_point begin,end;
      begin = std::chrono::high_resolution_clock::now();

      // Main system loop
      data_handler_.ReadSensorData(Microcontroller::frame_counter);

      // Update the heater output
      Microcontroller::SetThermalControl(data_handler_.GetFrameData());

      // Write processed data to storage
      data_handler_.WriteFrameToStorage(Microcontroller::frame_counter);

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
        std::cout << "Could not finish in 1 second" << std::endl; // DEBUG
      }


    }
  }
}
