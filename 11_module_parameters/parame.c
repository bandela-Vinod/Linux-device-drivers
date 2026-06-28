#include<linux/init.h>
#include<linux/module.h>

static unsigned int gpio_nr=12;
static char *device_name="testdevice";


module_param(gpio_nr,uint,S_IRUGO);
module_param(device_name,charp,S_IRUGO);

MODULE_PARM_DESC(gpio_nr,"number of gpio to use in this kernal module");
MODULE_PARM_DESC(device_name,"Device name to use in this kernal Module");



static int Tmodule_init(void)
{

    printk("gpio_nr=%u\n", gpio_nr);
    printk("device_name=%s\n", device_name);
    printk("Hello kernal!\n");
    return 0;
}

static void Tmodule_exit(void)
{
    printk("Bye kernal\n");

}

module_init(Tmodule_init);
module_exit(Tmodule_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("bandelavinod63029@gmail.com");
MODULE_DESCRIPTION("Use of Parameters");
