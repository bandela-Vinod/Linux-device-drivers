#include<linux/module.h>
#include<linux/slab.h>
#include<linux/fs.h>
#include<linux/mm.h>
#include<asm/page.h>
#include<asm/io.h>


#define MYMAJOR 64
#define DEVNAME "mydev"

static void *my_data;

static int my_mmap(struct file *file,struct vm_area_struct *vma)
{
	int status;

	vma->vm_pgoff= virt_to_phys(my_data)>>PAGE_SHIFT;

	status= remap_pfn_range(vma, vma->vm_start,vma->vm_pgoff,vma->vm_end-vma->vm_start,vma->vm_page_prot);

	if(status)
	{
		printk("my_mmap -Error remap_pfn_range: %d\n",status);
		return -EAGAIN;
	}
	return 0;
}

static struct file_operations fops=
{
	.owner= THIS_MODULE,
	.mmap = my_mmap,
};



static int Tmodule_init(void)
{
	int status;
        printk("my_mmap -Hello!\n");
        my_data=kzalloc(PAGE_SIZE,GFP_DMA);

	if(!my_data)
		return -ENOMEM;

	printk("my_mmap - I have allocated a page (%ld Bytes)\n",PAGE_SIZE);
	printk("my_mmap - PAGESHIFT :%d\n", PAGE_SHIFT);

	status= register_chrdev(MYMAJOR,DEVNAME,&fops);

	if(status<0)
	{
		printk("my_mmap -Error registering device number!\n");
		kfree(my_data);
		return status;
	}

        return 0;
}

static void Tmodule_exit(void)
{
	if(my_data)
	   kfree(my_data);

	unregister_chrdev(MYMAJOR, DEVNAME);
        printk("my_mmap bye\n");

}

module_init(Tmodule_init);
module_exit(Tmodule_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("bandelavinod63029@gmail.com");
MODULE_DESCRIPTION("mmap syscall program");
