#ifndef RADIANCE_SRC_EXTERNALTEMPERATURESENSOR_H_
#define RADIANCE_SRC_EXTERNALTEMPERATURESENSOR_H_
namespace RADIANCE {

  // Class for initializing and reading from the TMP102 temperature sensor
  class ExternalTemperatureSensor {
    
  public:
    // Initialize the temperature sensor and get it ready to read temperature
    void Initialize();

    // Return a temperature measurement
    float ReadTemperature();
  };    
      
}
#endif // RADIANCE_SRC_EXTERNALTEMPERATURESENSOR_H_
