#include <iostream>
#include "tmp102.h"

namespace RADIANCE {
  TMP102::TMP102() {};
  TMP102::~TMP102() {};
  double TMP102::readRegister() {
    i2cdevlib
  }
  double TMP102::readTemp(){
    int8_t LSBTemp = 30;
    int8_t MSBTemp = 30;

    int16_t tempMeasurement = (LSBTemp << 4) | (MSBTemp >> 4);
    uint16_t x = static_cast<unsigned int> (tempMeasurement);
    std::cout << x << std::endl;
    double temp = static_cast<float>(x)*0.0625
    return 0;              // DEBUG
  }
   
} // namespace RADIANCE
