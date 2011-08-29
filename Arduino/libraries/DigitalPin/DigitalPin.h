/**
  DigitalPin.h - Librarie pour gestion de la sortie d'une broche.

  @author :     Grégory Fromain, < gregoryfromain@gmail.com >
  @since : 	    04/011/2011
  @license :    http://creativecommons.org/licenses/by-nc/3.0/
  @link :       https://github.com/greg06/Baba-Robot
*/

#ifndef DigitalPin_h
#define DigitalPin_h

#include "WProgram.h"

#define ON           1
#define OFF          0

class DigitalPin
{
  public:
    DigitalPin();
	void init(byte pin);
    void action(byte val_action);
    void clignotte(int nombre_clignottement);
  private:
    byte _pin;
};

#endif