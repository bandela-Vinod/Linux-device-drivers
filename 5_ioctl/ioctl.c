
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/ioctl.h>
#include<linux/uaccess.h>



static int major;

#define WR_DATA _IOW('a','a',int32_t*)
#define RD_DATA _IOR('a','b',int32_t*)

static int my_open(struct inode *inode,struct file *filp)
{
    pr_info("open -Major: %d, Minor %d \n",imajor(inode),iminor(inode));

    return 0;
}

static int my_release(struct inode *inode,struct file *filp)
{
    pr_info("release - file is closed\n",filp->f_flags);
    return 0;
}




int32_t val;

static long int my_ioctl(struct file *file,unsigned cmd, unsigned long arg)
{


        switch(cmd)
        {
                case WR_DATA:
                        if(copy_from_user(&val,(int32_t *) arg,sizeof(val)))
                           printk("ioctl_example - Error copying data from user!\n");
                        else
                           printk("ioctl_example -Update the val: %d\n",val);
                        break;
                case RD_DATA:
                        if(copy_to_user((int32_t *) arg,&val,sizeof(val)))
                           printk("ioctl_example - Error copying data to user!\n");
                        else
                           printk("ioctl_example - The val copied!\n");
                        break;
        }

        return 0;
}

static struct file_operations fops={
    .open=my_open,
    .release=my_release,
    .unlocked_ioctl=my_ioctl
};




static int Tmodule_init(void)
{

    printk("ioctl init function\n");

    major=register_chrdev(0,"ioctl",&fops);

    if(major<0)
    {
        pr_err("ioctl - Error registrating chrdev\n");
        return major;
    }
    pr_info("ioctl -Major Device number: %d\n",major);
    return 0;
}

static void Tmodule_exit(void)
{
    unregister_chrdev(major,"ioctl");
    printk("ioctl exit function\n");
}

module_init(Tmodule_init);
module_exit(Tmodule_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("bandelavinod63029@gmail.com");
MODULE_DESCRIPTION("ioctl program");

