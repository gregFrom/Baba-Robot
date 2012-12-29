/**
  Bouton_romeo.h - Librarie pour gestion de la sortie d'une broche.

  @author :     Grégory Fromain, < gregoryfromain@gmail.com >
  @since : 	    04/011/2011
  @license :    http://creativecommons.org/licenses/by-nc/3.0/
  @link :       https://github.com/greg06/Baba-Robot
*/

#ifndef Bouton_romeo_h
#define Bouton_romeo_h

#include "Arduino.h"

#define PIN_BOUTON_ROMEO	7
#define NOMBRE_DE_BOUTON	5
#define AUCUN_BOUTON_ACTIF	'!'
#define BOUTON_S1			'1'
#define BOUTON_S2			'2'
#define BOUTON_S3			'3'
#define BOUTON_S4			'4'
#define BOUTON_S5			'5'
#define DEBUT_ASCII_NUM		49

class Bouton_romeo
{
  public:
    Bouton_romeo();
	bool changement_etat_bouton();
	char numero_bouton();
  private:
	byte touche_active();
	char _val_touche_precedente;
	char _val_toucle;
	int  _val_analogique_touche[]; 
};

#endif