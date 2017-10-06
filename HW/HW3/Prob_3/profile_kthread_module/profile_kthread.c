#include <linux/module.h>
#include <linux/init.h>      // included for __init and __exit macros
#include <linux/kernel.h>
#include <linux/kthread.h>  // for threads
#include <linux/timex.h> 

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Savitha");
MODULE_DESCRIPTION("Module to profile kthread");

static struct task_struct *thread1;

int display(void* a)
{
	printk(KERN_INFO "In thread1");                            
	return 0;
}

static int profile_init(void)
{
    cycles_t initial_number;                                    /* Clock cycles before creating thread */
    cycles_t end_number;                                        /* Clock cycles after creating thread */
    initial_number = get_cycles();
    thread1 = kthread_create(&display,NULL,"thread1");          /* Create a thread in kernel space */
    end_number = get_cycles();
    printk("CPU cycles taken is %llu \n", (end_number - initial_number)); 
    return 0;    // Non-zero return means that the module couldn't be loaded.
}


static void profile_exit(void)
{
    kthread_stop(thread1);     	                                /* Destroy thread*/
    printk("Terminating module\n"); 
}

module_init(profile_init);
module_exit(profile_exit);