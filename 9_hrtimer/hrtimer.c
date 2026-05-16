#include <linux/module.h>
#include <linux/init.h>
#include <linux/hrtimer.h>
#include <linux/jiffies.h>
#include <linux/ktime.h>

static struct hrtimer  my_hrtimer;
u64 start_t;


static enum hrtimer_restart test_hrtimer_handler(struct hrtimer *timer) {
	// Get current time 
	u64 now_t = jiffies;
	printk("start_t - now_t = %u\n", jiffies_to_msecs(now_t - start_t));
	return HRTIMER_NORESTART;
}


static int  moduleinit(void) {
	printk("Hello, Kernel!\n");

	/* Init of hrtimer */
	
	hrtimer_setup(&my_hrtimer, test_hrtimer_handler,CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	start_t = jiffies;
	hrtimer_start(&my_hrtimer, ms_to_ktime(100), HRTIMER_MODE_REL);
	return 0;
}
static void  moduleExit(void) {
	hrtimer_cancel(&my_hrtimer);
	printk("Goodbye, Kernel\n");
}

module_init(moduleinit);
module_exit(moduleExit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("bandelavinod63029@gmail.com");
MODULE_DESCRIPTION("High Resolution Timer");

