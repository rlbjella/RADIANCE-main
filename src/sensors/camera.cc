#include <stdexcept>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include "camera.h"
#include <algorithm>

namespace RADIANCE{

  // Initialize the camera object by opening the raspicam object, configuring
  // the image and then sleeping while the camera stabilizes
  Camera::Camera() {

    // If successful, configure the image
    // If not able to open a camera object, do nothing
    if (raspicam_still_.open()) {
      // Configure the image
      raspicam_still_.setCaptureSize(Camera::kImageWidth,Camera::kImageHeight);
      raspicam_still_.setEncoding(raspicam::RASPICAM_ENCODING_JPEG);

      // Let the camera stabilize
      std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    } else {
      std::cerr<< "Error opening camera" <<std::endl;
    }
  }

  // Reads and writes the camera image
  void Camera::ReadImage(std::array<unsigned char,Camera::kImageSize>& image_data) {

    // Retrieve the image in rgb format
		// If not able to retrieve the image, throw an error
    if (!raspicam_still_.grab_retrieve(image_data.data(),Camera::kImageSize)) {
			throw std::runtime_error("Could not retrieve image");
		}
  }

}
