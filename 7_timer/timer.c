#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/jiffies.h>
#include<linux/timer.h>


static struct timer_list my_timer;

void timer_callback(struct timer_list * data)
{
        printk("Timer call back\n");
}


static int Tmodule_init(void)
{
    printk("Hello kernal\n");

 /* Initialize timer */

    timer_setup(&my_timer,timer_callback,0);
    mod_timer(&my_timer, jiffies + msecs_to_jiffies(5000));

    return 0;
}

static void Tmodule_exit(void)
{
    printk("Bye kernal\n");
    timer_delete(&my_timer);

}

module_init(Tmodule_init);
module_exit(Tmodule_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("bandelavinod63029@gmail.com");
MODULE_DESCRIPTION("Timer program");


