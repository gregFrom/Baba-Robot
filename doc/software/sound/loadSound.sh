#!/bin/bash

# Vérification de unrar
[[ -z $(which unrar-nonfree) ]] && bash ~/Baba-Robot/doc/software/raspberry/installUnrar.sh

# Installation de espeak
sudo apt-get install espeak

# Installation de mbrola
wget http://tcts.fpms.ac.be/synthesis/mbrola/bin/armlinux/mbrola.rar
sudo apt-get install unrar
unrar e mbrola.rar
sudo mv mbrola /usr/bin
sudo chmod 777 /usr/bin/mbrola

# Il faut également télécharger une voix française
sudo mkdir /usr/share/mbrola 
sudo mkdir /usr/share/mbrola/voices
wget http://tcts.fpms.ac.be/synthesis/mbrola/dba/fr1/fr1-990204.zip
unzip fr1*.zip
sudo mv fr1/fr1 /usr/share/mbrola/voices/

# On supprime les fichiers d'installation.
rm mbrola.rar
rm fr1-990204.zip
sudo rm -f -r unrar*
rm -f -r tmp
rm -f -r fr1
