/**
  Baba.cpp - Librarie pour gestion complete du robot.

  @author :     Grégory Fromain < gregoryfromain@gmail.com >
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


  int val_analogique;
  analogReference(DEFAULT);		                        //Utile pour mesurer les entrée analogiques.
  pinMode(PIN_MESURE_BAT, OUTPUT);                    //Activation en entrée de la broche pour mesurer la tension de la batterie.
  for( int i = 0; i < 380; i++)                       //Permet de faire chauffer un peu l'entrée analogique de la batterie...
  {
    val_analogique = analogRead(PIN_MESURE_BAT);
  }
  
  pinMode(PIN_TEMPERATURE, OUTPUT);                    //Activation en entrée de la broche pour mesurer la tension de la batterie.
  for( int i = 0; i < 380; i++)                        //Permet de faire chauffer un peu l'entrée analogique du capteur de temperature...
  {
    val_analogique = analogRead(PIN_TEMPERATURE);
  }  
  
	led_blanche.init(PIN_LED_BLANCHE);
	led_verte.init(PIN_LED_VERTE);
}

int Baba::mesure_batterie()
{
	return int(analogRead(PIN_MESURE_BAT) * COEFFICIENT_BATTERIE);
}

byte Baba::mesure_temperature()
{
  int val = 0;
	for(char i=0; i<10; i++)                             // pour ameliorer la qualité de la mesure on va faire la moyenne de 10 mesure.
	{ 
		val += (5 * analogRead(PIN_TEMPERATURE) * 100 / 1024); 
	}
	return val / 10;
}

void Baba::lumiere( byte action)
{
	led_blanche.action(action);
}

void Baba::lumiere_verte( byte action)
{
	led_verte.action(action);
}
