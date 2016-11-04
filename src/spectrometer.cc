#include <chrono>
#include <thread>
#include "spectrometer.h"
#include <iostream>
namespace RADIANCE{
  Spectrometer::Spectrometer() {}
  Spectrometer::~Spectrometer() {}

  void Spectrometer::Initialize() {
    
    // DEBUG code - for testing with the spectrometer test unit
    unsigned int byte_set;

    AvsIdentityType a_plist[30];

    // init the library, the parameter is type of interface.
    // 0 for USB
    // 1..255 com port (not support in the linux library, only in the windows DLL)
    // 256 Ethernet auto search.
    int n = AVS_Init(0);

    printf("USB spectrometers found: %d\n", AVS_GetNrOfDevices());

    n = AVS_GetList( sizeof(a_plist), &byte_set, a_plist );
    
    int err = 0;

    handle_ = AVS_Activate( &a_plist[0] );

    printf ("Test spectrometer: %s\n", a_plist[0].SerialNumber );

    err = AVS_Deactivate(handle_);

    AVS_Done();
    std::cout <<  "Test Done" << std::endl;
    
  }


  // Reads the spectrum with the setup handle. First calls AVS_Measure which starts the read and then waits until a spectrum is ready. Then reads
  double* Spectrometer::ReadSpectrum() {
    // DEBUG code - for testing with the spectrometer test unit

    // TODO: Remove magic number
    double spectrum[2048];
    unsigned int ticks_count = 5;
    unsigned int* ticks_count_pointer = &ticks_count;
    std::cout << "Measure: " << AVS_Measure(handle_,0,1) << std::endl;
    std::cout << "Starting measurement" << std::endl;
    while (!AVS_PollScan(handle_)) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      AVS_GetScopeData(handle_,ticks_count_pointer,spectrum);

    }
    
    return spectrum;


  }
  
}
