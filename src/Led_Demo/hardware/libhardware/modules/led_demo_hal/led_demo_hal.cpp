#define LOG_TAG "LED_DEMO_HALSTUB"

#include <hardware/hardware.h>
#include <hardware/led_demo_hal.h>

#include <fcntl.h>
#include <errno.h>

#include <utils/Log.h>
#include <cutils/atomic.h>
#include <stdlib.h>

#define DEVICE_NAME    "/sys/class/leds/user_led/brightness"
#define MODULE_NAME    "led_demo"
#define MODULE_AUTHOR  "pengdonglin137@163.com"

#define LED_ON  0x40044c00
#define LED_OFF 0x40044c01


static int led_demo_open(const struct hw_module_t* module, const char* id,
		struct hw_device_t** device);

static int led_demo_close(struct hw_device_t* device);

static int led_demo_set_on(struct led_demo_device_t *dev, int val);

static int led_demo_set_off(struct led_demo_device_t *dev, int val);


static hw_module_methods_t led_demo_module_methods =
{
	open:led_demo_open,
};

struct led_demo_module_t HAL_MODULE_INFO_SYM = 
{
	common:{
		tag:HARDWARE_MODULE_TAG,
		version_major:1,
		version_minor:0,
		id:LED_DEMO_HARDWARE_MODULE_ID,
		name:MODULE_NAME,
		author:MODULE_AUTHOR,
		methods:&led_demo_module_methods,
	}
};

static int led_demo_open(const struct hw_module_t* module, const char* id,
		struct hw_device_t** device)
{
	if(!strcmp(id, LED_DEMO_HARDWARE_DEVICE_ID))
	{
		struct led_demo_device_t *dev;

		dev = (struct led_demo_device_t *)malloc(sizeof(struct led_demo_device_t));
		if(!dev)
		{
			LOGE("Failed to alloc space for struct led_demo_device_t.");
			return -EFAULT;
		}

		memset(dev, 0, sizeof(struct led_demo_device_t));

		dev->common.tag = HARDWARE_DEVICE_TAG;
		dev->common.version = 0;
		dev->common.module = (struct hw_module_t *)module;
		dev->common.close = led_demo_close;
		dev->set_on = led_demo_set_on;
		dev->set_off = led_demo_set_off;

		if((dev->fd = open(DEVICE_NAME, O_RDWR)) == -1)
		{
			LOGE("Failed to open device %s ---- %s\n.", DEVICE_NAME, strerror(errno));
			free(dev);
			return -EFAULT;
		}

		*device = &(dev->common);

		LOGE("Open device file %s successfully.", DEVICE_NAME);

	}

	return -EFAULT;
}

static int led_demo_close(struct hw_device_t* device)
{
	struct led_demo_device_t *led_device = (struct led_demo_device_t *)device;
	if(led_device)
	{
		close(led_device->fd);
		free(led_device);
	}

	return 0;
}

static int led_demo_set_on(struct led_demo_device_t *dev, int val)
{
	if(!dev)
	{
		LOGE("Null dev pointer.");
		return -EFAULT;
	}
	
	system("echo 1 > /sys/class/leds/user_led/brightness");
	
	return 0;
	
}

static int led_demo_set_off(struct led_demo_device_t *dev, int val)
{
	if(!dev)
	{
		LOGE("Null dev pointer.");
		return -EFAULT;
	}
	
	system("echo 0 > /sys/class/leds/user_led/brightness");
 
	return 0;
	
}

