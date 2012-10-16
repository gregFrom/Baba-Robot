/**
  DigitalPin.cpp - Librarie pour gestion de la sortie d'une broche.

  @author :     Grégory Fromain, < gregoryfromain@gmail.com >
  @since : 	    04/01/2011
  @license :    http://creativecommons.org/licenses/by-nc/3.0/
  @link :       https://github.com/greg06/Baba-Robot
*/

#include "Arduino.h"
#include "DigitalPin.h"

DigitalPin::DigitalPin()
{

}

void DigitalPin::init(byte pin)
{
	pinMode(pin, OUTPUT);
	_pin = pin;
}

void DigitalPin::action(byte val_action)
{
	if((val_action == 0) || (val_action == 1))
	{
		digitalWrite(_pin, val_action);
	}
	else
	{
		/* // Ne marche pas... :o(
		tone(_pin, 1), val_action * 1000);	// X 1000 pour la conversion de ms à sec.
		*/
	}
}

void DigitalPin::clignotte(int nombre_clignottement)
{
	for(int i=1; i<=nombre_clignottement; i++)
	{
		digitalWrite(_pin,ON);
		delay(200);
		digitalWrite(_pin,OFF);
		delay(200);
	}
}