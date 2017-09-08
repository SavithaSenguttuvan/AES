#!/bin/bash

#Kernel build

cd /home/raj/Desktop/AES/HW1/linux-4.12.10/
#Configuration
make defconfig

#Kernel build
make -j2

sudo make modules_install

sudo make install

#Update grub file 
sudo update -grub

#Reboot the file

#sudo reboot