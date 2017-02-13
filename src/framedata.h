#ifndef RADIANCE_SRC_FRAMEDATA_H_
#define RADIANCE_SRC_FRAMEDATA_H_

namespace RADIANCE {
  class FrameData{

  private:
    float* spectrum;
    float spectrometer_temperature;
    float rpi_temperature;
    float upper_battery_temperature;
    float lower_battery_temperature;
    float storage_temperature;
    float external_temperature;
    float humidity;
    float attitude;
    unsigned char* image;
  };

} // namespace RADIANCE
#endif //RADIANCE_SRC_FRAMEDATA_H_
