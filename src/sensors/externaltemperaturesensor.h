#ifndef RADIANCE_SRC_SENSORS_EXTERNALTEMPERATURESENSOR_H_
#define RADIANCE_SRC_SENSORS_EXTERNALTEMPERATURESENSOR_H_

namespace RADIANCE {

  // Class for initializing and reading from the TMP102 temperature sensor
  class ExternalTemperatureSensor {
public:
    // Initialize the temperature sensor and get it ready to read temperature
    void Initialize();

    // Return a temperature measurement
    float ReadTemperature();
private:
    // Linux file handler
    int file_handle;

    // I2C software address
    const int kI2cAddress = 0x48;

    // Number of LSBs per Celsius
    const float kCountsToCelsius = 0.0625;
  };

}
#endif // RADIANCE_SRC_SENSORS_EXTERNALTEMPERATURESENSOR_H_
