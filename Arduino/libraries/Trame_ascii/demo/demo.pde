// Par Grégory Fromain <gregoryfromain@gmail.com>
// le : 27/07/2011
// Permet de tester la classe trame_bluetooth

#include <Trame_ascii.h>

Trame_ascii trame_bluetooth;
char data[] = {'t','e','s','t'};

void setup()
{
  trame_bluetooth.init(19200);
}

void loop()
{
  trame_bluetooth.lire_buffer();
  // trame_bluetooth.debug();
  if(trame_bluetooth.disponible())
  {
    Serial.println(trame_bluetooth.adresse(), HEX);
  }
  
  trame_bluetooth.envoi('a','b', data);
}