#include <array>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include <pigpio.h>
#include "attitudesensor.h"

namespace RADIANCE {
  // Configure GPIO pins for CS and set high,
  // open SPI device. Set feedback resistances and ADC resolution
  AttitudeSensor::AttitudeSensor(){

    // Configure gpio MIGHT BE DONE ALREADY
    gpioInitialise();
    // Configure pins as output
    gpioSetMode(12, PI_OUTPUT);
    gpioSetMode(16, PI_OUTPUT);
    gpioSetMode(20, PI_OUTPUT);
    gpioSetMode(21, PI_OUTPUT);

    // Set CS pins high
    gpioWrite(12, 1);
    gpioWrite(16, 1);
    gpioWrite(20, 1);
    gpioWrite(21, 1);

    std::ifstream spidev;
    spidev.open("/dev/spidev0.0");

    // Construct SPI device for 1MHz and 8 bit words
    // If unsuccessful, do nothing
    if (!spidev.good()) {
    *adc_ = ltc2470("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);
    } else {
      adc_ = 0;
    }
  }

  // Returns the attitude angle
  // Returns false if the read failed
  bool AttitudeSensor::ReadAttitude(std::array<float,kNumPhotodiodes>& f_current){

    for (int i = 0; i < kNumPhotodiodes-1; i ++) {
      f_current[i] = ReadAdc(i);
    }

  }

  // Function to read current from a specified photodiode
  float AttitudeSensor::ReadAdc(unsigned char pdiode){
    unsigned int dn = 0;
    float current = 0;
    unsigned int rf;	// Feedback resistance

    // Set necessary CS pin low to make corresponding ADC listen
    if(pdiode == 0){
      gpioWrite(12, 0);
      rf = kResistorValue1;
    }
    else if(pdiode == 1){
      gpioWrite(16, 0);
      rf = kResistorValue2;
    }
    else if(pdiode == 2){
      gpioWrite(20, 0);
      rf = kResistorValue3;
    }
    else {
      gpioWrite(21, 0);
      rf = kResistorValue4;
    } 
    

    // Construct the data register
    unsigned char data[3] = {1, // Start bit
                             0b10000000, // Single-ended mode, channel 0
                             0};         // Unused byte


    // Call the read/write function of SPI object to get AD conversion
    if (!adc_) {
      throw std::runtime_error("Could not find ADC");
    }

    adc_->spiWriteRead(data, sizeof(data));


    // Get result from data registers
    dn = (data[1] << 8) & 0b1100000000;
    dn |= (data[2] & 0xff);

    // Convert DN to current
    current = (dn * this->kReferenceVoltage / ((float)(kAdcResolution))) / ((float)(rf));

    // Set necessary CS pin high again
    if(pdiode == 1){
      gpioWrite(12, 1);
    }
    else if(pdiode == 2){
      gpioWrite(16, 1);
    }
    else if(pdiode == 2){
      gpioWrite(20, 1);
    }
    else if(pdiode == 2){
      gpioWrite(21, 1);
    }
    return current;
  }

}
