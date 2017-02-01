#ifndef RADIANCE_SRC_SENSORS_SPECTROMETER_H_
#define RADIANCE_SRC_SENSORS_SPECTROMETER_H_
#include "../../include/avaspec/avaspec.h"

namespace RADIANCE {
  // Encapsulates the spectrometer configuration and reading
  class Spectrometer {

  public:
    // Setup and configure the spectrometer
    void Initialize();

    // Return a spectrum measurement
    float* ReadSpectrum();

    // Getter for num_pixels
    int GetNumPixels();

    // Return spectrometer temperature
    float ReadSpectrometerTemperature();

  private:
    // Number of spectrometer elements
    static const int num_pixels = 2048;

    // Spectrometer reference handle
    AvsHandle handle_;

    // Avantes library requires double array so use for measuring
    double d_spectrum[num_pixels];

    // Convert double spectrum to float array to save data storage
    float f_spectrum[num_pixels];

    // Converts the voltage into a temperature
    float ConvertVoltageToTemperature(float voltage);

  };

} // namespace RADIANCE
#endif //RADIANCE_SRC_SENSORS_SPECTROMETER_H_
