Configuration du son
==========
## Introduction
On va traiter ici uniquement l'installation et l'utilisation de la synthèse vocal sans
tarder dans les explications.
Si vous voulez d'avantage de détail sur le sujet, un très bon article existe sur
le [site de Pobot](http://www.pobot.org/Synthese-vocale-avec-espeak-et.html).

## Branchement
Baba utilise un ampli sonore, il est branché en direct sur un port jack de la raspberry.

## Installation
Pour installer la synthèse vocal il suffit d'executer le script suivant :

Executez le script :
``` bash
   bash ~/Baba-Robot/doc/software/sound/loadSound.sh
```

## Utilisation
Pour démarrer la synthèse vocal il suffit de saisir cette ligne:
``` bash
   bash ~/Baba-Robot/doc/software/sound/sendSound.sh "Bonjour, je suis Baba."
```