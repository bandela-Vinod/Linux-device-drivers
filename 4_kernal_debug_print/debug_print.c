#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

static int Tmodule_init(void)
{
    printk(KERN_INFO"init info\n");
    printk(KERN_WARNING"Log level warning\n");
    printk(KERN_DEBUG"Log level bebug\n");
    printk(KERN_ALERT"Log level Alert\n");
    return 0;
}

static void Tmodule_exit(void)
{
    pr_info("exit function\n");
    pr_err("Log level error\n");
    pr_emerg("kernal emergency\n");
    
}

module_init(Tmodule_init);
module_exit(Tmodule_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("bandelavinod63029@gmail.com");
MODULE_DESCRIPTION("kernal debuging use prink");
