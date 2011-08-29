/**
  Baba.h - Librarie pour gestion complete du robot.

  @author :     Grégory Fromain, < gregoryfromain@gmail.com >
  @since : 	    03/08/2011
  @license :    http://creativecommons.org/licenses/by-nc/3.0/
  @link :       https://github.com/greg06/Baba-Robot
*/

#ifndef Baba_h
#define Baba_h

#include "WProgram.h"
#include "../Moteur_cc/Moteur_cc.h"
#include "../DigitalPin/DigitalPin.h"

// déclaration des broches.
#define PIN_LUMIERE           		8
#define PIN_TEMPERATURE       		3
#define PIN_MOTEUR_DROITE_SENS      7
#define PIN_MOTEUR_DROITE_VITESSE   6
#define PIN_MOTEUR_GAUCHE_SENS      4
#define PIN_MOTEUR_GAUCHE_VITESSE   5

// declaration de mot cles pour le deplacement de baba.
#define STOP						0
#define AVANCE_NORMAL				30
#define AVANCE_RAPIDE				100
#define RECULE_NORMAL				-30
#define RECULE_RAPIDE				-100

// Mot cles pour la gestion de la trame.
// Détail des adresses.
#define ADRESSE_LUMIERE				'l' 	// attention c'est bien un L minuscule
#define ADRESSE_MOTEUR_DROITE		'd'
#define ADRESSE_MOTEUR_GAUCHE		'g'
#define ADRESSE_TEMPERATURE			't'
#define ADRESSE_TOURELLE			'x'

class Baba
{
  public:
    Baba();
    void init();
	void deplacement(char vitesse_gauche, char moteur_droite);
	void lumiere( byte action);
	
  private:
  Moteur_cc moteur_droite;
  Moteur_cc moteur_gauche;
  DigitalPin eclairage;
};

#endif