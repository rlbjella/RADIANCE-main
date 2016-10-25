#ifndef RADIANCE_SRC_TMP102_H_
#define RADIANCE_SRC_TMP102_H_
#include "sensor.h"

namespace RADIANCE {
  class TMP102: public Sensor {
  public:
    TMP102();
    ~TMP102();
    double readTemp();
  private:
    const float kBitsPerCelsius = 0.0625;
  };
}
#endif // RADIANCE_SRC_TMP102_H_
