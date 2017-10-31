#!/bin/bash
TOP=/home/android/gaoxh/AOSP/LED_DEMO/TI-Android-ICS-4.0.3-DevKit-EVM-SK-3.0.1

echo "compiling..."
cd $TOP
#HAL
mmm ./hardware/libhardware/modules/led_demo_hal/
#AIDL
mmm ./frameworks/base/
#JNI
mmm ./frameworks/base/services/jni/
#JAVA
mmm ./frameworks/base/services/java/
#ACTIVITY
mmm ./packages/experimental/Tiny4412_led_demo/
cd -
