# RADIANCE-main
Software repository for the RADIANCE senior project.

# Configuration
- Ensure the heater and sensor pin numbers are correct
# Requirements
- Install the pigpio, avaspec, and raspicam packages.

  To install pigpio: http://abyz.co.uk/rpi/pigpio/download.html (after following instructions you can remove master.zip from the Pi)
  
  To install avaspec: anywhere in the directory structure (on the Pi), run: 
  
  ```
  pi@raspberrypi:~ $ wget http://www.jennykampmeier.com/libavs_2.0.1.0_armhf.deb
  ```
  To install raspicam, download file from Sourceforge: https://downloads.sourceforge.net/project/raspicam/raspicam-0.1.6.zip, then follow instructions here: http://www.uco.es/investiga/grupos/ava/node/40

- Enable access to I2C, SPI, and 1-Wire via `sudo raspi-config`.

- Copy provided header files onto the Pi.

- Edit the crontab and add the following two lines beneath the comments (note if you've done a fresh install the crontab won't exist, but it will make one automatically):
  ```
  pi@raspberrypi:~ $ crontab -e
  ```
  ```
  @reboot sh /home/pi/RADIANCE-main/util/startup.sh &> /home/pi/stdout_pipe
  */5 * * * * /home/pi/RADIANCE-main/util/restart.sh >/dev/null 2>&1
  ```
  Note: The second line will cause the RPi to restart every 5 minutes if the RADIANCE software is not running.
  
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
