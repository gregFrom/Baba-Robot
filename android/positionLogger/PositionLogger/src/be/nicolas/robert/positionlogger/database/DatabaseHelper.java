package be.nicolas.robert.positionlogger.database;

import java.util.ArrayList;
import java.util.Calendar;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import be.nicolas.robert.positionlogger.pojos.PositionMarker;

/**
 * Permet d'enregistrer/lire les positions dans la base de données.
 */
public final class DatabaseHelper extends SQLiteOpenHelper {
	
	/** Nom du fichier de la DB **/
	private static String DATABASE_NAME = "poslog.db";
	
	/** Version de la DB, utilisé pour les mises à jour **/
	private static final int DATABASE_VERSION = 1;
	
	/** Référence vers la connection DB **/
	private SQLiteDatabase db;

	/** Nom de la table centralisant les Positions enregistrées **/
	private static String TABLE_POSITIONS = "Positions";
	
	private static String COLUMN_TECHKEY = "techKey";
	private static String COLUMN_CREATIONDATE = "createDate";
	private static String COLUMN_ANGLE = "angle";
	private static String COLUMN_X = "x";
	private static String COLUMN_Y = "y";
	private static String COLUMN_Z = "z";
	private static String COLUMN_LONGITUDE = "longitude";
	private static String COLUMN_LATITUDE = "latitude";
	private static String COLUMN_ALTITUDE = "altitude";
	private static String COLUMN_SPEED = "speed";
	private static String COLUMN_COMMENT = "comment";
	
	/** Script de création de la table Positions **/
	private static String CREATE_TABLE_POSITIONS = 
				"create table " + TABLE_POSITIONS + " ( " +
					COLUMN_TECHKEY + " integer PRIMARY KEY AUTOINCREMENT," +
					COLUMN_CREATIONDATE + " TIMESTAMP," +
					COLUMN_ANGLE + " FLOAT," +
					COLUMN_X + " FLOAT," +
					COLUMN_Y + " FLOAT," +
					COLUMN_Z + " FLOAT," +
					COLUMN_LONGITUDE + " FLOAT," +
					COLUMN_LATITUDE + " FLOAT," +
					COLUMN_ALTITUDE + " FLOAT," +
					COLUMN_SPEED + " FLOAT," +
					COLUMN_COMMENT + " TEXT" +
				");";
	
	public DatabaseHelper(Context context) {
		super(context, DATABASE_NAME, null, DATABASE_VERSION);
		db = getWritableDatabase();
	}

	/**
	 * Lors de la première exécution,
	 * crée la table Positions.
	 */
	@Override
	public void onCreate(SQLiteDatabase db) {
		db.execSQL(CREATE_TABLE_POSITIONS);
	}

	/**
	 * Exécuté lorsque le numéro de version change (DATABASE_VERSION).
	 * Supprime l'ancienne table Positions et la remplace par la nouvelle.
	 */
	@Override
	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
		db.execSQL("DROP TABLE IF EXISTS " + TABLE_POSITIONS);
		onCreate(db);
	}
	
	/**
	 * Enregistre la position donnée.
	 * Met à jour la date de création de la position.
	 */
	public long insertPosition(PositionMarker positionMarker) {
		if (null != positionMarker) {
			ContentValues positionToInsert = new ContentValues();
			positionToInsert.put(COLUMN_CREATIONDATE, positionMarker.getCreationDate().getTimeInMillis());
			positionToInsert.put(COLUMN_ANGLE, positionMarker.getAngle());
			positionToInsert.put(COLUMN_X, positionMarker.getX());
			positionToInsert.put(COLUMN_Y, positionMarker.getY());
			positionToInsert.put(COLUMN_Z, positionMarker.getZ());
			positionToInsert.put(COLUMN_LONGITUDE, positionMarker.getLongitude());
			positionToInsert.put(COLUMN_LATITUDE, positionMarker.getLatitude());
			positionToInsert.put(COLUMN_ALTITUDE, positionMarker.getAltitude());
			positionToInsert.put(COLUMN_SPEED, positionMarker.getSpeed());
			positionToInsert.put(COLUMN_COMMENT, positionMarker.getComment());
			long output = db.insert(TABLE_POSITIONS, null, positionToInsert);
			db.close();
			return output;
		} else {
			 return 0;
		} // end-if
	}
	
	/**
	 * Récupère l'ensemble des positions disponibles en DB.
	 */
	public ArrayList<PositionMarker> getPositions() {
		ArrayList<PositionMarker> output = new ArrayList<PositionMarker>();
		String[] colonnesARecup = new String[] { 
									COLUMN_TECHKEY,
									COLUMN_CREATIONDATE, 
									COLUMN_ANGLE,
									COLUMN_X,
									COLUMN_Y,
									COLUMN_Z,
									COLUMN_LONGITUDE,
									COLUMN_LATITUDE,
									COLUMN_ALTITUDE,
									COLUMN_SPEED,
									COLUMN_COMMENT
								};
		Cursor cursorResults = db.query(TABLE_POSITIONS, colonnesARecup, null, null, null, null, COLUMN_CREATIONDATE + " asc", null);
		if (null != cursorResults) {
			if (cursorResults.moveToFirst()) {
				do {
					long techKey =  cursorResults.getLong(cursorResults.getColumnIndex(COLUMN_TECHKEY));
					Calendar creationDate = Calendar.getInstance(); creationDate.setTimeInMillis(cursorResults.getLong(cursorResults.getColumnIndex(COLUMN_CREATIONDATE)));
					float angle = cursorResults.getFloat(cursorResults.getColumnIndex(COLUMN_ANGLE));
					float x = cursorResults.getFloat(cursorResults.getColumnIndex(COLUMN_X));
					float y = cursorResults.getFloat(cursorResults.getColumnIndex(COLUMN_Y));
					float z = cursorResults.getFloat(cursorResults.getColumnIndex(COLUMN_Z));
					double longitude = cursorResults.getDouble(cursorResults.getColumnIndex(COLUMN_LONGITUDE));
					double latitude = cursorResults.getDouble(cursorResults.getColumnIndex(COLUMN_LATITUDE));
					double altitude = cursorResults.getDouble(cursorResults.getColumnIndex(COLUMN_ALTITUDE));
					float speed = cursorResults.getFloat(cursorResults.getColumnIndex(COLUMN_SPEED));
					String comment = cursorResults.getString(cursorResults.getColumnIndex(COLUMN_COMMENT));
					PositionMarker positionToAdd = new PositionMarker(techKey, creationDate, angle, x,y,z,longitude,latitude,altitude,speed);
					positionToAdd.setComment(comment);
					output.add(positionToAdd);
				} while (cursorResults.moveToNext());
			} // end-if
		} // end-if
		db.close();
		return output;
	}

}
