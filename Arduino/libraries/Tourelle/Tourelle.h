/**
  Tourelle.h - Librarie pour gestion de la tourelle.

  @author :     Grégory Fromain, < gregoryfromain@gmail.com >
  @since : 	    27/07/2011
  @license :    http://creativecommons.org/licenses/by-nc/3.0/
  @link :       https://github.com/greg06/Baba-Robot
*/
#ifndef Tourelle_h
#define Tourelle_h

#include "WProgram.h"

#include "../../../../libraries/servo/Servo.h"

#define SERVO_X_CENTRE        90
#define SERVO_X_MAX        	  165
#define SERVO_X_MIN           10
#define SERVO_X_PIN           10

#define SERVO_Y_CENTRE        90
#define SERVO_Y_MIN           25
#define SERVO_Y_MAX           130
#define SERVO_Y_PIN           9

class Tourelle
{
	public:
		Tourelle();
		void init();
		int deplacement(byte angle_X, byte angle_Y);
	private:
		Servo servo_X;
		byte _pin_X;
		byte _pos_X;
		byte _pos_X_min;	
		byte _pos_X_max;
		byte _pos_X_centre;

		Servo servo_Y;
		byte _pin_Y;
		byte _pos_Y;
		byte _pos_Y_min;	
		byte _pos_Y_max;
		byte _pos_Y_centre;	
};

#endif