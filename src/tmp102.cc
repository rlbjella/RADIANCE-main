#include "tmp102.h"
#include "../include/pigpio/pigpio.h"
namespace RADIANCE {
  TMP102::TMP102() {};
  TMP102::~TMP102() {};
  double TMP102::readTemp(){
      return 0.01;              // DEBUG
    }
   
} // namespace RADIANCE
