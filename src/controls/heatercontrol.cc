#include <wiringPi.h>
#include "heatercontrol.h"

namespace RADIANCE{
  // TODO(James)
  // Initialize the the internal heaters
  void HeaterControl::Initialize() {
    wiringPiSetup();
    pinMode(gpio_pin,PWM_OUTPUT);
    is_heater_on = false;
  }

  // Turn the heater on or off
  void HeaterControl::CommandHeaterOn() {
    pwmWrite(gpio_pin,PWM_HEATER_ON);
    is_heater_on = true;
  }

  // Turn the heater off
  void HeaterControl::CommandHeaterOff() {
    pwmWrite(gpio_pin,PWM_HEATER_OFF);
    is_heater_on = false;
  }

  bool HeaterControl::IsHeaterOn() {return is_heater_on;}
}
