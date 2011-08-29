/*
 * Copyright (C) 2011 Eirik Taylor
 *
 * This work is licensed under a Creative Commons Attribution-Noncommercial-Share Alike 3.0 Unported License.
 * See the following website for more information: 
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 * 
 */

package com.uzzors2k.blu_car;

import java.io.IOException;
import java.io.OutputStream;
import java.util.List;
import java.util.UUID;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.DialogInterface.OnClickListener;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class blu_car extends Activity { 
	
	// Intent request codes
    private static final int REQUEST_CONNECT_DEVICE = 1;
    private static final int REQUEST_ENABLE_BT = 2;
    
    // Program variables
    private byte AttinyOut;
    private boolean ledStat;
    private boolean connectStat = false;
    private Button led_button;
    private Button forward_button;
    private Button reverse_button;
    private Button connect_button;
    private TextView xAccel;
    protected static final int MOVE_TIME = 80;
    private long lastWrite = 0;
    private AlertDialog aboutAlert;
    private View aboutView;
    private View controlView;
    OnClickListener myClickListener;
    ProgressDialog myProgressDialog;
    private Toast failToast;
    private Handler mHandler;
    
    // Sensor object used to handle accelerometer
    private SensorManager mySensorManager; 
    private List<Sensor> sensors; 
    private Sensor accSensor;
    
	// Bluetooth Stuff
    private BluetoothAdapter mBluetoothAdapter = null;
    private BluetoothSocket btSocket = null; 
    private OutputStream outStream = null;
    private ConnectThread mConnectThread = null;
    private String deviceAddress = null;
    // Well known SPP UUID (will *probably* map to RFCOMM channel 1 (default) if not in use); 
    private static final UUID SPP_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    
     /** Called when the activity is first created. */ 
     @Override 
     public void onCreate(Bundle savedInstanceState) { 
    	 super.onCreate(savedInstanceState);
    	 
    	 // Create main button view
    	 LayoutInflater inflater = (LayoutInflater)getSystemService(Context.LAYOUT_INFLATER_SERVICE);
    	 aboutView = inflater.inflate(R.layout.aboutview, null);
    	 controlView = inflater.inflate(R.layout.main, null);
    	 controlView.setKeepScreenOn(true);
    	 setContentView(controlView);
    	 
         // Finds buttons in .xml layout file
         led_button = (Button) findViewById(R.id.led_button);
         forward_button = (Button) findViewById(R.id.forward_button);
         reverse_button = (Button) findViewById(R.id.reverse_button);
         connect_button = (Button) findViewById(R.id.connect_button);
         xAccel = (TextView) findViewById(R.id.accText);
          
         // Set Sensor
         mySensorManager = (SensorManager)getSystemService(Context.SENSOR_SERVICE); 
         sensors = mySensorManager.getSensorList(Sensor.TYPE_ACCELEROMETER); 
         if(sensors.size() > 0) accSensor = sensors.get(0); 
         
         // Handle click events from help and info dialogs
         myClickListener = new DialogInterface.OnClickListener() {
    			@Override
    			public void onClick(DialogInterface dialog, int which) {
    				switch (which) {
    				case DialogInterface.BUTTON_POSITIVE:
    					dialog.dismiss();
    				break;
    				case DialogInterface.BUTTON_NEUTRAL:
    					// Display website
    					Intent browserIntent = new Intent("android.intent.action.VIEW", Uri.parse(getResources().getString(R.string.website_url)));
						startActivity(browserIntent);
    				break;
    				default: dialog.dismiss();
    				}
    			}
         };
         
         myProgressDialog = new ProgressDialog(this);
         failToast = Toast.makeText(this, R.string.failedToConnect, Toast.LENGTH_SHORT);
         
         mHandler = new Handler() {
             @Override
             public void handleMessage(Message msg) {
            	 if (myProgressDialog.isShowing()) {
                 	myProgressDialog.dismiss();
                 }
            	 
            	 // Check if bluetooth connection was made to selected device
                 if (msg.what == 1) {
                 	// Set button to display current status
                     connectStat = true;
                     connect_button.setText(R.string.connected);
                     
         	 		// Reset the BluCar
         	 		AttinyOut = 0;
         	 		ledStat = false;
         	 		write(AttinyOut);
                 }else {
                 	// Connection failed
                	 failToast.show();
                 }
             }
         };
         
         // Create about dialog
         AlertDialog.Builder builder = new AlertDialog.Builder(this);
         builder.setView(aboutView).setCancelable(true).setTitle(getResources().getString(R.string.app_name) + " " + getResources().getString(R.string.appVersion)).setIcon(R.drawable.blu_car_icon).setPositiveButton(getResources().getString(R.string.okButton), myClickListener).setNeutralButton(getResources().getString(R.string.websiteButton), myClickListener);
         aboutAlert = builder.create();
         
         // Check whether bluetooth adapter exists
         mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter(); 
         if (mBluetoothAdapter == null) { 
              Toast.makeText(this, R.string.no_bt_device, Toast.LENGTH_LONG).show(); 
              finish(); 
              return; 
         } 
         
         // If BT is not on, request that it be enabled.
         if (!mBluetoothAdapter.isEnabled()) {
             Intent enableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
             startActivityForResult(enableIntent, REQUEST_ENABLE_BT);
         }
         
          /**********************************************************************
           * Buttons for controlling BluCar
           */
          
         // Connect to Bluetooth Module
         connect_button.setOnClickListener(new View.OnClickListener() {
 			
 			@Override
 			public void onClick(View v) {
				if (connectStat) {
					// Attempt to disconnect from the device
					disconnect();
				}else{
					// Attempt to connect to the device
					connect();
				}
 			}
 		});
       
         // Toggle Headlights
         led_button.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				if (ledStat) {
					AttinyOut = (byte) (AttinyOut & 124);
					led_button.setText(R.string.ledON);
					ledStat = false;
				}else{
					AttinyOut = (byte) (AttinyOut | 128);
					led_button.setText(R.string.ledOFF);
					ledStat = true;
				}
				write(AttinyOut);
			}
		});
         
         // Drive forward
         forward_button.setOnTouchListener(new View.OnTouchListener() {
			
			@Override
			public boolean onTouch(View v, MotionEvent event) {
				if ((event.getAction() == MotionEvent.ACTION_DOWN) | (event.getAction() == MotionEvent.ACTION_MOVE)) {
					forward_button.setPressed(true);
					AttinyOut = (byte) (AttinyOut | 16);
					write(AttinyOut);
					return true;
					
				}else if (event.getAction() == MotionEvent.ACTION_UP) {
					forward_button.setPressed(false);
					AttinyOut = (byte) (AttinyOut & 236);
					write(AttinyOut);
					return true;
				}
				forward_button.setPressed(false);
				return false;
			}
		});
         
         // Back up
         reverse_button.setOnTouchListener(new View.OnTouchListener() {
			
			@Override
			public boolean onTouch(View v, MotionEvent event) {
				if ((event.getAction() == MotionEvent.ACTION_DOWN) | (event.getAction() == MotionEvent.ACTION_MOVE)) {
					reverse_button.setPressed(true);
					AttinyOut = (byte) (AttinyOut | 32);
					write(AttinyOut);
					return true;
					
				}else if (event.getAction() == MotionEvent.ACTION_UP) {
					reverse_button.setPressed(false);
					AttinyOut = (byte) (AttinyOut & 220);
					write(AttinyOut);
					return true;
				}
				reverse_button.setPressed(false);
				return false;
			}
		});
        
     }
     
     /** Thread used to connect to a specified Bluetooth Device */
     public class ConnectThread extends Thread {
    	private String address;
    	private boolean connectionStatus;
    	
		ConnectThread(String MACaddress) {
			address = MACaddress;
			connectionStatus = true;
    	}
		
		public void run() {
    		// When this returns, it will 'know' about the server, 
            // via it's MAC address. 
			try {
				BluetoothDevice device = mBluetoothAdapter.getRemoteDevice(address);
				
				// We need two things before we can successfully connect 
	            // (authentication issues aside): a MAC address, which we 
	            // already have, and an RFCOMM channel. 
	            // Because RFCOMM channels (aka ports) are limited in 
	            // number, Android doesn't allow you to use them directly; 
	            // instead you request a RFCOMM mapping based on a service 
	            // ID. In our case, we will use the well-known SPP Service 
	            // ID. This ID is in UUID (GUID to you Microsofties) 
	            // format. Given the UUID, Android will handle the 
	            // mapping for you. Generally, this will return RFCOMM 1, 
	            // but not always; it depends what other BlueTooth services 
	            // are in use on your Android device. 
	            try { 
	                 btSocket = device.createRfcommSocketToServiceRecord(SPP_UUID); 
	            } catch (IOException e) { 
	            	connectionStatus = false;
	            } 
			}catch (IllegalArgumentException e) {
				connectionStatus = false;
			}
            
            // Discovery may be going on, e.g., if you're running a 
            // 'scan for devices' search from your handset's Bluetooth 
            // settings, so we call cancelDiscovery(). It doesn't hurt 
            // to call it, but it might hurt not to... discovery is a 
            // heavyweight process; you don't want it in progress when 
            // a connection attempt is made. 
            mBluetoothAdapter.cancelDiscovery(); 
            
            // Blocking connect, for a simple client nothing else can 
            // happen until a successful connection is made, so we 
            // don't care if it blocks. 
            try {
                 btSocket.connect(); 
            } catch (IOException e1) {
                 try {
                      btSocket.close(); 
                 } catch (IOException e2) {
                 }
            }
            
            // Create a data stream so we can talk to server. 
            try { 
            	outStream = btSocket.getOutputStream(); 
            } catch (IOException e2) {
            	connectionStatus = false;
            }
            
            // Send final result
            if (connectionStatus) {
            	mHandler.sendEmptyMessage(1);
            }else {
            	mHandler.sendEmptyMessage(0);
            }
		}
     }
     
     public void onActivityResult(int requestCode, int resultCode, Intent data) {
    	 switch (requestCode) {
         case REQUEST_CONNECT_DEVICE:
        	 // When DeviceListActivity returns with a device to connect
             if (resultCode == Activity.RESULT_OK) {
            	// Show please wait dialog
 				myProgressDialog = ProgressDialog.show(this, getResources().getString(R.string.pleaseWait), getResources().getString(R.string.makingConnectionString), true);
 				
            	// Get the device MAC address
        		deviceAddress = data.getExtras().getString(DeviceListActivity.EXTRA_DEVICE_ADDRESS);
        		// Connect to device with specified MAC address
                mConnectThread = new ConnectThread(deviceAddress);
                mConnectThread.start();
                
             }else {
            	 // Failure retrieving MAC address
            	 Toast.makeText(this, R.string.macFailed, Toast.LENGTH_SHORT).show();
             }
             break;
         case REQUEST_ENABLE_BT:
             // When the request to enable Bluetooth returns
             if (resultCode == Activity.RESULT_OK) {
                 // Bluetooth is now enabled
             } else {
                 // User did not enable Bluetooth or an error occured
                 Toast.makeText(this, R.string.bt_not_enabled_leaving, Toast.LENGTH_SHORT).show();
                 finish();
             }
         }
     }
     
     public void write(byte data) {
    	 if (outStream != null) {
             try {
            	 outStream.write(data);
             } catch (IOException e) {
             }
         }
     }
     
     public void emptyOutStream() {
    	 if (outStream != null) {
             try {
            	 outStream.flush();
             } catch (IOException e) {
             }
         }
     }
     
     public void connect() {
    	 // Launch the DeviceListActivity to see devices and do scan
         Intent serverIntent = new Intent(this, DeviceListActivity.class);
         startActivityForResult(serverIntent, REQUEST_CONNECT_DEVICE);
     }
     
     public void disconnect() {
    	 if (outStream != null) {
    		 try {
    	 			outStream.close();
    	 			connectStat = false;
    				connect_button.setText(R.string.disconnected);
    	 		} catch (IOException e) {
    	 		}
    	 } 
     }
     
     private final SensorEventListener mSensorListener = new SensorEventListener() {
    	 
 		@Override
 		public void onAccuracyChanged(Sensor sensor, int accuracy) {}
 		
 		@Override
 		public void onSensorChanged(SensorEvent event) {
 			// Checks whether to send steering command or not
 			long date = System.currentTimeMillis();
 			if (date - lastWrite > MOVE_TIME) {
 				xAccel.setText(" " + event.values[0]);
 				if (event.values[0] > 4.5) {
 					// Turn right
 					AttinyOut = (byte) (AttinyOut & 248);
 					AttinyOut = (byte) (AttinyOut | 4);
 				}else if (event.values[0] < -4.5) {
 					// Turn left
 					AttinyOut = (byte) (AttinyOut & 244);
 					AttinyOut = (byte) (AttinyOut | 8);
 				}else {
 					// Center the steering servo
 					AttinyOut = (byte) (AttinyOut & 240);
 				}
 				write(AttinyOut);
 				lastWrite = date;
 			}
 		}
      };
     
     @Override
     public boolean onCreateOptionsMenu(Menu menu) {
         MenuInflater inflater = getMenuInflater();
         inflater.inflate(R.menu.option_menu, menu);
         return true;
     }
     
     @Override
     public boolean onOptionsItemSelected(MenuItem item) {
         switch (item.getItemId()) {
         case R.id.about:
             // Show info about the author (that's me!)
        	 aboutAlert.show();
             return true;
         }
         return false;
     }

     @Override 
     public void onResume() { 
          super.onResume();
          mySensorManager.registerListener(mSensorListener, accSensor, SensorManager.SENSOR_DELAY_GAME);
     } 

     @Override 
     public void onDestroy() { 
    	 emptyOutStream();
         disconnect();
         if (mSensorListener != null) {
        	 mySensorManager.unregisterListener(mSensorListener);
         }
         super.onDestroy(); 
     } 
}