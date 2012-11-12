#!/bin/bash

#Copie des fichiers de configuration du wifi
cp --force ~/Baba-Robot/doc/software/wifi/wpa_supplicant.conf /etc/wpa_supplicant.conf
cp --force ~/Baba-Robot/doc/software/wifi/interfaces /etc/network/interfaces
#Activation du wifi.
sudo ifup wlan0
