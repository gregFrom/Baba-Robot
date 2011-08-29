// Par Grégory Fromain <gregoryfromain@gmail.com>
// le : 27/07/2011
// Permet de tester la classe Température

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