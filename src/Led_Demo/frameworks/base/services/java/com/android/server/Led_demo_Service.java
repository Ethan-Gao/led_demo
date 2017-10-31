package com.android.server;

import android.content.Context;
import android.os.ILed_demo_service;
import android.util.Slog;

import android.os.RemoteCallbackList;
import android.os.ICallback;
import android.os.RemoteException;

public class Led_demo_Service extends ILed_demo_service.Stub
{
	private static final String TAG = "Led_demo_Service";
	private RemoteCallbackList<ICallback> mCallbacks = new RemoteCallbackList<ICallback>(); 
	private int mPtr = 0;

	Led_demo_Service()
	{
		mPtr = init_native();

		if(mPtr == 0)
		{
			Slog.e(TAG, "Failed to initialize Led demo Service.");
		}
	}

	public void led_set_ON(int val)
	{
		if(mPtr == 0)
		{
			Slog.e(TAG, "Led demo Service is not initialized.");
			return;
		}

		set_ON_native(mPtr, val);
	}

	public void led_set_OFF(int val)
	{
		if(mPtr == 0)
		{
			Slog.e(TAG, "Led demo Service is not initialized.");
			return;
		}

		set_OFF_native(mPtr, val);
	}


	public native int init_native();
	public native void set_OFF_native(int mPtr, int val);
	public native void set_ON_native(int mPtr, int val);
	 
	public void unregisterCallback(ICallback cb){  
		if(cb != null) mCallbacks.unregister(cb);  
	}  
 
	public void registerCallback(ICallback cb){  
		if(cb != null)   mCallbacks.register(cb);
	} 
	
	public void cb_output(String out){
		int N = mCallbacks.beginBroadcast(); 
		Slog.i(TAG, "mCallbacks.beginBroadcast() is " + N);
		try {  
			for (int i = 0; i < N; i++)  
				mCallbacks.getBroadcastItem(i).showResult(out); 
		} catch (RemoteException e) {  
			Slog.e(TAG, "cb_output RemoteException", e);  
		} 
		mCallbacks.finishBroadcast();
	}
};

