#include <iostream>
#include <string.h>
#include <unistd.h>
#include "internaltemperaturesensor.h"

namespace RADIANCE{

  // Set sensor location based on serial number
  InternalTemperatureSensor::InternalTemperatureSensor(char* aserial_str):kLocationStr(aserial_str) {}

  // Reads temperature from temperature file
  // Opens the sensor file, filter to the temperature and covert to celcius
  float InternalTemperatureSensor::ReadTemperature() {
    // Open the file and save the file handle
    int fd = open(kLocationStr, O_RDONLY);

    // Initialize the buffer and read 256 bytes
    char buf[256];
    read(fd, buf, 256);

    // Cut the string to just the temperature information
    char tmp_data[6];
    strncpy(tmp_data, strstr(buf, "t=") + 2, 5); 

    // Convert the string to float
    float temp = strtof(tmp_data, NULL);
    return temp/1000;
  }
}
