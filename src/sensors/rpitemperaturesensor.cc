#include "rpitemperaturesensor.h"
#include <iostream>
#include <iterator>
#include <string>
#include <stdexcept>

namespace RADIANCE{
  RPiTemperatureSensor::RPiTemperatureSensor():kLocationStr("/sys/class/thermal/thermal_zone0/temp") {}
  // Reads temperature from temperature sensor file
  // Opens the file, reads the temperature in as ASCII, then closes the file
  float RPiTemperatureSensor::ReadTemperature() {
    // Open the temperature file: temperature_file format is degrees Celcius in ASCII
    std::ifstream temp_file(kLocationStr);

    // Check if the file can be found and read
    if (!temp_file.good()) {
      throw std::runtime_error("Cannot read temperature file: " + kLocationStr);
    }

    // Read the temperature, close the file and return
    std::string buf((std::istreambuf_iterator<char>(temp_file)),std::istreambuf_iterator<char>());

    // Convert string to float
    float temp = std::stof(buf);

    // Return actual temperature value
    return temp/1000;
  }
}
