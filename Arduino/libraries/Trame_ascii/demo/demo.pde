/**
  demo.pde - Permet de tester la classe trame_ascii

  @author :     Grégory Fromain, < gregoryfromain@gmail.com >
  @since : 	    27/07/2011
  @license :    http://creativecommons.org/licenses/by-nc/3.0/
  @link :       https://github.com/greg06/Baba-Robot
*/

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