#include "microcontroller.h"
#include "datahandler.h"
#include <chrono>
#include <thread>

namespace RADIANCE {
  Microcontroller::Microcontroller() {}
  Microcontroller::~Microcontroller() {}

  // Setup and configure sensors
  void Microcontroller::Initialize() {
    // TODO(James): Setup sensors
  }

  // Steps one frame
  void Microcontroller::UpdateFrameCounter() {

    if (Microcontroller::frame_counter_==59) {
      Microcontroller::frame_counter_ = 0;
    } else {
      Microcontroller::frame_counter_++;
    }

  }

  // Changes the heater voltage according to the following table:
  // T < T_min -> Set maximum heater voltage
  // T_Min < T < T_Max -> Set heater voltage based on a TBD algorithm
  // T > T_max -> Set maximum heater voltage
  void Microcontroller::UpdateHeaterVoltage() {
    int internal_temperature = data_handler_.GetInternalTemperature();

    // TODO(James): Find a better way to store these minimums/maximums
    int minimum_temperature = 200;
    int maximum_temperature = 280;

    if (internal_temperature <= minimum_temperature) {
      // Payload is under survival temperature, turn heating to maximum
      // heater_.SetVoltage(5);

    } else if(internal_temperature > minimum_temperature
              && internal_temperature < maximum_temperature) {
      // Payload is between minimum and maximum temperature,
      // determine heater voltage and then set

      //TODO(James): Replace with heating algorithm
      // heater_.SetVoltage(3);

    } else if (internal_temperature >= maximum_temperature) {
      // Payload is over maximum temperature
      // heater_.SetVoltage(0);

    } else  {
      throw "Internal temperature not defined";
    }

  }
  // Start the system (infinite) loop 
  // General flow: Read -> Process -> Write -> Sleep;
  void Microcontroller::StartLoop() {

    // System loop
    while (true) {

      // Main system loop
      data_handler_.ReadSensorData(Microcontroller::frame_counter_);

      // Run the thermal heating algorithm
      UpdateHeaterVoltage();
      
      // Write processed data to storage
      data_handler_.WriteMeasurementsToStorage(Microcontroller::frame_counter_);

      // Step one frame
      UpdateFrameCounter();

      // Sleep for one second
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
  }
}
