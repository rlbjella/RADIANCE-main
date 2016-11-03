# RADIANCE-main
Software repository for the RADIANCE senior project.

# Downloading/Compilation
To install run git clone on the repository:
```
git clone https://github.com/JamesPavek/RADIANCE-main.git
```
Then install avaspec package:
```
dpkg -i avaspec.so
```
Then to compile:
```
cd RADIANCE-main
make
```

# Installation
Add the executable to be started on boot:

```
mv radiance /etc/init.d/radiance
chmod 755 /etc/init.d/radiance
update-rc.d radiance defaults
```

Enable the hardware watchdog: https://www.domoticz.com/wiki/Setting_up_the_raspberry_pi_watchdog
