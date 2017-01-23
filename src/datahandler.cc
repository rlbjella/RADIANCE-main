#include "datahandler.h"
#include "microcontroller.h"
#include "../include/avaspec/avaspec.h"
#include <stdio.h>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <thread>

namespace RADIANCE {
  // Setup and configure each sensor
  void DataHandler::Initialize() {
    spectrometer_.Initialize();
    humidity_sensor_.Initialize();
    upper_battery_temperature_sensor_.Initialize()
    lower_battery_temperature_sensor_.Initialize()
    external_temperature_sensor_.Initialize()  
    attitude_sensor_.Initialize()
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
  // Inputs: 
  // frame_counter: Used to determine a picture needs to be written
  void DataHandler::WriteMeasurementsToStorage(int frame_counter) {

    // Open file object and binary write to it
    // C file utilities is used for speed
    FILE* data_file;

    // data_file = fopen("/mnt/FLASHDRIVE/datafile", "wb");
    data_file = fopen("datafile", "ab"); // DEBUG

    // Write the data
    fwrite(frame_data.spectrum, sizeof(float), spectrometer_.GetNumPixels(), data_file);
    fwrite(reinterpret_cast<char*>(&frame_data.upper_battery_temperature), sizeof(float), 1, data_file);
    fwrite(reinterpret_cast<char*>(&frame_data.lower_battery_temperature), sizeof(float), 1, data_file);
    fwrite(reinterpret_cast<char*>(&frame_data.storage_temperature), sizeof(float), 1, data_file);
    fwrite(reinterpret_cast<char*>(&frame_data.external_temperature), sizeof(float), 1, data_file);
    fwrite(reinterpret_cast<char*>(&frame_data.humidity), sizeof(float), 1, data_file);
    fwrite(reinterpret_cast<char*>(&frame_data.attitude), sizeof(float), 1, data_file);

    // Flush the buffers before writing and then close the buffer
    fflush(data_file);
    fclose(data_file);

    // TODO: Update with multiple flash drive
    // Write image measurements
    FILE* image_file;
    // image_file = fopen("/mnt/FLASHDRIVE/imagefile", "wb");
    image_file = fopen("imagefile", "ab"); // DEBUG
    fwrite(frame_data.image, sizeof(float), camera_.GetImageSize(), image_file);

    // Flush the buffers before writing and then close the buffer
    fflush(image_file);
    fclose(image_file);

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

  // Reads a measurement from the external temperature sensor
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
