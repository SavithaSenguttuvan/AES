#include <linux/module.h>    // included for all kernel modules
#include <linux/init.h>      // included for __init and __exit macros
#include <linux/sched.h>
#include <linux/sched/task.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Savitha");
MODULE_DESCRIPTION("Module to find parent");

void display(struct task_struct *temp_ts)
{
	struct list_head *list;
	int32_t children_count = 0;
	printk("The process ID is %d\n",temp_ts->pid);								//Process ID
	printk("The process name is %s\n",temp_ts->comm);							//Process name
	printk("The process state is %ld\n",temp_ts->state);						//Process state

	list_for_each(list, &temp_ts->children) {									//Count the children for the current thread
		children_count++;
	}
	printk("The number of children for the thread with thread ID %d, is %d\n",temp_ts->pid,children_count);

}


static int ll_init(void)
{
	struct task_struct *temp_ts = current;										//Current thread

    for(temp_ts = current; temp_ts != &init_task; temp_ts = temp_ts->parent)	//Traversing from current thread to the init thread
    {
    	display(temp_ts);														//Function to display the process name, ID and state
    }
    printk("Init process details\n");											//Init process's details
    display(temp_ts);

    return 0;    // Non-zero return means that the module couldn't be loaded.
}

static void ll_exit(void)
{
    printk("Exiting the module\n");
}

module_init(ll_init);
module_exit(ll_exit);