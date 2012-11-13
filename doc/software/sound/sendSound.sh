# !/bin/bash

if [ "$#" -ne 1 ]
then
   printf "Param : Il manque le texte à réciter."\n"
else
   espeak -v mb/mb-fr1 "$1" | mbrola /usr/share/mbrola/voices/fr1 - - | aplay -r16000 -fS16
fi
