package com.robot.baba;

import java.util.Calendar;

/**
 * Représente une position combinant à la fois :
 * - angle (boussole)
 * - x,y,z (accéléromètre)
 * - longitude, latitude (GPS)
 */
public final class PositionMarker {

	/** Clé technique de la position. Différent de 0 si la position a été chargée à partir de la DB **/
	private long techKey = 0;
	
	/**
	 * Date de création de la position.
	 */
	private Calendar creationDate = Calendar.getInstance();
	
	private float angle;
	
	private float x;
	private float y;
	private float z;
	
	private double longitude;
	private double latitude;
	private double altitude;
	private float speed;
	
	/** Contient le commentaire saisit par l'utilisateur **/
	private String comment;
	
	public PositionMarker(long techKey, Calendar creationDate, float angle, float x,
					float y, float z, double longitude, double latitude,
					double altitude, float speed) {
		this.techKey = techKey;
		this.creationDate = creationDate;
		this.angle = angle;
		this.x = x;
		this.y = y;
		this.z = z;
		this.longitude = longitude;
		this.latitude = latitude;
		this.altitude = altitude;
		this.speed = speed;
	}
	
	/**
	 * Affiche le contenu de la position sous forme de String.
	 */
	@Override
	public String toString() {
		String output = "\ndate = " + creationDate.getTime() +
						"\nangle = " + angle +
						"\nx= " + x + 
						"\ny=" + y + 
						"\nz=" + z +
						"\nlongitude = " + longitude +
						"\nlatitude = " + latitude +
						"\naltitude = " + altitude +
						"\nspeed = " + speed +
						"\ncomment = " + comment;
		return output;
	}
	
	public final long getTechKey() {
		return techKey;
	}
	public final Calendar getCreationDate() {
		return creationDate;
	}
	public final float getAngle() {
		return angle;
	}
	public final float getX() {
		return x;
	}
	public final float getY() {
		return y;
	}
	public final float getZ() {
		return z;
	}
	public final double getLongitude() {
		return longitude;
	}
	public final double getLatitude() {
		return latitude;
	}
	public final double getAltitude() {
		return altitude;
	}
	public final float getSpeed() {
		return speed;
	}
	public final String getComment() {
		return comment;
	}
	public final void setComment(String comment) {
		this.comment = comment;
	}


}
