#include <wiringPiI2C.h>
#include "externaltemperaturesensor.h"
#include <iostream>

namespace RADIANCE{
  void ExternalTemperatureSensor::Initialize() {
    int file_handle = wiringPiI2CSetup(kI2cAddress);
  }
  float ExternalTemperatureSensor::ReadTemperature() {
    int lsb = wiringPiI2CReadReg8(file_handle,0);
    int msb = wiringPiI2CReadReg8(file_handle,1);

    float calib = (((msb << 8) | lsb) >> 4) * kCountsToCelsius;
    std::cout << calib << std::endl;
    return calib;
  }
}
