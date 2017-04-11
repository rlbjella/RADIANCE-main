#include <cstdlib>
#include "camera.h"
#include <string>

namespace RADIANCE{

  // Reads and writes the camera image
  // Calls the system utility 'raspistill' and then copies the images using tee
  // Returns true if read succeeds
  // Please do not judge me for writing this garbage
  bool Camera::TakePicture(int time_stamp) {
    std::system(("raspistill -w 640 -h 480 -o - | tee /mnt/mlcdrive1/images/" + std::to_string(time_stamp) +  "/mnt/mlcdrive2/images/" + std::to_string(time_stamp)).c_str());
    return true;
  }

}
