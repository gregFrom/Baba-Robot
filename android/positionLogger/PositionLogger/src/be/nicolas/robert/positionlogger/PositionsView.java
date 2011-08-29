package be.nicolas.robert.positionlogger;

import java.util.List;

import android.os.Bundle;
import android.view.View;
import android.widget.LinearLayout;
import be.nicolas.robert.positionlogger.database.DatabaseHelper;
import be.nicolas.robert.positionlogger.pojos.PositionMarkersList;
import be.nicolas.robert.positionlogger.pojos.PositionMarker;

import com.google.android.maps.GeoPoint;
import com.google.android.maps.MapActivity;
import com.google.android.maps.MapView;
import com.google.android.maps.Overlay;
import com.google.android.maps.OverlayItem;
import com.google.android.maps.MapView.LayoutParams;

/**
 * Activité affichant les positions enregistrées sur la carte.
 */
public final class PositionsView extends MapActivity {

	 MapView mapView = null;
	 PositionMarkersList positionMarkersList = null;
	
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.mapview);
        
        // Configure la map
        configureMapView();
        
        // Récupère les positions enregistrées
        // et ajoute les à la carte.
        retrieveAndDisplayPositions();
        
        // mapView.invalidate();
    }
	
	@Override
	protected boolean isRouteDisplayed() {
		return false;
	}
	
	/**
	 * Initialise/configure la map.
	 */
	private void configureMapView() {
        mapView = (MapView) findViewById(R.id.mapView);
        
        // ne fonctionne pas...
        {
        	LinearLayout zoomLayout = (LinearLayout)findViewById(R.id.zoom); 
        	View zoomView = mapView.getZoomControls(); 
        	zoomLayout.addView(zoomView, 
        			new LinearLayout.LayoutParams(
        					LayoutParams.WRAP_CONTENT, 
        					LayoutParams.WRAP_CONTENT)); 
        } // end-block
        
        mapView.setSatellite(true);
        mapView.setStreetView(true);
        mapView.displayZoomControls(true);
        
        // MapController mc = mapView.getController();
	}
	
	private void retrieveAndDisplayPositions() {
        // Affiche l'ensemble des marqueurs enregistrés en DB
        {
            positionMarkersList = new PositionMarkersList(this.getResources().getDrawable(R.drawable.marker), this);
            List<Overlay> mapOverlays = mapView.getOverlays();
            mapOverlays.add(positionMarkersList);
            
            // Récupère de la DB les marqueurs enregistrés
            // et ajoute les à la carte
            {
            	DatabaseHelper dbHelp = new DatabaseHelper(getApplicationContext());
            	for (PositionMarker positionToAdd : dbHelp.getPositions()) {
    	            addPosition(positionToAdd);
            	} // end-for
            } // end-block
        } // end-block
	}
	
	private void addPosition(PositionMarker positionMarker) {
        double lat = positionMarker.getLatitude();
        double lng = positionMarker.getLongitude();
        GeoPoint geoPoint = new GeoPoint((int) (lat * 1E6), (int) (lng * 1E6));
        OverlayItem overlayitem = new OverlayItem(geoPoint, positionMarker.getComment(), positionMarker.toString());
        positionMarkersList.addMarker(overlayitem);
	}
	

}
