#include <pigpio.h>
#include "heatercontrol.h"

namespace RADIANCE{

  // Initialize the heater, the argument is the GPIO pin. The heater
  // control is actually a PWM signal to a mosfet controlling the
  // heater. Therefore, turning the PWM signal on and off turns the
  // heater on and off.
  HeaterControl::HeaterControl(int gpio_pin):gpio_pin_(gpio_pin) {
    gpioSetMode(gpio_pin_,PI_OUTPUT);
    is_heater_on_ = false;
  }

  // Turn the heater on
  void HeaterControl::CommandHeaterOn() {
    gpioPWM(gpio_pin_,kPwmHeaterOn);
    is_heater_on_ = true;
  }

  // Turn the heater off
  void HeaterControl::CommandHeaterOff() {
    gpioPWM(gpio_pin_,kPwmHeaterOff);
    is_heater_on_ = false;
  }

  // Return heater status
  bool HeaterControl::IsHeaterOn() {return is_heater_on_;}
}
