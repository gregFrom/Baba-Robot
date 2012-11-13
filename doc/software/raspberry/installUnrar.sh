#!/bin/bash

#Installation du programme unrar pour raspberry
sudo chmod a+w /etc/apt/sources.list
sudo echo "deb-src http://mirrordirector.raspbian.org/raspbian/ wheezy main contrib non-free rpi" >> /etc/apt/sources.list
sudo chmod go-w /etc/apt/sources.list
sudo apt-get update
sudo apt-get build-dep unrar-nonfree
sudo apt-get source -b unrar-nonfree
sudo dpkg -i unrar*.deb
