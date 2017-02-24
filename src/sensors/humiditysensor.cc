#include <cmath>
#include "humiditysensor.h"

namespace RADIANCE{
  // TODO(James)
  void HumiditySensor::Initialize() {
  }

  // TODO(James)
  float HumiditySensor::ReadHumidity(){
    return ConvertFrequencyToHumidity(7500);
  }

  // Converts frequency to humidity using a polynomial fit equation
  float HumiditySensor::ConvertFrequencyToHumidity(float freq) {
    return 1.2158e-8*pow(freq,3)-2.193e-4*pow(freq,2)+1.2094*freq-1.8698e3;
  }
}
