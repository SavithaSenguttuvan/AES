#include <linux/module.h>    // included for all kernel modules
#include <linux/init.h>      // included for __init and __exit macros
#include <linux/moduleparam.h>
#include <linux/timer.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Savitha");
MODULE_DESCRIPTION("Module to log jiffies every 500ms");

int timer_log = 500;
static struct timer_list new_timer;

module_param(timer_log,int,S_IRUSR | S_IWUSR); 

void callback_timer( unsigned long data )                                         /* Callback function after timer expiry */
{
  int ret_val;
  static int callback_count = 0;	
  printk("The callback is called %d number of times\n",++callback_count);         /* Print the number of times the callback called */
  printk( "Current jiffies number is (%ld)\n", jiffies );                         /* Print the current jiffies count */
  ret_val = mod_timer( &new_timer, jiffies + msecs_to_jiffies(timer_log) );       /* Modifies the expires field for the timer */
  if (ret_val) printk("Error\n");
}
 
static int timer_module_init(void)                                                /* Init module */
{
	  int return_val;
    printk(KERN_INFO "Loaded the module\n");
    setup_timer( &new_timer, callback_timer, 0 );                                 /* Initizlize the timer with default values */
    printk( "Timer fires in %dms and the current jiffies value is (%ld)\n",timer_log,jiffies );
    return_val = mod_timer( &new_timer, jiffies + msecs_to_jiffies(timer_log) );  /* Modifies the expires field for the timer */
  	if (return_val) printk("Error\n");
    return 0;    
}

static void timer_module_exit(void)                                               /* Exit Module */
{	
  int return_value;
	return_value = del_timer_sync( &new_timer );                                     /* Delete the timer */
	if (return_value) printk("The timer has not been deleted\n"); 
  printk(KERN_INFO "Cleaning up module.\n");
}

module_init(timer_module_init);
module_exit(timer_module_exit);