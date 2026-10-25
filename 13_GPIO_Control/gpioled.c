#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>        // For GPIO functions
#include <linux/init.h>


#define GPIO_PIN 20   

#define OFFSET 512


int ret,gpio=GPIO_PIN+OFFSET;

static int __init gpio_driver_init(void)
{

    pr_info("GPIO Driver Init: Requesting GPIO %d\n",GPIO_PIN);

    // Request the GPIO
    ret = gpio_request(gpio, "gpio_test");
   if (ret) {
        pr_err("Failed to request GPIO %d\n",GPIO_PIN);
        return ret;
    }

    gpio_direction_output(gpio,0);


    // Turn GPIO ON
    gpio_set_value(gpio, 1);
    pr_info("GPIO %d set HIGH\n", GPIO_PIN);

    return 0;
}

static void __exit gpio_driver_exit(void)
{
    pr_info("GPIO Driver Exit: Freeing GPIO %d\n",GPIO_PIN);

    // Turn GPIO OFF before exit
    gpio_set_value(gpio,0);

    // Free the GPIO
    gpio_free(gpio);
}

module_init(gpio_driver_init);
module_exit(gpio_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("bandelavinod63029@gmail.com");
MODULE_DESCRIPTION("GPIO Driver for Raspberry Pi 4");
