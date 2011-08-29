package be.nicolas.robert.positionlogger.events;

import android.app.Activity;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.EditText;
import be.nicolas.robert.positionlogger.R;
import be.nicolas.robert.positionlogger.database.DatabaseHelper;
import be.nicolas.robert.positionlogger.pojos.PositionMarker;
import be.nicolas.robert.positionlogger.sensors.PositionSensor;

/**
 * Listener chargé de gérer le bouton "Record current position".
 * Lorsque le bouton "record current position" est cliqué,
 * la position courante est enregistrée en DB.
 */
public final class OnClickRecordCurrPosition implements OnClickListener {
	
	private Activity activity;
	
	public OnClickRecordCurrPosition(Activity activity) {
		this.activity = activity;
	}

	@Override
	public void onClick(View v) {
		
		// Construit le POJO pour la position courante
		PositionMarker currentPositionToInsert = null;
		{
			EditText txtComment = (EditText) activity.findViewById(R.id.txtComment);
			currentPositionToInsert = PositionSensor.CURRENT_POSITION;
			currentPositionToInsert.setComment(txtComment.getText().toString());
		} // end-block
		
		// Enregistre en DB la position courante
		{
			DatabaseHelper dbHelp = new DatabaseHelper(v.getContext());
			dbHelp.insertPosition(currentPositionToInsert);
		} // end-block

	}

}
