#ifndef RADIANCE_SRC_SENSORS_RPITEMPERATURESENSOR_H_
#define RADIANCE_SRC_SENSORS_RPITEMPERATURESENSOR_H_

#include <fstream>
namespace RADIANCE {

  // Class for initializing and reading from the RPi temperature sensor
  // Raspberry Pi temperature sensor does not require initialization
  class RPiTemperatureSensor {

  public:
    // Return a temperature measurement
    float ReadTemperature();
  };

}
#endif // RADIANCE_SRC_SENSORS_RPITEMPERATURESENSOR_H_
