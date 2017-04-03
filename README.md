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

- Enable access to I2C, SPI, and 1-Wire via `sudo raspi-config`:
  ```
  pi@raspberrypi:~ $ sudo raspi-config
  ```
  Arrow-down and choose `5 Interfacing Options`. Arrow-down and choose `P1 Camera`. Choose `Yes` when prompted. Repeat for `P4 SPI`, `P5 I2C` and `P7 1-Wire`. When it asks you to reboot, say `Yes`.
  
- Edit the crontab and add the following two lines beneath the comments (note if you've done a fresh install the crontab won't exist, but it will make one automatically):
  ```
  pi@raspberrypi:~ $ crontab -e
  ```
  ```
  @reboot sh /home/pi/RADIANCE-main/util/startup.sh &> /home/pi/stdout_pipe
  */5 * * * * /home/pi/RADIANCE-main/util/restart.sh >/dev/null 2>&1
  ```
  Note: The second line will cause the RPi to restart every 5 minutes if the RADIANCE software is not running.
  
- Mount, format, and configure the USB drives as ext4 and data=journal: 
  ```
  pi@raspberrypi:~ $ sudo nano /etc/fstab
  ```
  Then add the following lines at the end of the document:
  ```
  UUID=3f7681a4-bed7-4bbf-b1fd-966d3cc6f79f    /mnt/slcdrive  ext4  data=journal  0  0
  UUID=5c0d5816-9b30-4041-a98d-71844d1dd6b9    /mnt/mlcdrive1 ext4  data=journal  0  0
  UUID=8f7a6e96-8b9a-428c-bb17-ddd595607f23    /mnt/mlcdrive2 ext4  data=journal  0  0
  ```
  Exit and save the `fstab` file by doing a Ctrl+X, then type "Y" to save. 
  
- Enable the hardware watchdog: https://www.domoticz.com/wiki/Setting_up_the_raspberry_pi_watchdog

# Sync with Git and Compile
To download/compile:
```
pi@raspberrypi:~ $ git clone https://github.com/JamesPavek/RADIANCE-main.git
pi@raspberrypi:~ $ cd RADIANCE-main
pi@raspberrypi:~ $ sudo make
```

# If needed, update RADIANCE software
- Do the following on the Pi:
```
pi@raspberrypi:~ $ cd ~/RADIANCE-main/
pi@raspberrypi:~ $ git reset --hard
pi@raspberrypi:~ $ git pull
```
This will update the software and grab the header files for the `include` folder.


# Execution

To run:

```
sudo ./radiance
```
