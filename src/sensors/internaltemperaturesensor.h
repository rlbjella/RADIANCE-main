#include <fcntl.h>
#include <stdlib.h>

#ifndef RADIANCE_SRC_SENSORS_INTERNALTEMPERATURESENSOR_H_
#define RADIANCE_SRC_SENSORS_INTERNALTEMPERATURESENSOR_H_
namespace RADIANCE {

  // Class for initializing and reading from the DS18B20 temperature sensor
  class InternalTemperatureSensor {

  public:
    // Set location based on serial number
  InternalTemperatureSensor(char* aserial_str);

    // Return a temperature measurement
    float ReadTemperature();
  private:

    // Serial number of device, used for opening the sensor file
    const char* kLocationStr;

  };

}
#endif // RADIANCE_SRC_SENSORS_INTERNALTEMPERATURESENSOR_H_
