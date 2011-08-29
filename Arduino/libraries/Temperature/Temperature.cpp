/*
  DigitalPin.cpp - Librarie pour gestion de la sortie d'une broche.
  Crée par Grégory Fromain, 04/01/2011.
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