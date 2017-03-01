# RADIANCE-main
Software repository for the RADIANCE senior project.

# Requirements
Install the pigpio, avaspec, and raspicam packages.

Enable access to I2C, SPI, and 1-Wire via `sudo raspi-config`.

Copy the RADIANCE-main repository and the provided header files onto the Pi.
# Compilation

To compile:
```
cd RADIANCE-main
make
```
# Installation
- Add the executable to be started on boot:

```
mv radiance /etc/init.d/radiance
chmod 755 /etc/init.d/radiance
update-rc.d radiance defaults
```
- Add a Cron job to check every 5 minutes and reboot if not running:
```
*/5 * * * * /home/pi/RADIANCE-main/util/restart.sh >/dev/null 2>&1
```
- Make sure the partition is formatted with a journaled partition like ext3. The journaling mode should be selected for maximum write safety.

- Enable the hardware watchdog: https://www.domoticz.com/wiki/Setting_up_the_raspberry_pi_watchdog

- Mount the USB drive(s) with journaling and sync enabled
