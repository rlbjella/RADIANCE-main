#ifndef RADIANCE_SRC_SENSORS_ATTITUDESENSOR_H_
#define RADIANCE_SRC_SENSORS_ATTITUDESENSOR_H_
#include "../../include/ltc2470/ltc2470.h"
#include <cmath>

namespace RADIANCE {

  // Class for initializing and reading measurements from the attitude determination photodiodes
  class AttitudeSensor {

  public:
    // Setup GPIO pins and open SPI device
    AttitudeSensor();
    
    // Constant number of photodiodes
    const static int kNumPhotodiodes = 4;

    // Returns all four adc measurements
    // Returns false if the read failed
    bool ReadAttitude(std::array<float,kNumPhotodiodes>& f_current);

  private:

    // Reads a specific adc
    float ReadAdc(unsigned char pdiode);

    // SPI ADC device
    ltc2470* adc_;

    // Resistor values in ohms
    const unsigned int kResistorValue1 = 1000;
    const unsigned int kResistorValue2 = 1000;
    const unsigned int kResistorValue3 = 1000;
    const unsigned int kResistorValue4 = 1000;

	// Resolution of ADC, equal to 2^(bits)-1
	const unsigned int kAdcResolution = (std::pow(2,16) - 1);

    // Reference voltage
    const float kReferenceVoltage = 3.3;
  };

}
#endif // RADIANCE_SRC_SENSORS_ATTITUDESENSOR_H_
