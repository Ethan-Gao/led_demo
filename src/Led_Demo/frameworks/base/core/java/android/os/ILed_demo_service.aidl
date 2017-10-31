package android.os;
import android.os.ICallback;

interface ILed_demo_service
{
    void led_set_ON(int val);
    void led_set_OFF(int val);

	void registerCallback(ICallback cb);  
	void unregisterCallback(ICallback cb);
}
