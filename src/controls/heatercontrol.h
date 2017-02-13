#ifndef RADIANCE_SRC_HEATERCONTROL_H_
#define RADIANCE_SRC_HEATERCONTROL_H_

// Heater on and off values range between 1-1024
#define PWM_HEATER_OFF 0
#define PWM_HEATER_ON 1023
namespace RADIANCE {

  // Class for initializing and commanding the internal heaters
  class HeaterControl {

  public:

    // New
    HeaterControl(int agpio_pin):gpio_pin(agpio_pin){}

    // Initialize the the internal heaters
    void Initialize();

    // Turn the heater on or off
    void CommandHeaterOn();

    // Turn the heater off
    void CommandHeaterOff();

    bool IsHeaterOn();
  private:
    int gpio_pin;
    bool is_heater_on;

  };

}
#endif // RADIANCE_SRC_HEATERCONTROL_H_
