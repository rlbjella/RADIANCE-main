#ifndef RADIANCE_SRC_SENSORS_HUMIDITYSENSOR_H_
#define RADIANCE_SRC_SENSORS_HUMIDITYSENSOR_H_
namespace RADIANCE {

  // Class for interacting with the TE HPP804B130 humidity sensor
  class HumiditySensor {

  public:
    // Callback function for each edge
    void EdgeCallbackFunction(int gpio, int level, uint32_t tick);

    // Initialize the sensor and start the ability to read
    HumiditySensor();

    // Return a humidity measurement
    float ReadHumidity();
    
  private:
    // Convert a measurement from the humidity sensor to a humidity measurement
    float ConvertFrequencyToHumidity(float freq);

    // Set to one if reset is necessary
    int reset_counter;

    // Pulse track counter
    int pulse_counter;

    // Gpio pin to use
    const int kGpioPin = 5;

    // Pulse period in microseconds
    const int kPulseDelay = 20;
  };

}
#endif // RADIANCE_SRC_SENSORS_HUMIDITYSENSOR_H_
