#ifndef RADIANCE_SRC_DATAHANDLER_H_
#define RADIANCE_SRC_DATAHANDLER_H_

#include "sensors/spectrometer.h"
#include "sensors/internaltemperaturesensor.h"
#include "sensors/externaltemperaturesensor.h"
#include "sensors/humditysensor.h"
#include "sensors/attitudesensor.h"
#include "sensors/camera.h"

namespace RADIANCE {
  // DataHandler encapsulates the reading->writing process
  // The read functions set the data in the science data struct
  class DataHandler{
  public:

    DataHandler();
    ~DataHandler();
    
    // Setup and configure sensors
    void Initialize();
    
    // Reads a measurement from each sensor and places it into the
    // science data struct.
    // Inputs: 
    // frame_counter: Used to determine whether a picture is needed
    void ReadSensorData(int frame_counter);

    // Writes the science data struct to storage
    void WriteMeasurementsToStorage(int frame_counter);

  private:
    // Reads spectrum data into frame data
    void ReadSpectrum();

    // Reads engineering data into frame data
    void ReadInternalTemperature();
    void ReadExternalTemperature();
    void ReadHumidity();
    void ReadAttitude();

    // Reads camera data into frame data
    void ReadCamera();

    // Number of detector elements in the spectrometer
    const int kNumSpectrumPixels = 3648;

    // Size of the camera image
    const int kNumSpectrumPixels = 10000;

    // Structure type to hold all the sensor data for each frame
    struct frame_data_type {
      float* spectrum;
      unsigned char* image;
      float humidity;
      float upper_battery_temperature;
      float lower_battery_temperature;
      float storage_temperature;
      float external_temperature;
      float attitude;
    };

    // Holds the science data for each frame
    frame_data_type frame_data;

    // Sensor data members
    Spectrometer spectrometer_;
    Camera camera_;
    HumiditySensor humidity_sensor_;
    InternalTemperatureSensor upper_battery_temperature_sensor_;
    InternalTemperatureSensor lower_battery_temperature_sensor_;
    InternalTemperatureSensor storage_temperature_sensor_;
    ExternalTemperatureSensor external_temperature_sensor_;
    AttitudeSensor attitude_sensor;

  };

} // namespace RADIANCE
#endif //RADIANCE_SRC_DATAHANDLER_H_
