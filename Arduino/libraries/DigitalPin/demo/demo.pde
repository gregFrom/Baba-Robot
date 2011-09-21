/**
  demo.pde - Permet de tester la classe DigitalPin.

  @author :     Grégory Fromain, < gregoryfromain@gmail.com >
  @since : 	    04/01/2011
  @license :    http://creativecommons.org/licenses/by-nc/3.0/
  @link :       https://github.com/greg06/Baba-Robot
*/

#include <DigitalPin.h>

#define LUMIERE_PIN           8

DigitalPin lumiere;

void setup()
{
	lumiere.init(LUMIERE_PIN);
	lumiere.action(ON);
	delay(2000);
	lumiere.action(OFF);
	Serial.begin(9600);      //Set Baud Rate
}

void loop()
{
    char val = Serial.read();
    if(val!=-1)
    {
        switch(val)
        {
            case 'L'://Led On
                lumiere.action(ON);
                break;
            case 'l'://Led Off
                lumiere.action(OFF);
                break;
        }
    }
}
