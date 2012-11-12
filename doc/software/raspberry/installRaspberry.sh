#!/bin/bash

#Configuration de la carte.
#Mise a jour de l'OS
sudo apt-get update && sudo apt-get upgrade

#Pour récupérer beaucoup d’espace disque en supprimant les langues inutilisées
sudo apt-get install localepurge	
sudo localepurge

# extension de la partition
sudo raspi-config
# valider la ligne :  "expand_rootfs      Expand root partition to fill SD card

#Augnentation de la ram pour le processeur (224Mo).
sudo rpi-update
sudo rpi-update 224

#Reboot pour valider toutes les modifications.
sudo reboot