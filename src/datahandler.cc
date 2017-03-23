#include <stdio.h>
#include <sys/types.h>
#include <chrono>
#include <limits>
#include <iostream>
#include <thread>
#include <stdexcept>
#include "../include/avaspec/avaspec.h"
#include "systemhaltexception.h"
#include "datahandler.h"
#include "microcontroller.h"
#include "controls/heatercontrol.h"

namespace RADIANCE {

  // Reads a measurement from each sensor and places it into the
  // science data struct.
  // Inputs: 
  // frame_counter: Used to determine whether a picture is needed
  void DataHandler::ReadSensorData(const int frame_counter) {

    // Read timestamp measurement
    // This timestamp represents seconds since Unix epoch
    std::chrono::seconds ms = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch());
    frame_data_.time_stamp = ms.count();
    std::cout << "Timestamp: " << frame_data_.time_stamp << "; ";

    // Read main instrument(spectrometer)
    spectrometer_.ReadSpectrum(frame_data_.spectrum);

    // Read housekeeping(engineering) sensors
    frame_data_.spectrometer_temperature = spectrometer_.ReadSpectrometerTemperature();
    frame_data_.rpi_temperature = rpi_temperature_sensor_.ReadTemperature();

    // Read internal temperature sensors
    // If the sensors are not responding, assume heating is not needed so return large number
    try {
      frame_data_.upper_battery_temperature = upper_battery_temperature_sensor_.ReadTemperature();
    } catch (const std::exception& e) {
      frame_data_.upper_battery_temperature = std::numeric_limits<float>::max();
    }

    try {
      frame_data_.lower_battery_temperature = lower_battery_temperature_sensor_.ReadTemperature();
    } catch (const std::exception& e) {
      frame_data_.lower_battery_temperature = std::numeric_limits<float>::max();
    }

    try {
      frame_data_.storage_temperature = storage_temperature_sensor_.ReadTemperature();
    } catch (const std::exception& e) {
      frame_data_.storage_temperature = std::numeric_limits<float>::max();
    }

    frame_data_.external_temperature = external_temperature_sensor_.ReadTemperature();
    frame_data_.humidity = humidity_sensor_.ReadHumidity();
    attitude_sensor_.ReadAttitude(frame_data_.attitude_values);

    // Take a picture every 60 frames
    if (frame_counter==59) {
      camera_.ReadImage(frame_data_.image);
    }
  }

  // Writes the frame data to a csv file
  // Inputs: 
  // frame_counter: Used to determine a picture needs to be written
  void DataHandler::WriteFrameToStorage(const int frame_counter) {

    // Make sure at least one data file can be written to
    // If not, restart the system
    if (!slc_data_file_.good() && !mlc1_data_file_.good() && !mlc2_data_file_.good()) {
      throw SystemHaltException();
    }

    // Writes the data(measurements) to all three drives every second
    WriteDataToFile(slc_data_file_);
    WriteDataToFile(mlc1_data_file_);
    WriteDataToFile(mlc2_data_file_);

    // Write an image to just the MLC drives every minute
    if (frame_counter==59) {
      WriteImagesToFile();
    }
  }

  // Gets the frame_data struct for other routines
  DataHandler::frame_data_type DataHandler::GetFrameData() {return frame_data_;}

  // Writes the frame data to the given file
  // Inputs:
  // file: The ofstream object to write to. If the file cannot be found/written to do nothing
  void DataHandler::WriteDataToFile(std::ofstream& file) {

    // Check that the data file is OK
    // If not OK, do nothing
    if (file.good()) {
    
      // Write timestamp of measurement
      file << frame_data_.time_stamp;

      // Write the spectrometer measurements
      for (auto& i : frame_data_.spectrum) {
        file << i;
      }
      // Write the engineering/housekeeping measurements to the given file
      file << frame_data_.spectrometer_temperature;
      file << frame_data_.rpi_temperature;
      file << frame_data_.upper_battery_temperature;
      file << frame_data_.lower_battery_temperature;
      file << frame_data_.storage_temperature;
      file << frame_data_.external_temperature;
      file << frame_data_.humidity;

      // Write the attitude measurements
      for (auto& i : frame_data_.attitude_values) {
        file << i;
      }

    }
  }


  // Writes the images to storage
  // If image drives cannot be found, print debug information but do nothing
  void DataHandler::WriteImagesToFile() {

    // Use timestamp as filename
    std::string filename(std::to_string(frame_data_.time_stamp));

    // Attempt to write mlc1 images
    std::ofstream mlc1_image_file("/mnt/mlcdrive1/images/" + filename,std::ios::binary|std::ios::app);
    if (mlc1_image_file.good()) {
      for (auto& i : frame_data_.image) {
        mlc1_image_file << i;
      }
    } else {
      std::cerr << "Could not write images to mlcdrive2" << std::endl;
    }
    mlc1_image_file.close();

    // Attempt to write mlc2 images
    std::ofstream mlc2_image_file("/mnt/mlcdrive2/images/" + filename,std::ios::binary|std::ios::app);
    if (mlc2_image_file.good()) {
      for (auto& i : frame_data_.image) {
        mlc2_image_file << i;
      }
    } else {
      std::cerr << "Could not write images to mlcdrive2" << std::endl;
    }
    mlc2_image_file.close();

  }

}
