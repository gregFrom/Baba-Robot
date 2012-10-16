/**
  Moteur_cc.cpp - Librarie pour gestion d'un moteur a courant continue.

  @author :     Grégory Fromain, < gregoryfromain@gmail.com >
  @since : 	    03/08/2011
  @license :    http://creativecommons.org/licenses/by-nc/3.0/
  @link :       https://github.com/greg06/Baba-Robot
*/

#include "Arduino.h"
#include "Moteur_cc.h"

Moteur_cc::Moteur_cc()
{
	_vitesse = 0;	
}

//Initialisation des broches du moteur.
void Moteur_cc::init(byte pin_direction, byte pin_vitesse, bool sens_horaire)
{
	_pin_direction = pin_direction;
	_pin_vitesse = pin_vitesse;
	_marche_avant_sens_horaire = sens_horaire;
	
	pinMode(_pin_direction, OUTPUT);
	pinMode(_pin_vitesse, OUTPUT);
	
	digitalWrite(_pin_vitesse,LOW);						// On active le frein.
	digitalWrite(_pin_direction,LOW);
}

void Moteur_cc::rotation(byte mode, byte vitesse)
{
	switch (mode) // Mode de déplacement.
	{ 							
		case AVANT:
			analogWrite (_pin_vitesse, vitesse);
			digitalWrite(_pin_direction, _marche_avant_sens_horaire); 
			break;
			
		case ARRIERE:
			analogWrite (_pin_vitesse, vitesse);
			digitalWrite(_pin_direction, !_marche_avant_sens_horaire); 
			break;

		case ROUE_LIBRE:
			digitalWrite(_pin_vitesse,LOW);
			digitalWrite(_pin_direction,LOW);
			break;
/*
		case FREIN:
			digitalWrite(_pin_vitesse,HIGH);
			digitalWrite(_pin_direction,HIGH);
			break;
*/
		default:
			// si aucune condition n'est vraie, on passe en roue libre.
			digitalWrite(_pin_vitesse,LOW);
			digitalWrite(_pin_direction,LOW);
	}
}