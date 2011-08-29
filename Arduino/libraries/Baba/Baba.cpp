/**
  Baba.cpp - Librarie pour gestion complete du robot.

  @author :     Grégory Fromain, < gregoryfromain@gmail.com >
  @since : 	    03/08/2011
  @license :    http://creativecommons.org/licenses/by-nc/3.0/
  @link :       https://github.com/greg06/Baba-Robot
*/

#include "WProgram.h"
#include "Baba.h"
#include "../Moteur_cc/Moteur_cc.h"
#include "../DigitalPin/DigitalPin.h"

Baba::Baba()
{

}

//Initialisation de baba.
void Baba::init()
{
	eclairage.init(PIN_LUMIERE);
}

void Baba::lumiere( byte action)
{
	eclairage.action(action);
}