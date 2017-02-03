#include <stdio.h>
#include <sys/types.h>
#include <thread>
#include "../include/avaspec/avaspec.h"
#include "datahandler.h"
#include "microcontroller.h"
#include "controls/heatercontrol.h"

namespace RADIANCE {

  void DataHandler::Initialize() {

    // Setup and configure each sensor
    spectrometer_.Initialize();
    humidity_sensor_.Initialize();
    // rpi_temperature_sensor_.Initialize(); // RPi temperature sensor does no require initialization
    upper_battery_temperature_sensor_.Initialize();
    lower_battery_temperature_sensor_.Initialize();
    external_temperature_sensor_.Initialize();
    attitude_sensor_.Initialize();
    camera_.Initialize();

    // Setup and configure measurement storage
    // Open file objects in binary append mode
    // C file utilities are used for performance
    slc_data_file = fopen("datafile", "ab"); // DEBUG 
    // slc_data_file = fopen("/mnt/slcdrive/datafile", "ab");
    // mlc1_data_file = fopen("/mnt/mlcdrive1/datafile", "ab");
    // mlc2_data_file = fopen("/mnt/mlcdrive2/datafile", "ab");

    mlc1_image_file = fopen("imagefile", "ab"); //DEBUG
    // mlc1_image_file = fopen("/mnt/mlcdrive1/imagefile", "ab");
    // mlc2_image_file = fopen("/mnt/mlcdrive2/imagefile", "ab");

  }

  // Reads a measurement from each sensor and places it into the
  // science data struct.
  // Inputs: 
  // frame_counter: Used to determine whether a picture is needed
  void DataHandler::ReadSensorData(const int frame_counter) {
    
    // Spectrometer is the most important so measure first
    DataHandler::ReadSpectrum();

    // Read housekeeping(engineering) sensors
    DataHandler::ReadSpectrometerTemperature();
    DataHandler::ReadRPiTemperature();
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
  void DataHandler::WriteFrameToStorage(const int frame_counter) {

    // Writes the data(measurements) to all three drives every second
    WriteDataToFile(slc_data_file);
    // WriteDataToFile(&mlc1_data_file); // DEBUG
    // WriteDataToFile(&mlc2_data_file); // DEBUG

    // Write an image to just the MLC drives every minute
    // if (frame_counter==59) {
    WriteImagesToFile(mlc1_image_file);
    // WriteImagesToFile(&mlc2_image_file); // DEBUG
    // }
  }

  // Gets the frame_data struct for other routines
  DataHandler::frame_data_type DataHandler::GetFrameData() {return frame_data;}

  // Writes the frame data to the given file
  // Inputs:
  // file: The C file object to write to
  void DataHandler::WriteDataToFile(FILE* file) {

    // Write the engineering/housekeeping measurements to the given file
    fwrite(frame_data.spectrum, sizeof(float), spectrometer_.GetNumPixels(), file);
    fwrite(reinterpret_cast<char*>(&frame_data.spectrometer_temperature), sizeof(float), 1, file);
    fwrite(reinterpret_cast<char*>(&frame_data.rpi_temperature), sizeof(float), 1, file);
    fwrite(reinterpret_cast<char*>(&frame_data.upper_battery_temperature), sizeof(float), 1, file);
    fwrite(reinterpret_cast<char*>(&frame_data.lower_battery_temperature), sizeof(float), 1, file);
    fwrite(reinterpret_cast<char*>(&frame_data.storage_temperature), sizeof(float), 1, file);
    fwrite(reinterpret_cast<char*>(&frame_data.external_temperature), sizeof(float), 1, file);
    fwrite(reinterpret_cast<char*>(&frame_data.humidity), sizeof(float), 1, file);
    fwrite(reinterpret_cast<char*>(&frame_data.attitude), sizeof(float), 1, file);

    // Flush the buffers after each write
    fflush(file);
  }


  // Writes the images to the given file
  // Inputs: 
  // file: The C file object to write to
  void DataHandler::WriteImagesToFile(FILE* file) {

    // Write image to the given file
    fwrite(frame_data.image, sizeof(float), camera_.GetImageSize(), file);

    // Flush the buffers after each write
    fflush(file);
  }

  // Reads spectrometer data into frame data
  void DataHandler::ReadSpectrum() {
    frame_data.spectrum = DataHandler::spectrometer_.ReadSpectrum();
  }

  // Reads spectrometer temperature into frame data
  void DataHandler::ReadSpectrometerTemperature() {
    frame_data.spectrometer_temperature = DataHandler::spectrometer_.ReadSpectrometerTemperature();
  }

  // Reads RPi internal temperature sensor into frame data
  void DataHandler::ReadRPiTemperature() {
    frame_data.rpi_temperature = rpi_temperature_sensor_.ReadTemperature();

  }
  // Reads all internal temperature sensors into the float data
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
