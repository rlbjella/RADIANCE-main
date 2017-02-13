#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef RADIANCE_SRC_SENSORS_INTERNALTEMPERATURESENSOR_H_
#define RADIANCE_SRC_SENSORS_INTERNALTEMPERATURESENSOR_H_
namespace RADIANCE {

  // Class for initializing and reading from the DS18B20 temperature sensor
  class InternalTemperatureSensor {

  public:
  InternalTemperatureSensor(char* aserial_str):serial_str(aserial_str) {}

    // Initialize the temperature sensor and get it ready to read temperature
    void Initialize();
    // Return a temperature measurement
    float ReadTemperature();
  private:
    // 1 Wire file location string
    const char* location_str = "/sys/bus/w1/drivers/w1_slave_driver/%s/w1_slave";

    char* serial_str;
  };

}
#endif // RADIANCE_SRC_SENSORS_INTERNALTEMPERATURESENSOR_H_
