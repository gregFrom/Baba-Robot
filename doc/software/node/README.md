Utilisation de node.js avec Baba
==========

## Installation de node.js
Avant de pourvoir utiliser node.js, il faut déjà l'installer.
Et puisque rien n'est simple, il n'est pas possible de le récupérer depuis les dépots (car non comptatible avec ARM6)
Il va donc falloir le compiler. La bonne nouvelle c'est que j'ai fait un script qui fait tout le travail.
La mauvaise nouvelle c'est que c'est très long. (prévoir 3 bonnes heures)

Après avoir recupéré les sources, il suffit de lancer la commande suivante :
``` bash
   sudo bash ~/Baba-Robot/doc/software/node/installNode.sh
```
Pour vérifier que node.js est correctement installé :
``` bash
   node -v
```
## Charger le projet node de Baba
Une fois l'installation de node.js est fait, il faut récupérer les dépenses du projet (prévoir 40Mo):
``` bash
   bash ~/Baba-Robot/doc/software/node/loadProject.sh
```
Si tout fonctionne, vous devez voir apparaitre quelques modules dans le dossier 
node_modules dans :
``` bash
cd ~/Baba-Robot/node/ && ls
```