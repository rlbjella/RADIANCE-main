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
  // In general, if housekeep sensors cannot be read return high heater temperature
  // If science instruments cannot be read return zero
  void DataHandler::ReadSensorData(const int frame_counter) {

    // Read timestamp measurement
    // This timestamp represents seconds since Unix epoch
    std::chrono::seconds ms = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch());
    frame_data_.time_stamp = ms.count();
    std::cout << "Timestamp: " << frame_data_.time_stamp << std::endl;

    // Read main instrument(spectrometer)
    spectrometer_.ReadSpectrum(frame_data_.spectrum);

    // Read temperature sensors
    // These sensors are used for heater control. Overheating is a concern, so 
    // if the sensors are not responding, assume sensor is already at desired temperature
    try {
      frame_data_.spectrometer_temperature = spectrometer_.ReadSpectrometerTemperature();
    } catch (const std::exception& e) {
      std::cerr << "Could not read spectrometer temp sensor" << std::endl;
      frame_data_.spectrometer_temperature = Microcontroller::GetMaxHeaterTemp();
    }

    try {
      frame_data_.rpi_temperature = rpi_temperature_sensor_.ReadTemperature();
    } catch (const std::exception& e) {
      std::cerr << "Could not read RPi temp sensor" << std::endl;
      frame_data_.rpi_temperature = Microcontroller::GetMaxHeaterTemp();
    }

    try {
      frame_data_.upper_battery_temperature = upper_battery_temperature_sensor_.ReadTemperature();
    } catch (const std::exception& e) {
      std::cerr << "Could not read upper battery temp sensor" << std::endl;
      frame_data_.upper_battery_temperature = Microcontroller::GetMaxHeaterTemp();
    }

    try {
      frame_data_.lower_battery_temperature = lower_battery_temperature_sensor_.ReadTemperature();
    } catch (const std::exception& e) {
      std::cerr << "Could not read lower battery temp sensor" << std::endl;
      frame_data_.lower_battery_temperature = Microcontroller::GetMaxHeaterTemp();
    }

    try {
      frame_data_.storage_temperature = storage_temperature_sensor_.ReadTemperature();
    } catch (const std::exception& e) {
      std::cerr << "Could not read storage temp sensor" << std::endl;
      frame_data_.storage_temperature = Microcontroller::GetMaxHeaterTemp();
    }

    // Read environmental conditions
    // These sensors are not used in heating calculations, so return 0 if they cannot be read
    try {
      frame_data_.external_temperature = external_temperature_sensor_.ReadTemperature();
    } catch (const std::exception& e) {
      std::cerr << "Could not read env temp sensor" << std::endl;
      frame_data_.external_temperature = 0;
    }

    try {
      frame_data_.humidity  = humidity_sensor_.ReadHumidity();
    } catch (const std::exception& e) {
      std::cerr << "Could not read humidity sensor" << std::endl;
      frame_data_.humidity = 0;
    }

    // Read atittude system
    // If ADCS cannot be read, return zero for all measurements
    try {
      attitude_sensor_.ReadAttitude(frame_data_.attitude_values);
    } catch (const std::exception& e) {
      std::cerr << "Could not read attitude system" << std::endl;
      std::fill(frame_data_.attitude_values.begin(),frame_data_.attitude_values.end(),0);
    }

    // Take a picture every 60 frames
    // If camera cannot be read, return zero for all pixels
    if (frame_counter==59) {
      try {
        camera_.ReadImage(frame_data_.image);
      } catch (const std::exception& e) {
        std::cerr << "Could not read from camera" << std::endl;
        std::fill(frame_data_.image.begin(),frame_data_.image.end(),0);
      }
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


template<typename T> std::ostream& BinaryWrite(std::ostream& stream, const T& value) {
	return stream.write(reinterpret_cast<const char*>(&value), sizeof(T));
}
  // Writes the frame data to the given file
  // Inputs:
  // file: The ofstream object to write to. If the file cannot be found/written to do nothing
  void DataHandler::WriteDataToFile(std::ofstream& file) {

    // Check that the data file is OK
    // If not OK, do nothing
    if (file.good()) {
    
      // Write timestamp of measurement
      BinaryWrite(file,frame_data_.time_stamp);

      // Write the spectrometer measurements
      for (auto& i : frame_data_.spectrum) {
        BinaryWrite(file,i);
      }
      // Write the engineering/housekeeping measurements to the given file
     	BinaryWrite(file,frame_data_.spectrometer_temperature);
			BinaryWrite(file,frame_data_.rpi_temperature);
      BinaryWrite(file,frame_data_.upper_battery_temperature);
      BinaryWrite(file,frame_data_.lower_battery_temperature);
      BinaryWrite(file,frame_data_.storage_temperature);
      BinaryWrite(file,frame_data_.external_temperature);
      BinaryWrite(file,frame_data_.humidity);

      // Write the attitude measurements
      for (auto& i : frame_data_.attitude_values) {
        BinaryWrite(file,i);
      }

		file.flush();
    }
  }


  // Writes the images to storage
  // If image drives cannot be found, print debug information but do nothing
  void DataHandler::WriteImagesToFile() {

	std::cout << "Writing images" << std::endl; //DEBUG
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
