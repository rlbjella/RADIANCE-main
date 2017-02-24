#ifndef RADIANCE_SRC_CONTROLS_HEATERCONTROL_H_
#define RADIANCE_SRC_CONTROLS_HEATERCONTROL_H_

namespace RADIANCE {

  // Class for initializing and commanding the internal heaters
  class HeaterControl {

  public:

    // Initialize the heater with the gpio pin as argument
    HeaterControl(int agpio_pin):gpio_pin(agpio_pin){}

    // Initialize the the internal heaters
    void Initialize();

    // Turn the heater on or off
    void CommandHeaterOn();

    // Turn the heater off
    void CommandHeaterOff();

    // Return heater status
    bool IsHeaterOn();
  private:
    // The heater GPIO pin number, passed into the constructor
    const int gpio_pin;

    // Current heater status
    bool is_heater_on;

    // The heater on and off values range between 0 and 255
    const int kPwmHeaterOff{0};
    const int kPwmHeaterOn{255};

  };

}
#endif // RADIANCE_SRC_CONTROLS_HEATERCONTROL_H_
