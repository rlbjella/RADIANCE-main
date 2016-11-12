#include <chrono>
#include <thread>
#include "spectrometer.h"
#include <iostream>
#include <algorithm>
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

    std::cout << "USB spectrometers found: " << AVS_GetNrOfDevices() << std::endl;

    n = AVS_GetList( sizeof(a_plist), &byte_set, a_plist );
    
    int err = 0;

    handle_ = AVS_Activate( &a_plist[0] );

    std::cout << "Test spectrometer: " << a_plist[0].SerialNumber << std::endl;

    AVS_UseHighResAdc(handle_,1);

  }


  // Reads the spectrum with the setup handle. First calls AVS_Measure which starts the read and then waits until a spectrum is ready. Then reads
  double* Spectrometer::ReadSpectrum() {
    // DEBUG code - for testing with the spectrometer test unit

<<<<<<< HEAD
    std::cout << "Measuring" << std::endl;
=======
    // TODO: Remove magic number
    double spectrum[2048];
    unsigned int ticks_count = 5;
    unsigned int* ticks_count_pointer = &ticks_count;
    std::cout << "Measure: " << AVS_Measure(handle_,0,1) << std::endl;
    std::cout << "Starting measurement" << std::endl;
    while (!AVS_PollScan(handle_)) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      AVS_GetScopeData(handle_,ticks_count_pointer,spectrum);
>>>>>>> 7b55c037ec580d0375c9cf8a7874464ba4e187d3

    unsigned short num_pixels;
    if (AVS_GetNumPixels(handle_,&num_pixels)!=ERR_SUCCESS) {
      std::cout << "Err in getting num_pixels: " << AVS_GetNumPixels(handle_,&num_pixels) << std::endl;
    }

    // Configure the measurement
    MeasConfigType meas_config;

    // General parameters
    meas_config.m_StartPixel 			= 0;
    meas_config.m_StopPixel 			= (char) (num_pixels - 1);
    meas_config.m_IntegrationTime		= 100;
    meas_config.m_IntegrationDelay		= 0;
    meas_config.m_NrAverages			= 1;

    // Dark correction
    meas_config.m_CorDynDark.m_Enable	= 0; // Enable dark correction
    meas_config.m_CorDynDark.m_ForgetPercentage = 0; // Percentage of the new dark value pixels that has to be used


    // Smoothing
    meas_config.m_Smoothing.m_SmoothPix = 0; // Number of neighbor pixels used for smoothing
    meas_config.m_Smoothing.m_SmoothModel	= 0; // Only one model available(0)

    // Saturation Detection
    meas_config.m_SaturationDetection	= 0; // Saturation detection, 0 is disabled

    // Trigger modes
    meas_config.m_Trigger.m_Mode		= 0; // Mode, 0 is software
    meas_config.m_Trigger.m_Source		= 0; // Source, 0 is external trigger
    meas_config.m_Trigger.m_SourceType	= 0; // Source type, 0 is edge trigger

    // Control settings
    meas_config.m_Control.m_StrobeControl	= 0; // Number of strobe pulses during integration, 0 is no strobe pulses
    meas_config.m_Control.m_LaserDelay		= 0; // Laser delay since trigger(unit is FPGA clock cycles)
    meas_config.m_Control.m_LaserWidth		= 0; // Laser pulse width(unit is FPGA clock cycles), 0 is no laser pulse
    meas_config.m_Control.m_LaserWaveLength	= 1; // Peak wavelength of laser(nm), used for Raman spectroscopy
    meas_config.m_Control.m_StoreToRam			= 0; // Number of spectra to be store to RAM
    
    if (AVS_PrepareMeasure(handle_,&meas_config)!=ERR_SUCCESS) {
      std::cout << "Err in PrepareMeasure" << std::endl;
    }

    if (AVS_Measure(handle_,0,1)!=ERR_SUCCESS) {
      std::cout << "Err in Measure" << std::endl;
    }

    while (AVS_PollScan(handle_)!=1) {
      // std::cout << "Waiting for measurement" << std::endl; // DEBUG
      std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }

    double spectrum[num_pixels];

    // Time since the spectrometer started(10 microsecond units)
    unsigned int ticks;

    std::fill_n(spectrum,num_pixels,0.0);

    if (AVS_GetScopeData(handle_,&ticks,spectrum)!=ERR_SUCCESS) {
      std::cout << "Err in GetScopeData" << std::endl;
    }

    std::cout << std::endl;

    return spectrum;


  }
  
}
