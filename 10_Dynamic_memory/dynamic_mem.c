#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/slab.h>


u32 *p1,*p2;

static int myinit(void)
{

	printk("init module\n");
	p1=kmalloc(sizeof(u32),GFP_KERNEL);
	if(p1==NULL)
	{
		printk("memory not allocated\n");
        	return -1;
	}

	printk("Before val assign : 0x%x\n",*p1);
	*p1=0xabcdef01;
	printk("After val assign  : 0x%x\n",*p1);

	p2=kzalloc(sizeof(u32),GFP_KERNEL);
        if(p2==NULL)
	{
	       printk("memory not allocated\n");
	       return -1;
	}

	printk("Before val assign  : 0x%x\n",*p2);
	*p2=0x04030201;
	printk("After val assign   : 0x%x\n",*p2);

	return 0;

}

static void myexit(void)
{
     printk("exit module\n");
     kfree(p1);
     kfree(p2);
}

module_init(myinit);
module_exit(myexit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("bandelavinod63029@gmail.com");
MODULE_DESCRIPTION("Dynamic memory allocation in linux kernal module");
	





