#ifndef RADIANCE_SRC_INTERNALTEMPERATURESENSOR_H_
#define RADIANCE_SRC_INTERNALTEMPERATURESENSOR_H_
namespace RADIANCE {

  // Class for initializing and reading from the DS18B20 temperature sensor
  class InternalTemperatureSensor {
    
  public:
    // Initialize the temperature sensor and get it ready to read temperature
    void Initialize();
    // Return a temperature measurement
    float ReadTemperature();
  };    
      
}
#endif // RADIANCE_SRC_INTERNALTEMPERATURESENSOR_H_
