Configuration du wifi
==========

## Dongle wifi
Baba est connecté sur internet en wifi. Il utilise pour cela un dongle trenet N150.

## Chargement du wifi
Pour que le wifi soit pris en charge il suffit de copier les fichiers de configuration
et activer le wlan.

Executer le script :
``` bash
   bash ~/Baba-Robot/doc/software/wifi/loadWifi.sh
```

Vous devez maintenant mettre le SSID et mot de passe de votre reseau dans le fichier
de config. Le premier exemple permet une connexion en WPA, le 2eme exemple en WEP.

Editer le fichier de config :
``` bash
   sudo nano /etc/wpa_supplicant.conf
```

Il reste maintenant à activer le wifi et rebooter la carte.
``` bash
   sudo ifup wlan0
   sudo reboot
```

## Utile
Pour connaitre l'ip de vos differentes sorties reseau :
``` bash
   ifconfig
```