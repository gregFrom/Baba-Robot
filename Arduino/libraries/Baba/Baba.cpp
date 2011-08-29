/*
  Moteur_cc.cpp - Librarie pour gestion complete du robot.
  Crée par Grégory Fromain <gregoryfromain@gmail.com> , 04/08/2011.
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