#ifndef RADIANCE_SRC_SPECTROMETER_H_
#define RADIANCE_SRC_SPECTROMETER_H_
#include "../../include/avaspec/avaspec.h"

namespace RADIANCE {
  // Encapsulates the spectrometer configuration and reading
  class Spectrometer {
  public:
    
    Spectrometer();
    ~Spectrometer();

    // Setup and configure the spectrometer
    void Initialize();

    // Read a spectrom
    float* ReadSpectrum();

    // Getter for num_pixels
    int GetNumPixels();

  private:
    AvsHandle handle_;

    // Number of spectrometer elements
    static const int num_pixels = 3648;

    // Avantes library requires double array so use for measuring
    double d_spectrum[num_pixels];

    // Convert double spectrum to float array to save data storage
    float f_spectrum[num_pixels];
    
  };
  
} // namespace RADIANCE
#endif //RADIANCE_SRC_SPECTROMETER_H_
