#include<linux/module.h>
#include<linux/init.h>
#include<linux/kthread.h>
#include<linux/sched.h>
#include<linux/delay.h>
#include<linux/mutex.h>

static struct task_struct *kthread_1,*kthread_2;
static int t1=1,t2=2;
static struct mutex lock;

int thread_function(void * thread_nr)
{
	int delay[]={100,1000,500};
	int t_nr=*(int*) thread_nr;
        
	
	printk("my mutex - Thread %d is excuted\n",t_nr);
	mutex_lock(&lock);
	printk("my mutex - Thread %d is in critical section\n",t_nr);
	msleep(delay[t_nr]);
	printk("my mutex - Thread %d is leaving the critical section\n",t_nr);
	mutex_unlock(&lock);
	printk("my mutex - Thread %d finished execution\n",t_nr);

	return 0;
}


static int Tmodule_init(void)
{
    printk("mymutex -Init threads\n");
    
    mutex_init(&lock);

    kthread_1= kthread_create(thread_function,&t1,"kthread_1");

    if(kthread_1 !=NULL)
    {
	    wake_up_process(kthread_1);
	    printk("my mutex -thread 1 was created and is running now\n");
    }
    else 
    {
	    printk("my mutex -Thread 1 could not be created\n");
	    return -1;
    }

    kthread_2 = kthread_run(thread_function,&t2,"kthread_2");

    if(kthread_2 != NULL)
    {
	    printk("my mutex - Thread 2 was created and is running now \n");
    }
    else
    {
	    printk("my mutex - Thread 2 could not be created\n");
	    kthread_stop(kthread_1);
	    return -1;
    }

    printk("my mutex - Both threads are running now\n");



    return 0;
}

static void Tmodule_exit(void)
{
    printk("My mutex - Stop both threads\n");

}

module_init(Tmodule_init);
module_exit(Tmodule_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("bandelavinod63029@gmail.com");
MODULE_DESCRIPTION("mutex program");



