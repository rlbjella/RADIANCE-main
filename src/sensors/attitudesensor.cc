// #include "attitudesensor.h"
// #include "ads_adc.h"
// #include "GPIOclass.h"
#include "attitudesensor.h"
namespace RADIANCE {

  void AttitudeSensor::Initialize() {}
  float AttitudeSensor::ReadAttitude() {return 0;}
}

// namespace RADIANCE{
//   	// TODO(James)
// 	void AttitudeSensor::Initialize() {
//   		// Initialize all pins
// 		GPIOclass* cs0 = new GPIOclass("24");
// 		GPIOclass* cs1 = new GPIOclass("26");
// 		GPIOclass* cs2 = new GPIOclass("38");
// 		GPIOclass* cs3 = new GPIOclass("40");
// 		//GPIOclass* mosi = new GPIOclass("19");
// 		//GPIOclass* miso = new GPIOclass("21");
// 		//GPIOclass* sclk = new GPIOclass("23");

// 		// Enable all pins
// 		cs0->export_gpio();
// 		cs1->export_gpio();
// 		cs2->export_gpio();
// 		cs3->export_gpio();
// 		//mosi->export_gpio();
// 		//miso->export_gpio();
// 		//sclk->export_gpio();

// 		// Set pin directions
// 		cs0->setdir_gpio("out");
// 		cs1->setdir_gpio("out");
// 		cs2->setdir_gpio("out");
// 		cs3->setdir_gpio("out");
// 		//mosi->setdir_gpio("out");
// 		//miso->setdir_gpio("in");
// 		//sclk->setdir_gpio("out");

// 		// Set CS pins to "sleep"
// 		cs0->setval_gpio("1");
// 		cs1->setval_gpio("1");
// 		cs2->setval_gpio("1");
// 		cs3->setval_gpio("1");
// 	}

//   	float AttitudeSensor::ReadAttitude() {
//   		// Initialize current measurements for 16 bit ADC
//   		unsigned short int I1, I2, I3, I4;
//   		// Properties of ADC and amplifier for conversion from DN
//   		float bin_size = 5.0/(2^16);	// 5Vref divided 2^16 bins
//   		unsigned short int feedback = 5000;		// feedback resistance
//   		double f = 1;		// to be determined with actual board
//   		float x, y, theta;		// initialize calculated values

//   		// Create ADC objects (HOW CAN THIS BE MOVED???)
//   		ads_adc adc0("/dev/spidev0.0", SPI_MODE_0, 1000000, 16);
//   		ads_adc adc1("/dev/spidev0.0", SPI_MODE_0, 1000000, 16);
//   		ads_adc adc2("/dev/spidev0.0", SPI_MODE_0, 1000000, 16);
//   		ads_adc adc3("/dev/spidev0.0", SPI_MODE_0, 1000000, 16);

//   		// Successively read each photodiode DN
//   		cs0->setval_gpio("0");	// enable conversion
//   		I1 = 0x00;	// initialize data variable
//  		adc0.spiWriteRead(&I1, sizeof(I1));	// start conversion and store result
//  		cs0->setval_gpio("1");	// stop conversion

//  		cs1->setval_gpio("0");	// enable conversion
//   		I2 = 0x00;	// initialize data variable
//  		adc0.spiWriteRead(&I2, sizeof(I2));	// start conversion and store result
//  		cs1->setval_gpio("1");	// stop conversion

//  		cs2->setval_gpio("0");	// enable conversion
//   		I3 = 0x00;	// initialize data variable
//  		adc0.spiWriteRead(&I2, sizeof(I2));	// start conversion and store result
//  		cs2->setval_gpio("1");	// stop conversion

//  		cs3->setval_gpio("0");	// enable conversion
//   		I4 = 0x00;	// initialize data variable
//  		adc0.spiWriteRead(&I3, sizeof(I3));	// start conversion and store result
//  		cs3->setval_gpio("1");	// stop conversion

//  		// Convert DN to current
//  		I1 = (I1*bin_size)/feedback;
//  		I2 = (I2*bin_size)/feedback;
//  		I3 = (I3*bin_size)/feedback;
//  		I4 = (I4*bin_size)/feedback;

//  		// Convert current to off-sun angle
//  		x = f*((I2+I3)-(I1+I4))/(I1+I2+I3+I4);
//  		y = f*((I2+I3)-(I1+I4))/(I1+I2+I3+I4);
//  		theta = (x^2+y^2)^(1/2);
//   	}
// }
