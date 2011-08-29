// Par Grégory Fromain <gregoryfromain@gmail.com>
// le : 27/07/2011
// Permet de tester la tourelle

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