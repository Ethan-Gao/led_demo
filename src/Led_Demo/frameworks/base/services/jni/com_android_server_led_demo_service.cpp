#define LOG_TAG  "LED_DEMO_Service_JNI"

#include "jni.h"
#include "JNIHelp.h"
#include "android_runtime/AndroidRuntime.h"

#include <utils/misc.h>
#include <utils/Log.h>
#include <hardware/hardware.h>
#include <hardware/led_demo_hal.h>

#include <stdio.h>


namespace android
{
    static void cb_test(JNIEnv *env, jobject obj,jstring info){
        LOGI("executing cb_test...");   
        jclass cls = env->FindClass("com/android/server/Led_demo_Service");
        if(cls == NULL) {
            LOGE("can't find com/android/server/Led_demo_Service");
            return;
        }
        (jclass) env->NewGlobalRef(cls);
        jmethodID jmid = env->GetMethodID(cls, "cb_output", "(Ljava/lang/String;)V");
        if(jmid == NULL){
            LOGE("no cb_output in Led_demo_Service class");
            return;
        }
        //jstring info = env->NewStringUTF(out);
        env->CallVoidMethod(obj,jmid,info);
        env->ReleaseStringUTFChars(info,env->GetStringUTFChars(info, 0));      
    }

	static void led_demo_setOFF(JNIEnv *env, jobject clazz, jint ptr, jint value)
	{
		led_demo_device_t *device = (led_demo_device_t *)ptr;
		if(!device)
		{
			LOGE("Device led demo is not open.");
			return ;
		}

		int val = value;

		LOGI("Set value %d to device led demo.", val);
//cb_test(env,clazz,"Led Is Off");	env->NewStringUTF(out);
		cb_test(env,clazz,env->NewStringUTF("Led Is Off"));
		device->set_off(device, value);
	}

	static void led_demo_setON(JNIEnv *env, jobject clazz, jint ptr, jint value)
	{
		led_demo_device_t *device = (led_demo_device_t *)ptr;
		if(!device)
		{
			LOGE("Device led demo is not open.");
			return ;
		}

		int val = value;

		LOGI("Set value %d to device led demo.", val);
cb_test(env,clazz,env->NewStringUTF("Led Is On"));
		device->set_on(device, value);
	}
	

	static inline int led_demo_device_open(const hw_module_t *module, struct led_demo_device_t **device)
	{
		return module->methods->open(module, LED_DEMO_HARDWARE_DEVICE_ID, (struct hw_device_t **)device);	
	}

	static jint led_demo_init(JNIEnv *env, jclass clazz)
	{
		struct led_demo_module_t *module;
		struct led_demo_device_t *device;


		LOGI("Initializing HAL stub led ......");

		if(hw_get_module(LED_DEMO_HARDWARE_MODULE_ID, (const struct hw_module_t **)&module) == 0)
		{
			LOGE("Device led demo found.");

			if(led_demo_device_open(&(module->common), &device))
			{
				LOGI("Device led demo is open.");
				return (jint)device;
			}

			LOGE("Failed to open device led.");

			return 0;
		}

		LOGE("Failed to get HAL stub led demo.");
		return 0;
	}

	static const JNINativeMethod  method_table[] =
	{
		{"init_native", "()I", (void *)led_demo_init},
		{"set_OFF_native", "(II)V", (void *)led_demo_setOFF},
		{"set_ON_native", "(II)V", (void *)led_demo_setON},
	};

	int register_android_server_led_demo_service(JNIEnv *env)
	{
		return jniRegisterNativeMethods(env, "com/android/server/Led_demo_Service", 
			method_table, NELEM(method_table));
	}

};

