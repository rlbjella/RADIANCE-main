#ifndef RADIANCE_SRC_MICROCONTROLLER_H_
#define RADIANCE_SRC_MICROCONTROLLER_H_

#include "datahandler.h"

namespace RADIANCE {
  // The main commanding unit. Encapsulates the functions of the Rasperry
  // Pi 3. Handles the system infinite loop
  class Microcontroller {
  public:
    
    Microcontroller();
    ~Microcontroller();

    // Initialize data members
    void Initialize();

    // Step one frame
    void UpdateFrameCounter();

    // Start the system (infinite) loop
    void StartLoop();


  private:
    // Keeps track of frame number.
    // Resets every 60th frame
    int frame_counter = 0;

    // Used to handle input/output of data from reading the sensors to storage
    DataHandler data_handler_;
  };
  
} // namespace RADIANCE
#endif //RADIANCE_SRC_MICROCONTROLLER_H_
