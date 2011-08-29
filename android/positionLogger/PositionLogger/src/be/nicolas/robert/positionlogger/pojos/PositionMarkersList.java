package be.nicolas.robert.positionlogger.pojos;

import java.util.ArrayList;

import android.app.AlertDialog;
import android.content.Context;
import android.graphics.drawable.Drawable;

import com.google.android.maps.ItemizedOverlay;
import com.google.android.maps.OverlayItem;

/**
 * Regroupe la liste des marqueurs d'une même famille.
 */
public final class PositionMarkersList extends ItemizedOverlay {
	
	/**
	 * Contient la liste des marqueurs à afficher.
	 */
	private ArrayList<OverlayItem> marqueurs = new ArrayList<OverlayItem>();
	
	/**
	 * Référence vers le contexte d'exécution.
	 */
	private Context context;
	
	public PositionMarkersList(Drawable defaultMarker, Context context) {
		  super(boundCenterBottom(defaultMarker));
		  this.context = context;
	}
	
	/**
	 * Ajoute un marqueur à afficher.
	 */
	public void addMarker(OverlayItem overlay) {
		marqueurs.add(overlay);
	    populate();
	}

	@Override
	protected OverlayItem createItem(int i) {
		return marqueurs.get(i);
	}

	@Override
	public int size() {
		return marqueurs.size();
	}
	
	/**
	 * Affiche un dialogue décrivant le marqueur lorsque l'utilisateur clique sur un marqueur.
	 */
	@Override
	protected boolean onTap(int index) {
	  OverlayItem item = marqueurs.get(index);
	  AlertDialog.Builder dialog = new AlertDialog.Builder(context);
	  dialog.setTitle(item.getTitle());
	  dialog.setMessage(item.getSnippet());
	  dialog.show();
	  return true;
	}

}
