/**
  demo.pde - Permet de tester la classe Température.

  @author :     Grégory Fromain, < gregoryfromain@gmail.com >
  @since : 	    27/07/2011
  @license :    http://creativecommons.org/licenses/by-nc/3.0/
  @link :       https://github.com/greg06/Baba-Robot
*/

#include <Temperature.h>

#define TEMPERATURE_PIN           3

byte temperature_capteur;

Temperature capt_temp1(TEMPERATURE_PIN);

void setup()
{
    Serial.begin(19200);
}

void loop()
{
    delay(1000);
    temperature_capteur = capt_temp1.prendre();
    Serial.println(temperature_capteur, DEC);
}