/**
  Temperature.cpp - Librarie pour gestion de la temperature.

  @author :     Grégory Fromain, < gregoryfromain@gmail.com >
  @since : 	    27/07/2011
  @license :    http://creativecommons.org/licenses/by-nc/3.0/
  @link :       https://github.com/greg06/Baba-Robot
*/

#include "WProgram.h"
#include "Temperature.h"

Temperature::Temperature(int pin)
{
	pinMode(pin, OUTPUT);
	_pin = pin;
	analogReference(DEFAULT);		//Utile pour le capteur de temperature
}

byte Temperature::prendre()
{
	int val = 0;
	for(int i=0; i<10; i++)
	{ 
		val += (5 * analogRead(_pin) * 100 / 1024); 
	}
	return val / 10;
}