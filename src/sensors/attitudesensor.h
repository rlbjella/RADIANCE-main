#ifndef RADIANCE_SRC_SENSORS_ATTITUDESENSOR_H_
#define RADIANCE_SRC_SENSORS_ATTITUDESENSOR_H_
#include "ltc2470.h"
#include <cmath>

namespace RADIANCE {

  // Class for initializing and reading measurements from the attitude determination photodiodes
  class AttitudeSensor {

  public:
    // Initialize attitude sensor
    AttitudeSensor();

    // Constant number of photodiodes
    const static int kNumPhotodiodes = 4;

    // Returns all four adc measurements
    void ReadAttitude(std::array<float,kNumPhotodiodes>& f_current);

  private:
    // SPI ADC device
    ltc2470 adc;

    // Reads a specific adc
    float ReadAdc(unsigned char pdiode, ltc2470 adc);

    // Resistor values in ohms
    const unsigned int kResistorValue1 = 5000;
    const unsigned int kResistorValue2 = 5000;
    const unsigned int kResistorValue3 = 5000;
    const unsigned int kResistorValue4 = 5000;

	// Resolution of ADC, equal to 2^(bits)-1
	const unsigned int kAdcResolution = (unsigned int)(pow(2,16) - 1);

    // Reference voltage
    const float kReferenceVoltage = 3.3;
  };

}
#endif // RADIANCE_SRC_SENSORS_ATTITUDESENSOR_H_
