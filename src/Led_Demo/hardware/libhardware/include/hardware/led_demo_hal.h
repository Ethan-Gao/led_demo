#ifndef ANDROID_LED_DEMO_HAL_H
#define ANDROID_LED_DEMO_HAL_H

#include <hardware/hardware.h>

__BEGIN_DECLS

#define LED_DEMO_HARDWARE_MODULE_ID   "led_demo_hal"
#define LED_DEMO_HARDWARE_DEVICE_ID   "led_demo"


struct led_demo_module_t
{
	struct hw_module_t common;
};

struct led_demo_device_t
{
	struct hw_device_t common;
	int fd;
	int (*set_on)(struct led_demo_device_t *dev, int val);
	int (*set_off)(struct led_demo_device_t *dev, int val);
};

__END_DECLS


#endif
