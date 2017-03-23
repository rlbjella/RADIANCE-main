# RADIANCE-main
Software repository for the RADIANCE senior project.

# Configuration
- Ensure the heater and sensor pin numbers are correct
# Requirements
- Install the pigpio, avaspec, and raspicam packages.

- Enable access to I2C, SPI, and 1-Wire via `sudo raspi-config`.

- Copy provided header files onto the Pi.

- Add the following to the cron tab:
```
@reboot sh /home/pi/RADIANCE-main/util/startup.sh &> /home/pi/stdout_pipe
*/5 * * * * /home/pi/RADIANCE-main/util/restart.sh >/dev/null 2>&1
```

- Format the USB drives/slc card as ext4 with maximum write safety.

- Enable the hardware watchdog: https://www.domoticz.com/wiki/Setting_up_the_raspberry_pi_watchdog
# Compilation

To download/compile:
```
git clone https://github.com/JamesPavek/RADIANCE-main.git
cd RADIANCE-main
sudo make
```

# Execution

To run:

```
sudo ./radiance
```