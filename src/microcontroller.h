#ifndef RADIANCE_SRC_MICROCONTROLLER_H_
#define RADIANCE_SRC_MICROCONTROLLER_H_

#include "datamanager.h"

namespace RADIANCE {
  // The main commanding unit. Encapsulates the functions of the Rasperry
  // Pi 3. Handles the system infinite loop
  class Microcontroller {
  public:
    
    Microcontroller();
    ~Microcontroller();

    // Setup and configure sensors
    void Initialize();

    // Step one frame
    void UpdateFrameCounter();

    // Start the system (infinite) loop
    void StartLoop();

    // Change the heater voltage based on the current temperature
    void UpdateHeaterVoltage();

  private:
    // Keeps track of frame number.
    // Resets every 60th frame
    int frame_counter_ = 0;

    // Used to handle input/output of data from reading the sensors to storage
    DataManager data_manager_;

  };
  
} // namespace RADIANCE
#endif //RADIANCE_SRC_MICROCONTROLLER_H_
