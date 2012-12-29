/**
  demo.pde - Permet de tester la tourelle.

  @author :     Grégory Fromain, < gregoryfromain@gmail.com >
  @since : 	    27/07/2011
  @license :    http://creativecommons.org/licenses/by-nc/3.0/
  @link :       https://github.com/greg06/Baba-Robot
*/

#include <Servo.h>
#include <Tourelle.h>

int delai_pos = 0;

Tourelle tourelle_us;

void setup()
{
	tourelle_us.reset();
}

void loop()
{
	delay(delai_pos);
	delai_pos = tourelle_us.deplacement(110, 110);
	delay(delai_pos);
	delai_pos = tourelle_us.deplacement(80, 80);
}