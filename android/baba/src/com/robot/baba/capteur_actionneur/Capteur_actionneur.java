/**
 * Permet de gerer les differents organes matériel du robot.
 * 
 * @author Grégory Fromain <gregoryfromain@gmail.com>
 * @verion 0.1
 */
package com.robot.baba.capteur_actionneur;

import android.app.Activity;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

import com.robot.baba.Baba;
import com.robot.baba.PositionSensor;

public class Capteur_actionneur extends Baba
{
	/*
	 * Déclaration des constantes.
	 */
	//Définition des bits de start et stop	
	public static final char OCTET_START = '0';
    public static final char OCTET_FIN_1 = '8';
    public static final char OCTET_FIN_2 = '9';
    
	 // Définition des contantes pour le traitement de la trame bluetooth
    public static final char ADRESSE_LUMIERE = 'l';
    public static final char ADRESSE_MOTEUR_DROITE = 'd';
    public static final char ADRESSE_MOTEUR_GAUCHE = 'g';
    public static final char ADRESSE_TEMPERATURE = 't';
    public static final char ADRESSE_TOURELLE = 'x';
    
    // Constante des moteurs
    public static final char MOTEUR_AVANT = 0x10;
    public static final char MOTEUR_ARRIERE = 0x20;
    public static final char MOTEUR_FREIN = 0x30;
    public static final char MOTEUR_ROUE_LIBRE = 0x40;
    public static final char VITESSE_NORMAL = (char) (100);
    
    // Constante eclairage
    public static final char FONCTION_LUMIERE_ON = 1;
    public static final char FONCTION_LUMIERE_OFF = 0;
    
    // Constante tourelle
    public static final char SERVO_Y_CENTRE = (char) (90);
    public static final char SERVO_X_CENTRE = (char) (90);
    
    public static final char DONNEE_VIDE = '0';
    
   
    
    
    /*
     * Creation des organes du robot
     */
    private Communication_bluetooth bt_arduino = null;
    private PositionSensor sensor = null;				// Sonde multiposition (accéléromètre, boussole, GPS).

    
    
    /**
	 * Constructeur
	 */
	public Capteur_actionneur(Activity activity)
	{
		
		bt_arduino = new Communication_bluetooth(handlerStatus, handler);
		sensor = new PositionSensor(activity);
	}
	
    /*
     * Gestion du bluetooth
     */
    private long lastTime = 0;
    final Handler handler = new Handler() {
        public void handleMessage(Message msg) {
            String data = msg.getData().getString("receivedData");
            
            long t = System.currentTimeMillis();
            if(t-lastTime > 100) {// Pour éviter que les messages soit coupés
                Log.v(TAG, "\n");
				lastTime = System.currentTimeMillis();
			}
            Log.v(TAG, data);
        }
    };
    
    final Handler handlerStatus = new Handler() 
    {
        public void handleMessage(Message msg) 
        {
            int co = msg.arg1;
            if(co == 1)
            {
            	Log.v(TAG, "Connected\n");
            }
            else if(co == 2) 
            {
            	Log.v(TAG, "Disconnected\n");
            }
        }
    };
	
	public void trame_envoi(char adresse, char fonction, char donnee)
    {
		 String trame = Character.toString(OCTET_START);
		 trame = trame.concat(Character.toString(adresse));
		 trame = trame.concat(Character.toString(fonction));
		 trame = trame.concat(Character.toString(donnee));
		 trame = trame.concat(Character.toString(OCTET_FIN_1));
		 trame = trame.concat(Character.toString(OCTET_FIN_2));
		 bt_arduino.sendData(trame);
		 Log.v("Baba", trame);
    }
	
	public void bluetooth_close()
	{
		bt_arduino.close();
	}
	
	public void bluetooth_connect()
	{
		bt_arduino.connect();
	}
	
	public void eclairage(boolean etat_lumiere)
	{
		if(etat_lumiere)
		{
			bt_arduino.trame_envoi(ADRESSE_LUMIERE, FONCTION_LUMIERE_ON, DONNEE_VIDE);
		}
		else
		{
			bt_arduino.trame_envoi(ADRESSE_LUMIERE, FONCTION_LUMIERE_OFF, DONNEE_VIDE);
		}
		
	}
	
	public void tourelle(char pos_x, char pos_y)
	{
		trame_envoi(ADRESSE_TOURELLE, pos_x, pos_y);
	}
	
	public void moteur_droite(int vitesse_moteur)
	{
		char sens, adresse, vitesse;
		
		//gestion du sens
		if(vitesse_moteur == 0)
			sens = MOTEUR_ROUE_LIBRE;
		else if(vitesse_moteur < 0)
			sens = MOTEUR_ARRIERE;
		else
			sens = MOTEUR_AVANT;
				
		adresse = ADRESSE_MOTEUR_DROITE;
		
		if((vitesse_moteur > 127)||(vitesse_moteur < 127)) vitesse = 0;
		
		vitesse = (char) (Math.abs(vitesse_moteur * 2));
		
		bt_arduino.trame_envoi(adresse, sens, vitesse);
	}

	public void moteur_gauche(int vitesse_moteur)
	{
		char sens, adresse, vitesse;
		
		//gestion du sens
		if(vitesse_moteur == 0)
			sens = MOTEUR_ROUE_LIBRE;
		else if(vitesse_moteur < 0)
			sens = MOTEUR_ARRIERE;
		else
			sens = MOTEUR_AVANT;
				
		adresse = ADRESSE_MOTEUR_GAUCHE;
		
		if((vitesse_moteur > 127)||(vitesse_moteur < 127)) vitesse = 0;
		
		vitesse = (char) (Math.abs(vitesse_moteur * 2));
		
		bt_arduino.trame_envoi(adresse, sens, vitesse);
	}
	
	public void avant()
	{
		moteur_droite(50);
		moteur_gauche(50);

	}
	
	public void arriere()
	{
		moteur_droite(-50);
		moteur_gauche(-50);
	}	
	
	public void stop()
	{
		moteur_droite(0);
		moteur_gauche(0);
	}
	
	public float position_tel(char type_position)
	{
		float position_retour = 0;
		switch (type_position)
	    {
	    	case 'x':
	    		position_retour = sensor.pos_x();
	    		break;
	         
	    	case 'y':
	    		position_retour = sensor.pos_y();
	    		break;
	    	
	    	case 'z':
	    		position_retour = sensor.pos_z();
	    		break;
	    	
	    	case 'a': // angle
	    		position_retour = sensor.pos_angle();
	    		break;	    		
	     }
		return position_retour;
	}
}
