#ifndef RADIANCE_SRC_DATAHANDLER_H_
#define RADIANCE_SRC_DATAHANDLER_H_

#include "spectrometer.h"
#include "camera.h"

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
    void ReadPressure();
    void ReadAttitude();

    // Reads camera data into frame data
    void ReadCamera();

    // Number of detector elements in the spectrometer
    const int kNumSpectrumPixels = 3648;

    // Structure type to hold all the sensor data for each frame
    struct frame_data_type {
      float* spectrum;
    };

    // Holds the science data for each frame
    frame_data_type frame_data;

    // Sensor data members
    Spectrometer spectrometer_;
    Camera camera_;
  };

} // namespace RADIANCE
#endif //RADIANCE_SRC_DATAHANDLER_H_
