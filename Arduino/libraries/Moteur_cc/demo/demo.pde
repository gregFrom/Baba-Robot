// Par Grégory Fromain <gregoryfromain@gmail.com>
// le : 03/08/11
// Permet de tester la classe Moteur_cc

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