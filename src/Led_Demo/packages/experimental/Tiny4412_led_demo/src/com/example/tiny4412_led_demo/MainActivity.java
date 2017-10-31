package com.example.tiny4412_led_demo;

 import android.content.Intent;
import android.os.ILed_demo_service;
import android.os.ICallback;
import android.os.RemoteException;
import android.os.ServiceManager;
import android.os.Bundle;
import android.app.Activity;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.content.ComponentName;
import android.os.IBinder;
import android.content.ServiceConnection;
import android.content.Context;
import android.widget.Toast;

public class MainActivity extends Activity implements OnClickListener{
    private final static String LOG_TAG = "MainActivity";
    private ILed_demo_service Led_demo_service = null;
	
	private ICallback.Stub mCallback = new ICallback.Stub() { 
		public void showResult(String result) {
			Toast.makeText(MainActivity.this,result,Toast.LENGTH_SHORT).show();
			Log.d(LOG_TAG, " result : " + result);  
		}  
	};
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
		Log.i(LOG_TAG, "MainActivity:onCreate");

        Led_demo_service = ILed_demo_service.Stub.asInterface(ServiceManager.getService("led_demo"));

        Button bt_on = (Button)findViewById(R.id.bt_on);
        Button bt_off = (Button)findViewById(R.id.bt_off);
        bt_on.setOnClickListener(this);
        bt_off.setOnClickListener(this);
		
		try {
			Led_demo_service.registerCallback(mCallback); 
			Log.i(LOG_TAG, "registerCallback is execute.");
		} catch (RemoteException e) {
			Log.e(LOG_TAG, "Remote Exception while registerCallback.");
		}
	}

    @Override
    public void onClick(View v) {
        switch(v.getId())
        {
            case R.id.bt_on:
                try
                {
                    Led_demo_service.led_set_ON(1);
                    Log.e(LOG_TAG, "set led on is execute.");
                    break;
                } catch (RemoteException e)
                {
                    Log.e(LOG_TAG, "Remote Exception while set led on.");
                }

            case R.id.bt_off:
                try
                {
                    Led_demo_service.led_set_OFF(1);
                    Log.e(LOG_TAG, "set led off is execute.");
                    break;
                } catch (RemoteException e)
                {
                    Log.e(LOG_TAG, "Remote Exception while set led off.");
                }
		}
	};
}
