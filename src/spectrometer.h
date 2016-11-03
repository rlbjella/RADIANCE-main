#ifndef RADIANCE_SRC_SPECTROMETER_H_
#define RADIANCE_SRC_SPECTROMETER_H_
#include "../include/avaspec/avaspec.h"

namespace RADIANCE {
  // Encapsulates the spectrometer configuration and reading
  class Spectrometer {
  public:
    
    Spectrometer();
    ~Spectrometer();

    // Setup and configure the spectrometer
    void Initialize();

    // Read a spectrom
    double* ReadSpectrum();

  private:
    AvsHandle handle_;
    
  };
  
} // namespace RADIANCE
#endif //RADIANCE_SRC_SPECTROMETER_H_
