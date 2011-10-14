/**
  Trame_ascii.cpp - Bibliotheque pour la gestion de communication entre android et arduino

  @author :     Grégory Fromain, < gregoryfromain@gmail.com >
  @since : 	    27/07/2011
  @license :    http://creativecommons.org/licenses/by-nc/3.0/
  @link :       https://github.com/greg06/Baba-Robot
*/

// trame de test : 55501238977

#include "WProgram.h"
#include "Trame_ascii.h"

Trame_ascii::Trame_ascii()
{
	_pos_tableau = 0;
	_dispo = false;
}

// Initialisation du port série.
void Trame_ascii::init(int debit)
{
	Serial.begin(debit);
}

// Permet de savoir si une trame est disponible.
bool Trame_ascii::disponible()
{
	return _dispo;
}

// Permet de renvoyer l'adresse (ou le capteur)
byte Trame_ascii::adresse()
{
	return _adresse;
}

// Permet de renvoyer la fonction
byte Trame_ascii::fonction()
{
	return _fonction;
}

// Permet de renvoyer la donnée
byte Trame_ascii::donnee()
{
	return _donnee[0];
}

// Affiche des informations de débuggage
void Trame_ascii::debug()
{
	Serial.print("Trame non traité : ");
	Serial.println(_trame);
	Serial.print("Adresse : ");
	Serial.println(_adresse);
	Serial.print("Fonction : ");
	Serial.println(_fonction);
	Serial.print("Données : ");
	Serial.println(_donnee);
	delay(1000);
}

bool Trame_ascii::lire_buffer()
{
	bool reset_trame = false;
	byte i = 0;
	byte _fin_de_trame = 0;
	_dispo = false;								//Par defaut la trame n'est pas disponible.
		
	// On recupere le buffer dans la limite de la taille de la trame.
	while((Serial.available() > 0) && (_pos_tableau < TRAME_TAILLE_MAX))
	{
		_trame[_pos_tableau] = Serial.read();
		_pos_tableau++;
	}
	
	// On regarde si le bit de start est valide.	
	while((_trame[0] != TRAME_OCTET_START) && (_pos_tableau != 0))
	{																			
		for( i=0; i<_pos_tableau; i++)			// Si ce n'est pas valide on decale les octets de 1
		{
			_trame[i] = _trame[i+1];			
		}
		_pos_tableau--;							// On décremente la position actuel de la position du tableau.
	}

	// On regarde si les octets de fin sont arrivés
	for( i=0; i<_pos_tableau; i++)
	{
		if ((_trame[i] == TRAME_OCTET_STOP1) && (_trame[i+1] == TRAME_OCTET_STOP2))
		{										//Les 2 octets de fin son bien la.	
			_fin_de_trame = i + 1;
			i = _pos_tableau;					// On sort de la boucle
		}
	}
	
	// Si la trame entiere ne contient pas de fin de trame, on reset la trame.
	if((_fin_de_trame == 0) && (_pos_tableau == TRAME_TAILLE_MAX))
	{											
		reset_trame = true;
		for( i=0; i<TRAME_TAILLE_MAX; i++)
		{
			_trame[i] = 0;
		}
		_pos_tableau = 0;						// reset de la position du tableau.		
	}

	// Si la trame est correct et que l'on retrouve les octets de fin
	if((_trame[0] == TRAME_OCTET_START) && (_fin_de_trame!=0))
	{																						
		_adresse = _trame[1];					// on attribut les valeurs on differentes variable.
		_fonction = _trame[2];
		_donnee[0] = _trame[3];
		_dispo = true;							//Et on finit par indiquer qu'une nouvelle trame est dispo.
		
		for( i=0; i<TRAME_TAILLE_MAX; i++)
		{										//Et on décalle la trame des éléments utilisé pour laisser de la place aux nouveaux.
			byte decallage = i + _fin_de_trame + 1;
			if(decallage <= TRAME_TAILLE_MAX)
			{									// nous ne somme pas en position de fin de trame.
				_trame[i] = _trame[decallage];	// On decalle donc les éléments.
			}
			else
			{									// La trame est décallé, il faut maintenant mettre des valeurs à vide.
				_trame[i] = 0;
			}
		}
	}

	return _dispo;
}

void Trame_ascii::envoi(char adresse, char fonction, char donnee[DONNEE_TAILLE_MAX])
{
	char trame_envoi[TRAME_TAILLE_MAX];
	byte position;
	byte i;
	trame_envoi[0] = TRAME_OCTET_START;			// Octet de Start
	trame_envoi[1] = adresse;					// Octet d'adresse
	trame_envoi[2] = fonction;					// Octet de la fonction
	
	for( i=0; i < DONNEE_TAILLE_MAX; i++)
	{
		if(donnee[i] != 0)
		{
			trame_envoi[i+DONNEE_POSITION_MIN] = donnee[i];	// + 3 car a partir du 3eme element du tableau
		}
		else
		{
			position = i + DONNEE_POSITION_MIN;
			i = DONNEE_TAILLE_MAX;
		}
	}	
	trame_envoi[position] = TRAME_OCTET_STOP1;			// Octet de Stop 1
	trame_envoi[position + 1] = TRAME_OCTET_STOP2;		// Octet de Stop 2
	
	// A partir de position + 2 si il reste des elements dans le tableau il devront etre à Null
	
	for( i = position + 2; i <= DONNEE_TAILLE_MAX; i++)
	{
		trame_envoi[i] = 0;
	}
	
	Serial.print(trame_envoi);					// Envoi de la trame
	
}

void Trame_ascii::debug_int(char myStrings[10], int val_int)
{
  Serial.print(myStrings);
  Serial.println(val_int);
}