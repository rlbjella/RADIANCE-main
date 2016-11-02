#include "datahandler.h"
#include "microcontroller.h"
#include <iostream>

namespace RADIANCE {
  DataHandler::DataHandler() {}
  DataHandler::~DataHandler() {}

  // Reads a measurement from each sensor and places it into the
  // science data struct.
  // Inputs: 
  // frame_counter: Used to determine whether a picture is needed
  void DataHandler::ReadSensorData(int frame_counter) {
    // Spectrometer is the most important so measure first
    DataHandler::ReadSpectrometer();

    // Read housekeeping(engineering) sensors
    DataHandler::ReadExternalTemperature();
    DataHandler::ReadHumidity();
    DataHandler::ReadPressure();
    DataHandler::ReadInternalTemperature();
    DataHandler::ReadAttitude();

    // Take a picture every 60 frames
    if (frame_counter==59) {
        DataHandler::ReadCamera();
      }

  }

  // Returns measured internal temperature
  int DataHandler::GetInternalTemperature() {
    return frame_data_.internal_temperature;
  }

  // Writes the frame data to a csv file
  void DataHandler::WriteMeasurementsToStorage(int frame_counter) {
    //TODO(James): Replace with storage write algorithm

  }

  // Reads spectrometer data into frame data
  void DataHandler::ReadSpectrometer() {}

  // Reads engineering data into frame data
  void DataHandler::ReadInternalTemperature() {}
  void DataHandler::ReadExternalTemperature() {}
  void DataHandler::ReadHumidity() {}
  void DataHandler::ReadPressure() {}
  void DataHandler::ReadAttitude() {}

  // Reads camera data into frame data
  void DataHandler::ReadCamera() {}
 
}
