#!/bin/bash

cd ~
sudo aptitude install libv4l-0
ls /dev/video0
wget http://www.bobtech.ro/get?download=36:mjpg-streamer-rpi
mv get\?download\=36\:mjpg-streamer-rpi mjpg-streamer-rpi.tar.gz
tar -zxvf mjpg-streamer-rpi.tar.gz
rm mjpg-streamer-rpi.tar.gz