/*
  DigitalPin.cpp - Librarie pour gestion de la sortie d'une broche.
  Crée par Grégory Fromain, 04/01/2011.
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