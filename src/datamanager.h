#ifndef RADIANCE_SRC_DATAMANAGER_H_
#define RADIANCE_SRC_DATAMANAGER_H_

namespace RADIANCE {
  // DataManager encapsulates the reading->writing process
  // The read functions set the data in the science data struct
  class DataManager{
  public:

    DataManager();
    ~DataManager();
    
    // Reads a measurement from each sensor and places it into the
    // science data struct.
    // Inputs: 
    // frame_counter: Used to determine whether a picture is needed
    void ReadSensorData(int frame_counter);

    // Writes the science data struct to storage
    void WriteMeasurementsToStorage(int frame_counter);

    int GetInternalTemperature();

  private:
    // Reads spectrometer data into frame data
    void ReadSpectrometer();

    // Reads engineering data into frame data
    void ReadInternalTemperature();
    void ReadExternalTemperature();
    void ReadHumidity();
    void ReadPressure();
    void ReadAttitude();

    // Reads camera data into frame data
    void ReadCamera();

    // Structure type to hold all the sensor data for each frame
    struct frame_data_type_ {
      int internal_temperature;
    };

    // Holds the science data for each frame
    frame_data_type_ frame_data_;
  };

} // namespace RADIANCE
#endif //RADIANCE_SRC_DATAMANAGER_H_
