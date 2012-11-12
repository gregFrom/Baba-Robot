Configuration de la webcam
==========
## Introduction
On va traiter ici uniquement l'installation et l'utilisation de la webcam sans
tarder dans les explications.
Si vous voulez d'avantage de détail sur le sujet, un très bon article existe sur
le [site de Pobot](http://www.pobot.org/Vision-par-webcam-avec-une.html).

Les sources de cette installation sont issus de 
[cette page](http://www.bobtech.ro/tutoriale/raspberry-pi/78-streaming-webcam-in-format-m-jpg-cu-raspberry-pi).

## Branchement
Baba utilise une webcam [Logitech C210](http://www.logitech.com/assets/30154/4/logitech-webcam-c210.png),
elle est branché en direct sur un port usb de la raspberry.

## Installation
Pour installer la webcam il suffit d'executer le script suivant :

Executez le script :
``` bash
   bash ~/Baba-Robot/doc/software/webcam/loadWebcam.sh
```

Configuration de la webcam (port, flux, résolution, nombre d'image), c'est ici :
``` bash
   sudo nano ~/mjpg-streamer/mjpg-streamer.sh
```


## Utilisation
Démarrez le serveur de stream :
``` bash
   ~/mjpg-streamer/mjpg-streamer.sh start
```

Il reste maintenant à lire de flux de votre stream, par exemple de votre navigateur internet :
``` bash
   http://IpRaspberry:8080/?action=stream
```