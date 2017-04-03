#include <pigpio.h>
#include <iostream>
#include "externaltemperaturesensor.h"

namespace RADIANCE{
  // Initializes the temperature sensor by setting the file handle to the I2C address
  ExternalTemperatureSensor::ExternalTemperatureSensor() {
    gpioInitialise();
    file_handle_ = i2cOpen(1,kI2cAddress,0);
  }

  // Read temperature from sensor
  float ExternalTemperatureSensor::ReadTemperature() {
    // Create buffer and read two bytes from register
    char buf[2];
    gpioInitialise();
    i2cReadI2CBlockData(file_handle_,kTempRegister,buf,2);
    return ConvertBlockDataToTemperature(buf);
  }

  // Converts two's complement block data to temperature measurement
  float ExternalTemperatureSensor::ConvertBlockDataToTemperature(char* buf) {
    // Combines high and low measurements
    int meas = buf[0] << 4 | buf[1] >> 4;

    // Check if temperature is negative
    // If negative, take complement and add 1
    if (buf[0] & 0x10000000) {
      meas = ~meas+1;
    }
    return meas*kCountsToCelsius;
  }
}
