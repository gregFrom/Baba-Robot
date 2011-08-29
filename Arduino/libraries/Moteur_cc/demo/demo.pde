/**
  demo.pde - Permet de tester la classe Moteur_cc

  @author :     Grégory Fromain, < gregoryfromain@gmail.com >
  @since : 	    03/08/2011
  @license :    http://creativecommons.org/licenses/by-nc/3.0/
  @link :       https://github.com/greg06/Baba-Robot
*/

#include <Moteur_cc.h>

#define PIN_VITESSE     6
#define PIN_SENS        7
#define VITESSE_PWM     100

Moteur_cc moteur_droite;

void setup()
{
    moteur_droite.init(PIN_SENS, PIN_VITESSE, SENS_HORAIRE);
}

void loop()
{
    moteur_droite.rotation(AVANT, VITESSE_PWM);
    delay(2000);
    moteur_droite.rotation(ROUE_LIBRE, VITESSE_PWM);
    delay(2000);
    moteur_droite.rotation(ARRIERE, VITESSE_PWM); 
    delay(2000);
    moteur_droite.rotation(ROUE_LIBRE, VITESSE_PWM);
    delay(2000);
}