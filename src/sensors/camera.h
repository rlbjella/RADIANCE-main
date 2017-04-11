#ifndef RADIANCE_SRC_SENSORS_CAMERA_H_
#define RADIANCE_SRC_SENSORS_CAMERA_H_

namespace RADIANCE {
  // Encapsulates the camera configuration and reading
  class Camera {

  public:

    // Reads and writes the camera image
    bool TakePicture(int time_stamp);

  };
  
} // namespace RADIANCE
#endif //RADIANCE_SRC_SENSORS_CAMERA_H_
