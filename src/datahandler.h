#ifndef RADIANCE_SRC_DATAHANDLER_H_
#define RADIANCE_SRC_DATAHANDLER_H_

#include "sensors/spectrometer.h"
#include "sensors/internaltemperaturesensor.h"
#include "sensors/externaltemperaturesensor.h"
#include "sensors/humiditysensor.h"
#include "sensors/attitudesensor.h"
#include "sensors/camera.h"
#include <iostream>
#include <fstream>

namespace RADIANCE {
  // DataHandler encapsulates the data transfer process
  // The read functions set the data in the science data struct
  class DataHandler{
  public:

    // Setup and configure sensors
    void Initialize();

    // Reads a measurement from each sensor and places it into the
    // science data struct.
    void ReadSensorData(const int frame_counter);

    // Process the measured data and then write the heater output
    void SetThermalControl();

    // Writes the science data struct to storage
    void WriteFrameToStorage(const int frame_counter);

  private:

    // Structure type to hold all the sensor data for each frame
    struct frame_data_type {
      float* spectrum;
      float humidity;
      float upper_battery_temperature;
      float lower_battery_temperature;
      float storage_temperature;
      float external_temperature;
      float attitude;
      unsigned char* image;
    };

    // Holds the science data for each frame
    frame_data_type frame_data;

    // Sensor data members
    Spectrometer spectrometer_;
    HumiditySensor humidity_sensor_;
    InternalTemperatureSensor upper_battery_temperature_sensor_;
    InternalTemperatureSensor lower_battery_temperature_sensor_;
    InternalTemperatureSensor storage_temperature_sensor_;
    ExternalTemperatureSensor external_temperature_sensor_;
    AttitudeSensor attitude_sensor_;
    Camera camera_;

    // Storage data objects for regular data
    // These are kept open for performance
    FILE* slc_data_file;
    FILE* mlc1_data_file;
    FILE* mlc2_data_file;

    // Image data objects, these are also kept open
    FILE* mlc1_image_file;
    FILE* mlc2_image_file;


    // Writes the frame data to the given file
    void WriteDataToFile(FILE* file);

    // Writes the images to the given file
    void WriteImagesToFile(FILE* file);

    // These functions read the measurements into the frame data struct
    void ReadSpectrum();
    void ReadInternalTemperature();
    void ReadExternalTemperature();
    void ReadHumidity();
    void ReadAttitude();
    void ReadCamera();
  };

} // namespace RADIANCE
#endif //RADIANCE_SRC_DATAHANDLER_H_
