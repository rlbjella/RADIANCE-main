#include "camera.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <fstream>
#include "raspicam_still.h"

namespace RADIANCE{
  Camera::Camera() {}
  Camera::~Camera() {}

  void Camera::Initialize() {

    // DEBUG, cleanup and move to seperate file
    
    //Open camera 
    if (!raspicam_still_.open()) {
      std::cout<<"Error opening camera"<<std::endl;
    }
    raspicam_still_.setCaptureSize(640,480);
    raspicam_still_.setEncoding(raspicam::RASPICAM_ENCODING_JPEG);

    //wait a while until camera stabilizes
    std::cout<<"Sleeping for 3 secs"<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  }

  // Reads and writes the camera image
  void Camera::ReadImage() {

    //allocate memory
    unsigned char *data=new unsigned char[raspicam_still_.getImageBufferSize()];

    //extract the image in rgb format
    raspicam_still_.grab_retrieve(data,raspicam_still_.getImageBufferSize());//get camera image

    // Write to file
    static char name[27];
    time_t now = time(0);
    strftime(name, sizeof(name), "/mnt/FLASHDRIVE/%s", localtime(&now));

    std::ofstream outFile(name,std::ios::binary);

    outFile.write((char*)data,raspicam_still_.getImageBufferSize());
    outFile << std::flush;
    delete data;
  }
  
}
