#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include "camera.h"

namespace RADIANCE{

  // Initialize the camera object by opening the raspicam object, configuring
  // the image and then sleeping while the camera stabilizes
  Camera::Camera() {

    // Initialize camera library
    if (!raspicam_still_.open()) {
      std::cout<<"Error opening camera"<<std::endl;
    }

    // Allocate image buffer
    image_data=new unsigned char[image_size];

    // Configure the image
    raspicam_still_.setCaptureSize(640,480);
    raspicam_still_.setEncoding(raspicam::RASPICAM_ENCODING_JPEG);

    // Let the camera stabilize
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  }

  // Getter for image_size
  int Camera::GetImageSize() {
    return image_size;
  }

  // Reads and writes the camera image
  unsigned char* Camera::ReadImage() {

    // Retrieve the image in rgb format
    raspicam_still_.grab_retrieve(image_data,image_size);

    return image_data;
  }

}
