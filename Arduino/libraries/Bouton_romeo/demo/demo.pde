/**
  demo.pde - Permet de tester la classe Bouton_romeo.

  @author :     Grégory Fromain, < gregoryfromain@gmail.com >
  @since : 	    04/01/2011
  @license :    http://creativecommons.org/licenses/by-nc/3.0/
  @link :       https://github.com/greg06/Baba-Robot
*/

#include <Bouton_romeo.h>

Bouton_romeo bouton_baba;

char numero_du_bouton = -1;

void setup()
{
	Serial.begin(9600);
	bouton_baba.init();
}

void loop()
{
    if(bouton_baba.changement_etat_bouton())
    {
		numero_du_bouton = bouton_baba.numero_bouton();
        switch(bouton_baba.numero_bouton())
        {
            case BOUTON_S1:
                Serial.println("Pression sur S1");
                break;
				
            case BOUTON_S2:
                Serial.println("Pression sur S2");
                break;
				
			case BOUTON_S3:
                Serial.println("Pression sur S3");
                break;
				
			case BOUTON_S4:
                Serial.println("Pression sur S4");
                break;
			
			case BOUTON_S5:
                Serial.println("Pression sur S5");
                break;
				
			case AUCUN_BOUTON_ACTIF:
                Serial.println("Relachement du bouton");
                break;
				
			default:
				Serial.println("Erreur Bouton");
                break;
        }
    }
}