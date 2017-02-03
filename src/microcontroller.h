#ifndef RADIANCE_SRC_MICROCONTROLLER_H_
#define RADIANCE_SRC_MICROCONTROLLER_H_

#include "datahandler.h"
#include "controls/heatercontrol.h"

namespace RADIANCE {
    // The main commanding unit. Encapsulates the command
    // functions of the Rasperry Pi 3. 
  class Microcontroller {
  public:

    // Setup and configure sensors
    void Initialize();

    // Step one frame
    void UpdateFrameCounter();

    // Start the system (infinite) loop
    void StartLoop();

    // Process the measured data and then write the heater output
    void SetThermalControl(DataHandler::frame_data_type frame_data);

  private:
    // Keeps track of frame number.
    // Resets every 60th frame
    int frame_counter = 0;

    // Used to handle input/output of data from reading the sensors to storage
    DataHandler data_handler_;

    // Initialize the heater controls
    HeaterControl battery_heater(1);
    HeaterControl spectrometer_heater(1);
  };
  
} // namespace RADIANCE
#endif //RADIANCE_SRC_MICROCONTROLLER_H_
