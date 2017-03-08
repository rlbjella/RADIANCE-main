#ifndef RADIANCE_SRC_SENSORS_HUMIDITYSENSOR_H_
#define RADIANCE_SRC_SENSORS_HUMIDITYSENSOR_H_
namespace RADIANCE {

  // Class for interacting with the TE HPP804B130 humidity sensor
  class HumiditySensor {

  public:
    // Initialize the sensor and start the ability to read
    HumiditySensor();

    // Return a humidity measurement
    float ReadHumidity();

  private:
    // Convert a measurement from the humidity sensor to a humidity measurement
    float ConvertFrequencyToHumidity(float freq);
  };

}
#endif // RADIANCE_SRC_SENSORS_HUMIDITYSENSOR_H_
