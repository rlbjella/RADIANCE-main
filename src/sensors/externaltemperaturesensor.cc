#include <pigpio.h>
#include <iostream>
#include "externaltemperaturesensor.h"

namespace RADIANCE{
  // Initializes the temperature sensor by setting the file handle to the I2C address
  ExternalTemperatureSensor::ExternalTemperatureSensor() {
    file_handle = i2cOpen(1,kI2cAddress,0);
  }

  // Read temperature from sensor
  float ExternalTemperatureSensor::ReadTemperature() {
    // Create buffer and read two bytes from register
    char buf[2];
    i2cReadI2CBlockData(file_handle,kTempRegister,buf,2);
    return ConvertBlockDataToTemperature(buf);
  }

  // Converts two's complement block data to temperature measurement
  float ExternalTemperatureSensor::ConvertBlockDataToTemperature(char* buf) {
    int meas = buf[0] << 4 | buf[1] >> 4;
    return meas*kCountsToCelsius;
  }
}
