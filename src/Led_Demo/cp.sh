#!/bin/bash
TOP=/home/android/gaoxh/AOSP/LED_DEMO/TI-Android-ICS-4.0.3-DevKit-EVM-SK-3.0.1

if [ "$1" == "install" ]
then
	echo "install..."
	#hal
	cp -rvf hardware/libhardware/include/hardware/led_demo_hal.h $TOP/hardware/libhardware/include/hardware
	cp -rvf hardware/libhardware/modules/led_demo_hal $TOP/hardware/libhardware/modules
	#aidl
	cp -rvf frameworks/base/core/java/android/os/* $TOP/frameworks/base/core/java/android/os
	cd $TOP
	patch -p0 < $OLDPWD/frameworks/base/Android.mk.patch
	cd $OLDPWD
	#jni
	cp -rvf frameworks/base/services/jni/com_android_server_led_demo_service.cpp $TOP/frameworks/base/services/jni
	cd $TOP
	patch -p0 < $OLDPWD/frameworks/base/services/jni/Android.mk.patch
	patch -p0 < $OLDPWD/frameworks/base/services/jni/onload.cpp.patch
	cd $OLDPWD
	#service
	cp -rvf frameworks/base/services/java/com/android/server/Led_demo_Service.java $TOP/frameworks/base/services/java/com/android/server
	cd $TOP
	patch -p0 < $OLDPWD/frameworks/base/services/java/com/android/server/SystemServer.java.patch
	cd $OLDPWD
	#activity
	cp -rvf packages/experimental/Tiny4412_led_demo $TOP/packages/experimental
elif [ "$1" == "remove" ]
then
	echo "remove..."
	cd $TOP
	rm -rvf hardware/libhardware/include/hardware/led_demo_hal.h hardware/libhardware/modules/led_demo_hal frameworks/base/core/java/android/os/ILed_demo_service.aidl frameworks/base/core/java/android/os/ICallback.aidl frameworks/base/services/jni/com_android_server_led_demo_service.cpp frameworks/base/services/java/com/android/server/Led_demo_Service.java packages/experimental/Tiny4412_led_demo
	patch -R -p0 < $OLDPWD/frameworks/base/Android.mk.patch
	patch -R -p0 < $OLDPWD/frameworks/base/services/jni/Android.mk.patch
	patch -R -p0 < $OLDPWD/frameworks/base/services/jni/onload.cpp.patch
	patch -R -p0 < $OLDPWD/frameworks/base/services/java/com/android/server/SystemServer.java.patch
	cd $OLDPWD
else
	echo "$0 <install/remove>"
	echo $TOP
	exit
fi
