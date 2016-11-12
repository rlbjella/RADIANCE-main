#include "datahandler.h"
#include "microcontroller.h"
#include "spectrometer.h"
#include "../include/avaspec/avaspec.h"
#include <stdio.h>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <thread>
#include "camera.h"

namespace RADIANCE {
  DataHandler::DataHandler() {}
  DataHandler::~DataHandler() {}

  // Setup and configure sensors
  void DataHandler::Initialize() {

    spectrometer_.Initialize();
    camera_.Initialize();
  }

  // Reads a measurement from each sensor and places it into the
  // science data struct.
  // Inputs: 
  // frame_counter: Used to determine whether a picture is needed
  void DataHandler::ReadSensorData(int frame_counter) {
    
    // Spectrometer is the most important so measure first
    DataHandler::ReadSpectrum();

    // Read housekeeping(engineering) sensors
    DataHandler::ReadExternalTemperature();
    DataHandler::ReadHumidity();
    DataHandler::ReadPressure();
    DataHandler::ReadInternalTemperature();
    DataHandler::ReadAttitude();

    // Take a picture every 60 frames
    //DEBUG
    // if (frame_counter==59) {
    DataHandler::ReadCamera();
    // }
  }

  // Writes the frame data to a csv file
  void DataHandler::WriteMeasurementsToStorage(int frame_counter) {
    
    //TODO(James): Replace with storage write algorithm
    int num_pixels = 3648;

    std::ofstream csv_file;

    csv_file.open("/mnt/FLASHDRIVE/file.csv", std::ofstream::app);
    for (int i=0; i < num_pixels-1;i++) {
      csv_file << frame_data.spectrum[i];
      if (i != num_pixels-1) {
          csv_file << ",";
        }
     }
    csv_file << std::endl;
    csv_file << std::flush;
    
    csv_file.close();
  }

  // Reads spectrometer data into frame data
  void DataHandler::ReadSpectrum() {
    frame_data.spectrum = DataHandler::spectrometer_.ReadSpectrum();

  }

  // Reads engineering data into frame data
  void DataHandler::ReadInternalTemperature() {}
  void DataHandler::ReadExternalTemperature() {}
  void DataHandler::ReadHumidity() {}
  void DataHandler::ReadPressure() {}
  void DataHandler::ReadAttitude() {}

  // Reads camera data into frame data
  void DataHandler::ReadCamera() {
    
    camera_.ReadImage();
  }
 
}
