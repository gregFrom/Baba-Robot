/**
  Moteur_cc.h - Librarie pour gestion d'un moteur a courant continue.

  @author :     Grégory Fromain, < gregoryfromain@gmail.com >
  @since : 	    03/08/2011
  @license :    http://creativecommons.org/licenses/by-nc/3.0/
  @link :       https://github.com/greg06/Baba-Robot
*/

#ifndef Moteur_cc_h
#define Moteur_cc_h

#include "WProgram.h"

#define SENS_HORAIRE			true
#define INVERSE_SENS_HORAIRE   	false

#define AVANT        			0x10
#define ARRIERE        			0x20
#define FREIN	        		0x30
#define ROUE_LIBRE      		0x40

class Moteur_cc
{
	public:
		Moteur_cc();
		void init(byte pin_direction, byte pin_vitesse, bool sens_horaire);
		void rotation(byte mode, byte vitesse);

	private:
		byte _pin_direction;
		byte _pin_vitesse;
		byte _vitesse;
		bool _marche_avant_sens_horaire;
};

#endif