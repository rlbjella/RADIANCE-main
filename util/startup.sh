#!/bin/sh

sudo service watchdog start

sudo mkdir -p /mnt/mlcdrive1/images
sudo mkdir -p /mnt/mlcdrive2/images
sudo /home/pi/RADIANCE-main/radiance
