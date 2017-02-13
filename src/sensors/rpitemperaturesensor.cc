#include "rpitemperaturesensor.h"
#include <iostream>

namespace RADIANCE{
  // Reads temperature from temperature sensor file
  // Opens the file, reads the temperature in as ASCII, then closes the file
  float RPiTemperatureSensor::ReadTemperature() {
    // Open the temperature file: temperature_file format is degrees Celcius in ASCII
    FILE* temperature_file = fopen(location_str,"r");

    // Read the temperature, close the file and return
    float temp;
    fscanf(temperature_file, "%f", &temp);
    fclose(temperature_file);
    return temp/1000;
  }
}
