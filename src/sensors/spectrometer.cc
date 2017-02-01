#include <chrono>
#include <thread>
#include "spectrometer.h"
#include <iostream>
#include <algorithm>
#include <cmath>
namespace RADIANCE{

  // Setup and configure the spectrometer
  // Start by finding and retrieving the spectrometer handle, then configuring the measurements
  void Spectrometer::Initialize() {

    // Init the library, the parameter is type of interface.
    // 0 for USB
    int n = AVS_Init(0);

    // Find available devices
    std::cout << "USB spectrometers found: " << AVS_GetNrOfDevices() << std::endl; // DEBUG

    // Parameters for calling AVS_GetList()
    unsigned int byte_set;
    AvsIdentityType a_plist[30];
    n = AVS_GetList(sizeof(a_plist), // Number of bytes of list data
                    &byte_set, // Number of bytes needed to store information
                    a_plist);    // Pointer to storage of identity information;

    // Retrieve handle
    handle_ = AVS_Activate(&a_plist[0]);

    // Set the ADC to high res mode
    AVS_UseHighResAdc(handle_,1);

    // Retrieve number of pixels
    unsigned short num_pixels;
    if (AVS_GetNumPixels(handle_,&num_pixels)!=ERR_SUCCESS) {
      std::cout << "Err in getting num_pixels" << std::endl; // DEBUG
    }

  }

  // Reads the spectrum with the setup handle. First calls AVS_Measure
  // which starts the read and then waits until a spectrum is
  // ready. Then reads and converts to float array for storage
  float* Spectrometer::ReadSpectrum() {

    // Configure the measurement
    // TODO Make measurement config its own function
    MeasConfigType meas_config;

    // General parameters
    meas_config.m_StartPixel      = 0;
    meas_config.m_StopPixel       = (num_pixels - 1);
    meas_config.m_IntegrationTime   = 100;
    meas_config.m_IntegrationDelay    = 0;
    meas_config.m_NrAverages      = 1;

    // Dark correction
    meas_config.m_CorDynDark.m_Enable = 0; // Enable dark correction
    meas_config.m_CorDynDark.m_ForgetPercentage = 0; // Percentage of the new dark value pixels that has to be used


    // Smoothing
    meas_config.m_Smoothing.m_SmoothPix = 0; // Number of neighbor pixels used for smoothing
    meas_config.m_Smoothing.m_SmoothModel = 0; // Only one model available(0)

    // Saturation Detection
    meas_config.m_SaturationDetection = 0; // Saturation detection, 0 is disabled

    // Trigger modes
    meas_config.m_Trigger.m_Mode    = 0; // Mode, 0 is software
    meas_config.m_Trigger.m_Source    = 0; // Source, 0 is external trigger
    meas_config.m_Trigger.m_SourceType  = 0; // Source type, 0 is edge trigger

    // Control settings
    meas_config.m_Control.m_StrobeControl = 0; // Number of strobe pulses during integration, 0 is no strobe pulses
    meas_config.m_Control.m_LaserDelay    = 0; // Laser delay since trigger(unit is FPGA clock cycles)
    meas_config.m_Control.m_LaserWidth    = 0; // Laser pulse width(unit is FPGA clock cycles), 0 is no laser pulse
    meas_config.m_Control.m_LaserWaveLength = 1; // Peak wavelength of laser(nm), used for Raman spectroscopy
    meas_config.m_Control.m_StoreToRam      = 0; // Number of spectra to be store to RAM

    // Configure the spectrometer with the measurement config
    if (AVS_PrepareMeasure(handle_,&meas_config)!=ERR_SUCCESS) {
      std::cout << "Err in PrepareMeasure" << std::endl; //DEBUG
    }
    // Signal to start the measurement
    if (AVS_Measure(handle_,0,1)!=ERR_SUCCESS) {
      std::cout << "Err in Measure" << std::endl; //DEBUG
    }

    // Wait for the measurement to complete
    while (AVS_PollScan(handle_)!=1) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    // Get spectrum from device
    if (AVS_GetLambda(handle_,d_spectrum)!=ERR_SUCCESS) {
      std::cout << "Err in GetScopeData" << std::endl; //DEBUG
    }

    // Convert spectrum to floats for storage efficiency
    for (int i=0; i < num_pixels; i++) {
      f_spectrum[i] = (float) d_spectrum[i];
    }
    return f_spectrum;

  }

  // Returns num_pixels
  int Spectrometer::GetNumPixels() {
    return num_pixels;
  }

  // Returns spectrometer internal temperature
  float Spectrometer::ReadSpectrometerTemperature() {

    // Read the temperature as voltage
     float voltage;
     AVS_GetAnalogIn(handle_,   // Spectrometer handle
                     0, // Which input to use; 0 is the detector temperature
                     &voltage); // Return value

     // Need to convert the result to an actual measurement
     return Spectrometer::ConvertVoltageToTemperature(voltage);
  }
  // Converts the voltage into a temperature using a polynomial
  float Spectrometer::ConvertVoltageToTemperature(float voltage) {
    return 118.69 - 70.361*(voltage)+ 21.02*std::pow(voltage,2) - 3.6443*std::pow(voltage,3) + 0.1993*std::pow(voltage,4);

  }
}

