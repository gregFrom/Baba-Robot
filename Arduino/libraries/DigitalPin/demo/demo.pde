// Par Grégory Fromain <gregoryfromain@gmail.com>
// le : 04/01/2011

// Permet de tester la classe DigitalPin

#include <DigitalPin.h>

#define LUMIERE_PIN           8

DigitalPin lumiere;

void setup()
{
  lumiere.init(LUMIERE_PIN);
  lumiere.etat(ON);
  delay(2000);
  lumiere.etat(OFF);

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
                lumiere.etat(ON);
                break;
            case 'l'://Led Off
                lumiere.etat(OFF);
                break;
        }
    }
}