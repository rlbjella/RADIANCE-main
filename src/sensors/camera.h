#ifndef RADIANCE_SRC_SENSORS_CAMERA_H_
#define RADIANCE_SRC_SENSORS_CAMERA_H_

#include <array>
#include "../../include/raspicam/raspicam_still.h"
namespace RADIANCE {
  // Encapsulates the camera configuration and reading
  class Camera {

  public:

    // Camera image dimensions
    static const int kImageHeight = 480;
    static const int kImageWidth = 640;

    // Camera image size
    // Based on maximum jpg size for the image dimensions
    const static size_t kImageSize = kImageHeight*kImageWidth*3+54;

    // Setup and configure the camera
    Camera();
    // Read a spectrom
    void ReadImage(std::array<unsigned char,Camera::kImageSize>& image_data);


  private:

    // Raspberry Pi Camera library for grabbing images
    raspicam::RaspiCam_Still raspicam_still_;

  };
  
} // namespace RADIANCE
#endif //RADIANCE_SRC_SENSORS_CAMERA_H_
