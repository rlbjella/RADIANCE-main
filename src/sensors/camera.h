#ifndef RADIANCE_SRC_CAMERA_H_
#define RADIANCE_SRC_CAMERA_H_

#include "../../include/raspicam/raspicam_still.h"
namespace RADIANCE {
  // Encapsulates the camera configuration and reading
  class Camera {
  public:
    
    Camera();
    ~Camera();

    // Setup and configure the camera
    void Initialize();

    // Read a spectrom
    void ReadImage();

  private:
    // Raspberry Pi Camera library for grabbing images
    raspicam::RaspiCam_Still raspicam_still_;

    // Camera sensor data
    unsigned char* image_data;
    
  };
  
} // namespace RADIANCE
#endif //RADIANCE_SRC_CAMERA_H_
