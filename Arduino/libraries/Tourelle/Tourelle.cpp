/*
  DigitalPin.cpp - Librarie pour gestion de la sortie d'une broche.
  Crée par Grégory Fromain, 04/01/2011.
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
	
  _pin_Z = SERVO_Z_PIN;
  _pos_Z = 0;
  _pos_Z_min = SERVO_Z_MIN;
  _pos_Z_max = SERVO_Z_MAX;
  _pos_Z_centre = SERVO_Z_CENTRE;
}

// Positionnement de la tourelle droite et définition des broches.
void Tourelle::init(){
  servo_X.attach(SERVO_X_PIN);
  servo_X.write(SERVO_X_CENTRE);
  
  servo_Z.attach(SERVO_Z_PIN);
  servo_Z.write(SERVO_Z_CENTRE);   
}

int Tourelle::deplacement(byte angle_X, byte angle_Z)
{
 //Verification de l'angle max
  if(angle_X < _pos_X_min) angle_X = _pos_X_min;
  if(angle_X > _pos_X_max) angle_X = _pos_X_max;
  if(angle_Z < SERVO_Z_MIN) angle_Z = SERVO_Z_MIN;
  if(angle_Z > SERVO_Z_MAX) angle_Z = SERVO_Z_MAX;
  
  //On determine le temps d'attente pour le microcontroleur pour laisser le
  //servomoteur prendre sa place.
  int delai_x = abs(servo_X.read() - angle_X) * 5;
  int delai_y = abs(servo_Z.read() - angle_Z) * 5;
  if(delai_x < delai_y) delai_x = delai_y;
  
  servo_X.write(angle_X);
  servo_Z.write(angle_Z);
  
  return delai_x;
}