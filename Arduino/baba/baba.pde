/**
  baba.pde - Permet d'être controler le robot via un téléphone android.

  @author :     Grégory Fromain, < gregoryfromain@gmail.com >
  @since : 	    27/07/2011
  @license :    http://creativecommons.org/licenses/by-nc/3.0/
  @link :       https://github.com/greg06/Baba-Robot
*/

#include <Wire.h>
#include <Servo.h>
#include <DigitalPin.h>
#include <Temperature.h>
#include <Tourelle.h>
#include <Moteur_cc.h>
#include <Baba.h>
#include <Trame_ascii.h>
#include <Bouton_romeo.h>

Baba 		baba;
Temperature capt_temp1(PIN_TEMPERATURE);
Tourelle 	tourelle_us;
Trame_ascii trame_bluetooth;
Moteur_cc 	moteur_droite;
Moteur_cc 	moteur_gauche;
Bouton_romeo bouton_baba;

int mesure_us()
{
  // step 1: instruct sensor to read echoes
  Wire.beginTransmission(112); // transmit to device #112 (0x70)
                               // the address specified in the datasheet is 224 (0xE0)
                               // but i2c adressing uses the high 7 bits so it's 112
  Wire.send(0x00);             // sets register pointer to the command register (0x00)  
  Wire.send(0x51);             // command sensor to measure in "inches" (0x50) 
                               // use 0x51 for centimeters
                               // use 0x52 for ping microseconds
  Wire.endTransmission();      // stop transmitting

  // step 2: wait for readings to happen
  delay(70);                   // datasheet suggests at least 65 milliseconds

  // step 3: instruct sensor to return a particular echo reading
  Wire.beginTransmission(112); // transmit to device #112
  Wire.send(0x02);             // sets register pointer to echo #1 register (0x02)
  Wire.endTransmission();      // stop transmitting

  // step 4: request reading from sensor
  Wire.requestFrom(112, 2);    // request 2 bytes from slave device #112

  // step 5: receive reading from sensor
  int reading = -1;
  if(2 <= Wire.available())    // if two bytes were received
  {
    reading = Wire.receive();  // receive high byte (overwrites previous reading)
    reading = reading << 8;    // shift high byte to be high 8 bits
    reading |= Wire.receive(); // receive low byte as lower 8 bits
  }
return reading;
}

void setup(void)
{
	baba.init();
	moteur_droite.init(PIN_MOTEUR_DROITE_SENS, PIN_MOTEUR_DROITE_VITESSE, SENS_HORAIRE);
	moteur_gauche.init(PIN_MOTEUR_GAUCHE_SENS, PIN_MOTEUR_GAUCHE_VITESSE, SENS_HORAIRE);
	trame_bluetooth.init(9600);
    Wire.begin();                // join i2c bus (address optional for master)
    tourelle_us.init();
    
    for(int i=6;i<=9;i++)
    pinMode(i, OUTPUT);
    
	moteur_droite.rotation(ROUE_LIBRE , STOP);
	moteur_gauche.rotation(ROUE_LIBRE , STOP);
	
	//envoi une info au téléphone pour dire que le robot est prêt.
	trame_bluetooth.envoi(ADRESSE_ETAT_ROBOT, ETAT_INIT_OK, 0);
}
void loop(void)
{
	trame_bluetooth.lire_buffer();
	if(trame_bluetooth.disponible())
	{
		Serial.println(trame_bluetooth.fonction(), DEC);
		
		byte val_fonction = trame_bluetooth.fonction();
		byte val_donnee = trame_bluetooth.donnee();
		switch(trame_bluetooth.adresse())
		{
			case ADRESSE_MOTEUR_DROITE:
				// dans ce cas val_fonction donne le sens du moteur droite.
				// et val_donnee donne la puissance
				moteur_droite.rotation(char(val_fonction), char(val_donnee));
				break;

			case ADRESSE_MOTEUR_GAUCHE:
				// dans ce cas val_fonction donne le sens du moteur Gauche.
				// et val_donnee donne la puissance
				moteur_gauche.rotation(char(val_fonction), char(val_donnee));
				break;

			case ADRESSE_LUMIERE:
				//trame_bluetooth.fonction() doit renvoyer soit 0 (ON) ou 1 (OFF)
				baba.lumiere(val_fonction);
				break;

			case ADRESSE_LUMIERE_VERTE:
				//trame_bluetooth.fonction() doit renvoyer soit 0 (ON) ou 1 (OFF)
				baba.lumiere_verte(val_fonction);
				break;

			case ADRESSE_TEMPERATURE:
				// renvoie la temperature dans une trame bluetooth. (le 3 param est inutile dans ce cas.)
				trame_bluetooth.envoi(ADRESSE_TEMPERATURE, capt_temp1.prendre(), 0);
				break;
				
			case ADRESSE_BOUTON:
				// Il peut être utile que le telephone demande l'etat des boutons
				// Dans ce cas on lui renvoit la trame envoyé lors d'un changement d'etat.
				trame_bluetooth.envoi(ADRESSE_BOUTON, bouton_baba.numero_bouton(), 0);
				break;

			case ADRESSE_ETAT_ROBOT:
				// Permet de faire une test simple entre le tel et le robot.
				if(val_fonction == ETAT_TEST_LIAISON)
				{
					trame_bluetooth.envoi(ADRESSE_ETAT_ROBOT, ETAT_TEST_LIAISON, 0);
				}
				break; 
				
			case ADRESSE_TOURELLE:
				// dans ce cas val_fonction donne la angle dans l'axe X.
				// et val_donnee donne la valeur de l'angle Y.
				int delay_tourelle = tourelle_us.deplacement(val_fonction, val_donnee);
				// On retourne le delais au téléphone (Sa peut etre utile)
				trame_bluetooth.envoi(ADRESSE_TOURELLE, char(delay_tourelle), 0);
				break;

		}	
	}
	
	//Gestion des boutons S1 à S5
    if(bouton_baba.changement_etat_bouton())
    {
		// Une trame est envoyé à chaque appuis ou relachement d'un bouton.
		trame_bluetooth.envoi(ADRESSE_BOUTON, bouton_baba.numero_bouton(), 0);
    }	
}