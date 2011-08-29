/*
  Temperature.h - Librarie pour gestion de la temperature.
  Crée par Grégory Fromain <gregoryfromain@gmail.com> , 27/07/2011.
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