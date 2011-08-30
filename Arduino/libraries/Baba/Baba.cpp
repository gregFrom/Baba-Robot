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
	led_blanche.init(PIN_LED_BLANCHE);
	led_verte.init(PIN_LED_VERTE);	
}

void Baba::lumiere( byte action)
{
	led_blanche.action(action);
}

void Baba::lumiere_verte( byte action)
{
	led_verte.action(action);
}