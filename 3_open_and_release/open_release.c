#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>

static int major;

static int my_open(struct inode *inode,struct file *filp)
{
    pr_info("open_release -Major: %d, Minor %d \n",imajor(inode),iminor(inode));

    pr_info("open_release - filp->f_pos: %lld\n",filp->f_pos);
    pr_info("open_release - filp->f_mode: 0x%x\n",filp->f_mode);
    pr_info("open_release - filp->f_flags:0x%x\n",filp->f_flags);

    return 0;
}

static int my_release(struct inode *inode,struct file *filp)
{
    pr_info("open_release - file is closed\n",filp->f_flags);
    return 0;
}

static struct file_operations fops={
    .open=my_open,
    .release=my_release,
};

static int Tmodule_init(void)
{
    major=register_chrdev(0,"open_release",&fops);

    if(major<0)
    {
        pr_err("open_release - Error registrating chrdev\n");
        return major;
    }
    pr_info("open_release -Major Device number: %d\n",major);
    return 0;
}

static void Tmodule_exit(void)
{
    unregister_chrdev(major,"open_release");
    
}

module_init(Tmodule_init);
module_exit(Tmodule_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("bandelavinod63029@gmail.com");
MODULE_DESCRIPTION("open and release");
