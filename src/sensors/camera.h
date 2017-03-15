#ifndef RADIANCE_SRC_SENSORS_CAMERA_H_
#define RADIANCE_SRC_SENSORS_CAMERA_H_

#include <array>
#include "../../include/raspicam/raspicam_still.h"
namespace RADIANCE {
  // Encapsulates the camera configuration and reading
  class Camera {
  public:

    // Setup and configure the camera
    Camera();

    // Camera image size
    const static size_t kImageSize = 921654;

    // Read a spectrom
    void ReadImage(std::array<unsigned char,kImageSize>& image_data);

  private:
    // Raspberry Pi Camera library for grabbing images
    raspicam::RaspiCam_Still raspicam_still_;

  };
  
} // namespace RADIANCE
#endif //RADIANCE_SRC_SENSORS_CAMERA_H_
