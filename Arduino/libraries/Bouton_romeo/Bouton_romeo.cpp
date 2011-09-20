/**
  Bouton_romeo.cpp - Librarie pour gestion des boutons S1 à S5 sur la carte roméo.

  @author :     Grégory Fromain, < gregoryfromain@gmail.com >
  @since : 	    04/01/2011
  @license :    http://creativecommons.org/licenses/by-nc/3.0/
  @link :       https://github.com/greg06/Baba-Robot
*/

#include "WProgram.h"
#include "Bouton_romeo.h"

/**
 Permet d'initialiser les valeurs par defaut.
 @param aucun
 @return rien
*/
Bouton_romeo::Bouton_romeo()
{
	char _val_touche_precedente = -1;
	char _val_toucle = -1;
	
}

/**
 Permet de détécter le changement d'etat d'un interrupteur.
 @param aucun
 @return un bool, TRUE si changement d'etat ou FALSE si aucun changement d'etat. 
*/
bool Bouton_romeo::changement_etat_bouton()
{
	_val_toucle = touche_active();
	if(_val_toucle != _val_touche_precedente)
	{
		delay(50);  										// Permet de controler d'eventuel rebont élétrique
		_val_toucle = touche_active();
		if(_val_toucle != _val_touche_precedente) 			//2eme controle pour valider l'action
		{
			_val_touche_precedente = _val_toucle;
			return true;
		}
	}
	return false;
}

/**
 Permet de retourner quel bouton est préssé.
 @param aucun
 @return un byte, qui renvoit le numéro du bouton en dehort de la methode
*/
char Bouton_romeo::numero_bouton()
{
	return _val_toucle + DEBUT_ASCII_NUM;
}

/**
 Convertie la valeur de l'entrée analogique en numéro de touche appuyé
 @param aucun
 @return un byte, qui indique le numéro du bouton 
*/
byte Bouton_romeo::touche_active() 
{ 
	int  _val_analogique_touche[5] = {30, 150, 360, 535, 760 };
	
	int val_pin_bouton = analogRead(PIN_BOUTON_ROMEO);    		// Lire la valeur de l'entrée analogique
	
	for (int k = 0; k < NOMBRE_DE_BOUTON; k++) 
	{ 
		if (val_pin_bouton < _val_analogique_touche[k]) 
		{			
			return k;	//Termine la fonction en cours et renvoie la valeur de k
		}	
	}
	
	return AUCUN_BOUTON_ACTIF - DEBUT_ASCII_NUM; 				// Aucune touche pressé ou relachement	
}