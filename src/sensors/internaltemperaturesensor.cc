#include <fstream>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <stdexcept>
#include "internaltemperaturesensor.h"

namespace RADIANCE{

  // Set sensor location based on serial number
  InternalTemperatureSensor::InternalTemperatureSensor(std::string sensor_file_):sensor_file_(sensor_file_) {
  }

  // Reads temperature from temperature file
  // Opens the sensor file, filter to the temperature and covert to celcius
  // Throws runtime_error if the temperature file could not be read
  float InternalTemperatureSensor::ReadTemperature() {

    // Open the file and save the file handle
    std::ifstream temp_file(kLocationStrPrefix + sensor_file_ + kLocationStrPostfix);

    // If the file cannot be read from throw runtime error
    if (!temp_file.good()) {
      std::string error_message("Could not open temperature file: " + sensor_file_);
      throw std::runtime_error(error_message);
    }

    // Read the file into a buffer
    std::string buf((std::istreambuf_iterator<char>(temp_file)),
                 std::istreambuf_iterator<char>());

    // Check if the file has the standard format
    int match = buf.find("t=");

    if (match == std::string::npos) {
      std::string error_message("Temperature file does not contain proper format: " + sensor_file_);
      throw std::runtime_error(error_message);
    }
    // Cut the string to just the temperature information
    // The temperature information stats after 't='
    std::string temp_str(buf.substr(match+2));

    // Convert the string to float and convert to actual value
    return std::stof(temp_str)/1000;
  }
}
