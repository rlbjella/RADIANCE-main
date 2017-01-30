#ifndef RADIANCE_SRC_SENSORS_HUMIDITYSENSOR_H_
#define RADIANCE_SRC_SENSORS_HUMIDITYSENSOR_H_
namespace RADIANCE {

  // Class for interacting with the TE HPP804B130 humidity sensor
  class HumiditySensor {
    
  public:
    // Initialize the sensor and start the ability to read
    void Initialize();

    // Return a humidity measurement
    float ReadHumidity();
  };    
      
}
#endif // RADIANCE_SRC_SENSORS_HUMIDITYSENSOR_H_
