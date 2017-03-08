#include <cmath>
#ifndef RADIANCE_SRC_SENSORS_ATTITUDESENSOR_H_
#define RADIANCE_SRC_SENSORS_ATTITUDESENSOR_H_
namespace RADIANCE {

  // Class for initializing and reading measurements from the attitude determination photodiodes
  class AttitudeSensor {

  public:
    // Initialize the photodiodes and get them ready to take measurements
    void Initialize();

    // Return an attitude measurement
    float ReadAttitude();
  };

}
#endif // RADIANCE_SRC_SENSORS_ATTITUDESENSOR_H_
