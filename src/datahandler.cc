#include "datahandler.h"
#include "microcontroller.h"
#include "../include/avaspec/avaspec.h"
#include <stdio.h>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <thread>

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
    DataHandler::ReadInternalTemperature();
    DataHandler::ReadExternalTemperature();
    DataHandler::ReadHumidity();
    DataHandler::ReadAttitude();

    // Take a picture every 60 frames
    // if (frame_counter==59) { DEBUG
    DataHandler::ReadCamera();
    // }
  }

  // Writes the frame data to a csv file
  void DataHandler::WriteMeasurementsToStorage(int frame_counter) {

    // Write sensor measurements
    FILE* open_file;
    // open_file = fopen("/mnt/FLASHDRIVE/datafile", "wb");
    open_file = fopen("datafile", "wb"); // DEBUG

    fwrite(frame_data.spectrum, sizeof(float), spectrometer_.GetNumPixels(), open_file);
    fwrite(frame_data.image, sizeof(float), camera_.GetImageSize(), open_file);
    fwrite(reinterpret_cast<char*>(&frame_data.upper_battery_temperature), sizeof(float), 1, open_file);
    fwrite(reinterpret_cast<char*>(&frame_data.lower_battery_temperature), sizeof(float), 1, open_file);
    fwrite(reinterpret_cast<char*>(&frame_data.storage_temperature), sizeof(float), 1, open_file);
    fwrite(reinterpret_cast<char*>(&frame_data.external_temperature), sizeof(float), 1, open_file);
    fwrite(reinterpret_cast<char*>(&frame_data.humidity), sizeof(float), 1, open_file);
    fwrite(reinterpret_cast<char*>(&frame_data.attitude), sizeof(float), 1, open_file);

    // Flush the buffers before writing and then close the buffer
    fflush(open_file);
    fclose(open_file);

  }

  // Reads spectrometer data into frame data
  void DataHandler::ReadSpectrum() {
    frame_data.spectrum = DataHandler::spectrometer_.ReadSpectrum();
  }

  // Reads engineering data into frame data
  void DataHandler::ReadInternalTemperature() {
    frame_data.upper_battery_temperature = upper_battery_temperature_sensor_.ReadTemperature();
    frame_data.lower_battery_temperature = lower_battery_temperature_sensor_.ReadTemperature();
    frame_data.storage_temperature = storage_temperature_sensor_.ReadTemperature();
  }

  //Reads a measurement from the external temperature sensor
  void DataHandler::ReadExternalTemperature() {
    frame_data.external_temperature = external_temperature_sensor_.ReadTemperature();
  }
  // Reads a measurement from the humidity sensor
  void DataHandler::ReadHumidity() {
    frame_data.humidity = humidity_sensor_.ReadHumidity();
  }

  // Takes a measurement from the attitude determination photodiodes
  void DataHandler::ReadAttitude() {
    frame_data.attitude = attitude_sensor_.ReadAttitude();
  }

  // Reads camera data into frame data
  void DataHandler::ReadCamera() {
    frame_data.image = camera_.ReadImage();
  }
 
}
