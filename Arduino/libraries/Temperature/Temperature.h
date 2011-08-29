/**
  Temperature.h - Librarie pour gestion de la temperature.

  @author :     Grégory Fromain, < gregoryfromain@gmail.com >
  @since : 	    27/07/2011
  @license :    http://creativecommons.org/licenses/by-nc/3.0/
  @link :       https://github.com/greg06/Baba-Robot
*/

#ifndef Temperature_h
#define Temperature_h

#include "WProgram.h"

class Temperature
{
	public:
		Temperature(int pin);
		byte prendre();
	private:
		int _pin;
};

#endif