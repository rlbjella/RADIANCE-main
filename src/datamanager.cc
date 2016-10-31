#include "datamanager.h"
#include "microcontroller.h"
#include <iostream>

namespace RADIANCE {
  DataManager::DataManager() {}
  DataManager::~DataManager() {}

  // Reads a measurement from each sensor and places it into the
  // science data struct.
  // Inputs: 
  // frame_counter: Used to determine whether a picture is needed
  void DataManager::ReadSensorData(int frame_counter) {
    // Spectrometer is the most important so measure first
    DataManager::ReadSpectrometer();

    // Read housekeeping(engineering) sensors
    DataManager::ReadExternalTemperature();
    DataManager::ReadHumidity();
    DataManager::ReadPressure();
    DataManager::ReadInternalTemperature();
    DataManager::ReadAttitude();

    // Take a picture every 60 frames
    if (frame_counter==59) {
        DataManager::ReadCamera();
      }

  }

  // Returns measured internal temperature
  int DataManager::GetInternalTemperature() {
    return frame_data_.internal_temperature;
  }

  // Writes the frame data to a csv file
  void DataManager::WriteMeasurementsToStorage(int frame_counter) {
    //TODO(James): Replace with storage write algorithm

  }

  // Reads spectrometer data into frame data
  void DataManager::ReadSpectrometer() {}

  // Reads engineering data into frame data
  void DataManager::ReadInternalTemperature() {}
  void DataManager::ReadExternalTemperature() {}
  void DataManager::ReadHumidity() {}
  void DataManager::ReadPressure() {}
  void DataManager::ReadAttitude() {}

  // Reads camera data into frame data
  void DataManager::ReadCamera() {}
 
}
