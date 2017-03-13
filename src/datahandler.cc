#include <stdio.h>
#include <sys/types.h>
#include <chrono>
#include <typeinfo>
#include <iostream>
#include <thread>
#include "../include/avaspec/avaspec.h"
#include "systemhaltexception.h"
#include "datahandler.h"
#include "microcontroller.h"
#include "controls/heatercontrol.h"

namespace RADIANCE {

  DataHandler::DataHandler() {

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

    // Read timestamp measurement
    // This timestamp represents seconds since Unix epoch
    std::chrono::seconds ms = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch());
    frame_data.time_stamp = ms.count();

    // Read main instrument(spectrometer)
    // frame_data.spectrum = spectrometer_.ReadSpectrum();

    // Read housekeeping(engineering) sensors
    // frame_data.spectrometer_temperature = spectrometer_.ReadSpectrometerTemperature(); DEBUG
    frame_data.rpi_temperature = rpi_temperature_sensor_.ReadTemperature();
    // frame_data.upper_battery_temperature = upper_battery_temperature_sensor_.ReadTemperature();
    // frame_data.lower_battery_temperature = lower_battery_temperature_sensor_.ReadTemperature();
    // frame_data.storage_temperature = storage_temperature_sensor_.ReadTemperature();
    // frame_data.external_temperature = external_temperature_sensor_.ReadTemperature();
    // frame_data.humidity = humidity_sensor_.ReadHumidity();
    // frame_data.attitude = attitude_sensor_.ReadAttitude();

    // Take a picture every 60 frames
    // if (frame_counter==59) { DEBUG
    // frame_data.image = camera_.ReadImage();
    std::cout << "Timestamp: " << frame_data.time_stamp << "; ";
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
    // WriteImagesToFile(mlc1_image_file);
    // WriteImagesToFile(&mlc2_image_file); // DEBUG
    // }
  }

  // Gets the frame_data struct for other routines
  DataHandler::frame_data_type DataHandler::GetFrameData() {return frame_data;}

  // Writes the frame data to the given file
  // Inputs:
  // file: The C file object to write to
  void DataHandler::WriteDataToFile(FILE* file) {
    // Null pointer check
    if (!file) {
      throw SystemHaltException();
    }

    // Write timestamp of measurement
    fwrite(&frame_data.time_stamp, sizeof(unsigned int), 1, file);

    // Write the engineering/housekeeping measurements to the given file
    // fwrite(frame_data.spectrum, sizeof(float), spectrometer_.GetNumPixels(), file);//DEBUG
    // fwrite(&frame_data.spectrometer_temperature, sizeof(float), 1, file);//DEBUG
    fwrite(&frame_data.rpi_temperature, sizeof(float), 1, file);
    // fwrite(&frame_data.upper_battery_temperature, sizeof(float), 1, file);
    // fwrite(&frame_data.lower_battery_temperature, sizeof(float), 1, file);
    // fwrite(&frame_data.storage_temperature, sizeof(float), 1, file);
    // fwrite(&frame_data.external_temperature, sizeof(float), 1, file);
    // fwrite(&frame_data.humidity, sizeof(float), 1, file);
    // fwrite(&frame_data.attitude, sizeof(float), 1, file);

    // Flush the buffers after each write
    fflush(file);
  }


  // Writes the images to the given file
  // Inputs: 
  // file: The C file object to write to
  void DataHandler::WriteImagesToFile(FILE* file) {
    // Null pointer check
    if (!file) {
      throw SystemHaltException();
    }

    // Write timestamp of image
    fwrite(&frame_data.time_stamp, sizeof(float), 1, file);

    // Write image to the given file
    // fwrite(frame_data.image, sizeof(float), camera_.GetImageSize(), file);

    // Flush the buffers after each write
    fflush(file);
  }

}
