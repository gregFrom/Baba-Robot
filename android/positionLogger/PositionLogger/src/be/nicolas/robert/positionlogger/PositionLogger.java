package be.nicolas.robert.positionlogger;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import be.nicolas.robert.positionlogger.events.OnClickRecordCurrPosition;
import be.nicolas.robert.positionlogger.sensors.PositionSensor;

/**
 * Activité principale permettant à l'utilisateur d'enregistrer la position courante.
 */
public final class PositionLogger extends Activity  {
	
	/**
	 * Sonde multiposition (accéléromètre, boussole, GPS).
	 */
	private PositionSensor sensor = null;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        // Met en place la sonde multiposition
        {
        	sensor = new PositionSensor(this);
        } // end-block
        
        //Met en place le listener du bouton "record current position"
        {
        	Button recordButton = (Button) findViewById(R.id.btnRecord);
        	OnClickRecordCurrPosition onClickRecordCurrPosition = new OnClickRecordCurrPosition(this);
        	recordButton.setOnClickListener(onClickRecordCurrPosition);
        } // end-block

        // Met en place le listener du bouton "view recorded positions"
        {
        	Button viewPositionsButton = (Button) findViewById(R.id.btnViewPositions);
        	viewPositionsButton.setOnClickListener(
        											new View.OnClickListener() {
        												public void onClick(View view) {
        													Intent i = new Intent(PositionLogger.this, PositionsView.class);
        													startActivity(i);
        												}
        											}
        										);
        } // end-block
    }
    
}