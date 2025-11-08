#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

static int Tmodule_init(void)
{
    printk("Hello world!\n");
    return 0;
}

static void Tmodule_exit(void)
{
    printk("Bye hello world\n");

}

module_init(Tmodule_init);
module_exit(Tmodule_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("bandelavinod63029@gmail.com");
MODULE_DESCRIPTION("Hello program");