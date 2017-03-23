#ifndef RADIANCE_SRC_SENSORS_RPITEMPERATURESENSOR_H_
#define RADIANCE_SRC_SENSORS_RPITEMPERATURESENSOR_H_

#include <fstream>
namespace RADIANCE {

  // Class for initializing and reading from the RPi temperature sensor
  class RPiTemperatureSensor {

  public:

    // Initialize the sensor
    RPiTemperatureSensor();

    // Return a temperature measurement
    float ReadTemperature();
  private:
    // Location of temperature sensor file
    const std::string kLocationStr;
  };

}
#endif // RADIANCE_SRC_SENSORS_RPITEMPERATURESENSOR_H_
