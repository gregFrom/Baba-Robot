/**
  Trame_ascii.h - Bibliotheque pour la gestion de communication entre android et arduino

  @author :     Grégory Fromain, < gregoryfromain@gmail.com >
  @since : 	    27/07/2011
  @license :    http://creativecommons.org/licenses/by-nc/3.0/
  @link :       https://github.com/greg06/Baba-Robot
*/

/*
Detail du protocole de communication

1 octet de start		Hex. 01 (Start of Header)
1 octet d'adresse		> hex. 20
1 octet de fonction		> hex. 20
n octet de données		> hex. 20 (max. 15 octets)
2 octet de stop			Hex. 0D	et 0A (Carriage Return et Line Feed)

Octet D'adresse :
Permet de definir par exemple le capteur concerné.

Octet de fonction :
Permet de définir quel action doit etre fait sur le capteur.

Octet de données :
Permet de faire passer un flux d'information avec un max de 15 octets
*/


#ifndef Trame_ascii_h
#define Trame_ascii_h

#include "Arduino.h"

#define TRAME_OCTET_START		  '0'//0x01
#define TRAME_OCTET_STOP1		  '8'//0x0D
#define TRAME_OCTET_STOP2		  '9'//0x0A
#define TRAME_OCTET_MIN			  0x20

#define TRAME_TAILLE_MAX      20
#define DONNEE_TAILLE_MAX     15	//TRAME_TAILLE_MAX-5
#define DONNEE_POSITION_MIN		3

class Trame_ascii
{
	public:
		Trame_ascii();
		void init(int debit);
		bool disponible();
		bool lire_buffer();
		byte adresse();
		byte fonction();
		byte donnee();
		void debug();
		void envoi(char adresse, char fonction, char donnee[DONNEE_TAILLE_MAX]);
    void debug_int(char myStrings[10], int val_int);
	private:
		bool _dispo;
		byte _pos_tableau;
		char _trame[TRAME_TAILLE_MAX];
		byte _adresse;
		byte _fonction;
		char _donnee[DONNEE_TAILLE_MAX];
};

#endif