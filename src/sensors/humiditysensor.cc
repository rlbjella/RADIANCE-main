#include <cmath>
#include <pigpio.h>
#include "humiditysensor.h"

namespace RADIANCE{

  // Callback function for each edge
  void HumiditySensor::EdgeCallbackFunction(int gpio, int level, uint32_t tick)
  {
    if (reset_counter)
      {
        reset_counter = 0;
        pulse_counter = 0;
      }

    /* only record low to high edges */
    if (level == 1)
      pulse_counter++;
  }
  
  // Initializes humidity sensor and prepares it for measurement
  HumiditySensor::HumiditySensor() {

    int wave_id, mode;
    gpioPulse_t pulse[2];
    int kPulseDelay = 20;
    int g_mask = 1;

    gpioWaveClear();

    pulse[0].gpioOn  = g_mask;
    pulse[0].gpioOff = 0;
    pulse[0].usDelay = kPulseDelay;

    pulse[1].gpioOn  = 0;
    pulse[1].gpioOff = g_mask;
    pulse[1].usDelay = kPulseDelay;

    gpioWaveAddGeneric(2, pulse);

    wave_id = gpioWaveCreate();

    // gpioSetAlertFunc(kGpioPin, EdgeCallbackFunction);

    mode = PI_INPUT;

    gpioSetMode(kGpioPin, mode);
  }

  // Reads a humidity measurement. This requires finding the frequency
  // of the wave and then converting that measurement to percent
  // relative humidity
  float HumiditySensor::ReadHumidity(){
    reset_counter = 1;

    float period = pulse_counter/kPulseDelay;
    float frequency = 1/period;

    return ConvertFrequencyToHumidity(frequency);
  }

  // Converts frequency to humidity using a polynomial fit equation
  float HumiditySensor::ConvertFrequencyToHumidity(float freq) {
    return 1.2158e-8*pow(freq,3)-2.193e-4*pow(freq,2)+1.2094*freq-1.8698e3;
  }

}
