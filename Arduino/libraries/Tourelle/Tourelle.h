/*
  Tourelle.h - Librarie pour gestion de la tourelle.
  Crée par Grégory Fromain <gregoryfromain@gmail.com> , 27/07/2011.
*/
#ifndef Tourelle_h
#define Tourelle_h

#include "WProgram.h"


#include "../../../../libraries/servo/Servo.h"

#define SERVO_X_CENTRE        90
#define SERVO_X_MAX        	  165
#define SERVO_X_MIN           10
#define SERVO_X_PIN           10

#define SERVO_Z_CENTRE        90
#define SERVO_Z_MIN           25
#define SERVO_Z_MAX           130
#define SERVO_Z_PIN           9




class Tourelle
{
  public:
    Tourelle();
	void init();
    int deplacement(byte angle_X, byte angle_Z);
  private:
	Servo servo_X;
    byte _pin_X;
	byte _pos_X;
	byte _pos_X_min;	
	byte _pos_X_max;
	byte _pos_X_centre;
	
	Servo servo_Z;
    byte _pin_Z;
	byte _pos_Z;
	byte _pos_Z_min;	
	byte _pos_Z_max;
	byte _pos_Z_centre;	
};

#endif