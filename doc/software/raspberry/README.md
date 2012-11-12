Configuration du Rapsberry
==========

## Distribution linux
La distribution utilisé pour la rapsberry est Occidentalis V0.2 d'Adafruit.
Il est possible de la récupérer [avec ce lien](http://learn.adafruit.com/adafruit-raspberry-pi-educational-linux-distro/occidentalis-v0-dot-2)
La carte SD utilisé est de 4Go.

Pour la fin de l'instalation de l'OS, il suffit de suivre les indications sur le suite officiel de Raspberry.
[Voila le lien](http://www.raspberrypi.org/downloads) 

## Préparation de la carte
Maintenant que linux tourne sur la carte, nous allons lancer un bash qui permettra 
de realiser les taches suivantes (il peut être utile de jeter un oeil au script):
*  Mise à jour des aptitudes
*  Purge des langues inutilisés (toutes sauf l'anglais, permet de gagner ~40Mo)
*  Extension de la partition
*  Mise à jour de la carte Raspberry.
*  Reboot de la carte pour valider toutes les modifications.

Executer le script :
``` bash
   bash ~/Baba-Robot/doc/software/raspberry/installRaspberry.sh
```