#ifndef RADIANCE_SRC_DATAHANDLER_H_
#define RADIANCE_SRC_DATAHANDLER_H_

#include <iostream>
#include <fstream>
#include <array>
#include "sensors/spectrometer.h"
#include "sensors/rpitemperaturesensor.h"
#include "sensors/internaltemperaturesensor.h"
#include "sensors/externaltemperaturesensor.h"
#include "sensors/humiditysensor.h"
#include "sensors/attitudesensor.h"
#include "sensors/camera.h"

namespace RADIANCE {
  // DataHandler encapsulates the data transfer process
  // The read functions set the data in the science data struct
  class DataHandler{
  public:

    // Setup and configure sensors
    DataHandler();

    // Reads a measurement from each sensor and places it into the
    // science data struct.
    void ReadSensorData(const int frame_counter);

    // Writes the science data struct to storage
    void WriteFrameToStorage(const int frame_counter);

    // Structure type to hold all the sensor data for each frame
    struct frame_data_type {
      unsigned int time_stamp;
      std::array<float,Spectrometer::kNumPixels> spectrum;
      float spectrometer_temperature;
      float rpi_temperature;
      float upper_battery_temperature;
      float lower_battery_temperature;
      float storage_temperature;
      float external_temperature;
      float humidity;
      std::array<float,AttitudeSensor::kNumPhotodiodes> attitude_values;
      std::array<unsigned char,Camera::kImageSize> image;
    };

    // Gets the frame_data struct for other routines
    frame_data_type GetFrameData();

  private:

    // Holds the science data for each frame
    frame_data_type frame_data;

    // Sensor data members
    Spectrometer spectrometer_;
    HumiditySensor humidity_sensor_;
    RPiTemperatureSensor rpi_temperature_sensor_;
    InternalTemperatureSensor upper_battery_temperature_sensor_{"/sys/bus/w1/drivers/w1_slave_driver/10-000803362138/w1_slave"}; // File location
    InternalTemperatureSensor lower_battery_temperature_sensor_{"/sys/bus/w1/drivers/w1_slave_driver/28-00000620a9b2/w1_slave"}; // File location
    InternalTemperatureSensor storage_temperature_sensor_{"/sys/bus/w1/drivers/w1_slave_driver/28-0000075f85ba/w1_slave"}; // File location
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
  };

} // namespace RADIANCE
#endif //RADIANCE_SRC_DATAHANDLER_H_
