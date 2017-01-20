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

  private:
    AvsHandle handle_;

    // Avantes library requires double array so use for measuring
    double d_spectrum[3648];

    // Convert double spectrum to float array to save data storage
    float f_spectrum[3648];
    
  };
  
} // namespace RADIANCE
#endif //RADIANCE_SRC_SPECTROMETER_H_
