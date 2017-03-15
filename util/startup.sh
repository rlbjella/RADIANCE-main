#!/bin/sh
mkdir -p /mnt/mlcdrive1 /mnt/mlcdrive2 /mnt/slcdrive; 
sudo mount /dev/sda1 /mnt/mlcdrive1 -o data=journal;
sudo mount /dev/sdb1 /mnt/slcdrive -o data=journal;
sudo mount /dev/sdc1 /mnt/mlcdrive2 -o data=journal;

sudo service watchdog start

sudo /home/pi/RADIANCE-main/radiance
