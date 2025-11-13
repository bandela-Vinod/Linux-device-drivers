#include<linux/init.h>
#include<linux/module.h>
#include<linux/proc_fs.h>


char buf[128];

static struct proc_dir_entry *custom_proc_node;

static ssize_t p_read(struct file * file_pointer,
                      char *user_space_buffer,
                      size_t count,
                      loff_t *offset)


{
    
    size_t len=strlen(buf);
    int result;
    printk("p_read\n");

    if(*offset>=len)
    return 0;

    result=copy_to_user(user_space_buffer,buf,len);

    *offset+=len;

    return len;
}


static ssize_t p_write(struct file *file, 
                       const char __user *buffer,
                       size_t count, 
                       loff_t *pos)
{
    

    if (count > sizeof(buf) - 1)
        return 0;

    if (copy_from_user(buf, buffer, count))
        return 0;

    buf[count] = '\0';
    printk(KERN_INFO "User wrote: %s\n", buf);

    return count; 
}

struct proc_ops driver_proc_ops=
{
    
    .proc_write=p_write,
    .proc_read=p_read
};

static int p_module_init(void)
{
    custom_proc_node=proc_create("proc_read_write",0,NULL,&driver_proc_ops);
    printk("p_module_init: exit \n");
    return 0;
}

static void p_module_exit(void)
{
    proc_remove(custom_proc_node);
    printk("p_module_exit: exit\n");

}

module_init(p_module_init);
module_exit(p_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("bandelavinod63029@gmail.com");
MODULE_DESCRIPTION("proc_read_write");
