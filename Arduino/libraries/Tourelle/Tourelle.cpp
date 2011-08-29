/**
  Tourelle.cpp - Librarie pour gestion de la tourelle.

  @author :     Grégory Fromain, < gregoryfromain@gmail.com >
  @since : 	    27/07/2011
  @license :    http://creativecommons.org/licenses/by-nc/3.0/
  @link :       https://github.com/greg06/Baba-Robot
*/

#include "WProgram.h"
#include "../../../../libraries/servo/Servo.h"
#include "Tourelle.h"

// Mise en place des limites par defaut.
Tourelle::Tourelle()
{
  _pin_X = SERVO_X_PIN;
  _pos_X_min = SERVO_X_MIN;
  _pos_X_max = SERVO_X_MAX;
  _pos_X_centre = SERVO_X_CENTRE;
	
  _pin_Y = SERVO_Y_PIN;
  _pos_Y = 0;
  _pos_Y_min = SERVO_Y_MIN;
  _pos_Y_max = SERVO_Y_MAX;
  _pos_Y_centre = SERVO_Y_CENTRE;
}

// Positionnement de la tourelle droite et définition des broches.
void Tourelle::init(){
	servo_X.attach(SERVO_X_PIN);
	servo_X.write(SERVO_X_CENTRE);

	servo_Y.attach(SERVO_Y_PIN);
	servo_Y.write(SERVO_Y_CENTRE);   
}

int Tourelle::deplacement(byte angle_X, byte angle_Y)
{
	//Verification de l'angle max
	if(angle_X < _pos_X_min) angle_X = _pos_X_min;
	if(angle_X > _pos_X_max) angle_X = _pos_X_max;
	if(angle_Y < SERVO_Y_MIN) angle_Y = SERVO_Y_MIN;
	if(angle_Y > SERVO_Y_MAX) angle_Y = SERVO_Y_MAX;

	//On determine le temps d'attente pour le microcontroleur pour laisser le
	//servomoteur prendre sa place.
	int delai_x = abs(servo_X.read() - angle_X) * 5;
	int delai_y = abs(servo_Y.read() - angle_Y) * 5;
	if(delai_x < delai_y) delai_x = delai_y;

	servo_X.write(angle_X);
	servo_Y.write(angle_Y);

	return delai_x;
}