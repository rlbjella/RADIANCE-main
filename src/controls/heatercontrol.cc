#include <pigpio.h>
#include "heatercontrol.h"

namespace RADIANCE{
  // Initialize the the internal heaters
  void HeaterControl::Initialize() {
    gpioSetMode(gpio_pin,PI_OUTPUT);
    is_heater_on = false;
  }

  // Turn the heater on or off
  void HeaterControl::CommandHeaterOn() {
    gpioPWM(gpio_pin,kPwmHeaterOn);
    is_heater_on = true;
  }

  // Turn the heater off
  void HeaterControl::CommandHeaterOff() {
    gpioPWM(gpio_pin,kPwmHeaterOff);
    is_heater_on = false;
  }

  // Return heater status
  bool HeaterControl::IsHeaterOn() {return is_heater_on;}
}
