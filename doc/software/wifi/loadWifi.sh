#!/bin/bash

#Copie des fichiers de configuration du wifi
cp --force wpa_supplicant.conf /etc/wpa_supplicant.conf
cp --force interfaces /etc/network/interfaces
#Activation du wifi.
sudo ifup wlan0
