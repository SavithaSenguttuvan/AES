/*
 * LED_Char_Module.c 
 *
 * @author: Savitha Senguttuvan
 * @brief:  Linux kernel module for char driver
 */
#include <linux/init.h>           
#include <linux/module.h>         
#include <linux/device.h>         
#include <linux/kernel.h>        
#include <linux/fs.h>             
#include <asm/uaccess.h>          
#include <linux/slab.h>
#include <linux/gpio.h> 

#define  BBG_LED      (53)            /* GPIO for the LED */
#define  DEVICE_NAME  ("LED_Driver")     /* Device name */
#define  CLASS_NAME   ("LED_Class")         /* Char device driver */

#define DEF_PERIOD     (5000)
#define DEF_DUTY       (75)
#define DEF_ON_PERIOD  (2000)
#define DEF_OFF_PERIOD (3000)
#define DEF_STATUS     (true)

MODULE_LICENSE("GPL");            
MODULE_AUTHOR("Savitha_Senguttuvan");    
MODULE_DESCRIPTION("BBG Driver");  
MODULE_VERSION("0.1");   

static int    major_num;                    /* Device Major Number */
static struct class*  Led_Class_struct  = NULL; /* The device-driver class struct pointer */
static struct device* Led_Device_struct = NULL; /* The device-driver device struct pointer */
static bool led_value = false;

static int     device_driver_open(struct inode *, struct file *);
static int     device_driver_release(struct inode *, struct file *);
static ssize_t device_driver_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_driver_write(struct file *, const char *, size_t, loff_t *);

static struct timer_list new_timer;

static int period = DEF_PERIOD;
static int duty_cycle = DEF_DUTY;
static int on_period = DEF_ON_PERIOD;
static int off_period = DEF_OFF_PERIOD;
static int status = DEF_STATUS;
static char query_type = 'A';

typedef struct 
{
   int32_t led_duty_cycle;
   int32_t led_period;
   int32_t led_status;
}LED_info;

LED_info led_information;

static struct file_operations file_ops =     /* File operation registration */
{
   .open = device_driver_open,
   .read = device_driver_read,
   .write = device_driver_write,
   .release = device_driver_release,
};

void callback_timer( unsigned long data )     /* Callback function after timer expiry */
{
  int ret_val;
  static int callback_count = 0; 
  if(callback_count == 0)                    /* Off duration */
  {
      led_value = false;
      gpio_set_value(BBG_LED,led_value);
      printk(KERN_INFO "Led off period is %d\n",off_period);
      ret_val = mod_timer( &new_timer, jiffies + msecs_to_jiffies(off_period) ); 
      if (ret_val) printk("Callback: Error1\n");
      callback_count = 1;
  }
  else
  {
      led_value = true;                      /* On duration */
      gpio_set_value(BBG_LED,led_value);
      printk(KERN_INFO "Led on period is %d\n",on_period);
      ret_val = mod_timer( &new_timer, jiffies + msecs_to_jiffies(on_period) ); 
      if (ret_val) printk("Callback: Error2\n"); 
      callback_count = 0;
  }
  if (ret_val) printk("Callback: Error\n");
}


static int __init mod_init(void)
{
   int return_val;
   major_num = register_chrdev(0, DEVICE_NAME, &file_ops);		   /* Major number allocation */
   if (major_num<0){
      printk(KERN_ALERT "mod_init: Failure - Major num allocation\n");
      return major_num;
   }
   Led_Class_struct = class_create(THIS_MODULE, CLASS_NAME);		     /* Device class registration */
   if (IS_ERR(Led_Class_struct)){                
	  unregister_chrdev(major_num, DEVICE_NAME);
	  printk(KERN_ALERT "mod_init: Failed - register device class\n");
	  return PTR_ERR(Led_Class_struct);          
   }
   
   Led_Device_struct = device_create(Led_Class_struct, NULL, MKDEV(major_num, 0), NULL, DEVICE_NAME); /*Device river registration */
   if (IS_ERR(Led_Device_struct)){               
      class_destroy(Led_Class_struct);           
      unregister_chrdev(major_num, DEVICE_NAME);
      printk(KERN_ALERT "mod_init: Failed to create the device\n");
      return PTR_ERR(Led_Device_struct);
   }

   if(gpio_is_valid(BBG_LED)==0)             /* Check the availability of the GPIO */
   {
      printk(KERN_ALERT "mod_init: Invalid GPIO\n");
   }
   if(gpio_direction_output(BBG_LED, 0))     /* Set the direction of the GPIO */ 
   {
      printk(KERN_ALERT "mod_init: LED direction failure\n");
   }  
   if(gpio_export(BBG_LED, false))           /* GPIO Export */
   {
      printk(KERN_ALERT "mod_init: LED export failure\n");
   } 

   led_information.led_duty_cycle = DEF_DUTY;
   led_information.led_period = DEF_PERIOD;
   led_information.led_status = 1;

   led_value = DEF_STATUS;                               /* LED Value */
   gpio_set_value(BBG_LED,led_value);        
   setup_timer( &new_timer, callback_timer, 0 );   /* Setting the timer */ 
   return_val = mod_timer( &new_timer, jiffies + msecs_to_jiffies(on_period) );  /* Modifies the expires field for the timer */
   if (return_val) printk("mod_init: Error\n");
   return 0;
}

static void __exit mod_exit(void){
   int return_value;
   device_destroy(Led_Class_struct, MKDEV(major_num, 0));     /* Remove device */
   class_unregister(Led_Class_struct);                        /* Device class unregister */
   class_destroy(Led_Class_struct);                           /* Device class remove */
   unregister_chrdev(major_num, DEVICE_NAME);             /* Major number unregister */
   
   return_value = del_timer_sync( &new_timer );           /* Delete the timer */
   if (return_value) printk("Mod_Exit: The timer has not been deleted\n"); 
   gpio_unexport(BBG_LED);

   printk(KERN_INFO "Mod_exit: Bye\n");
}

static int device_driver_open(struct inode *inodep, struct file *filep){
   filep->private_data = (void *)&led_information; 
   printk(KERN_INFO "Driver_Open: Device opened \n");
   return 0;
}

static ssize_t device_driver_read(struct file *filep, char *buffer, size_t len, loff_t *offset){
   char inp_arr[20];
   int error_count = 0;
   filep->private_data = (void *)&led_information;
   if(query_type == 'A')
   {
      sprintf(inp_arr,"%d",led_information.led_period);           /* Creating a buffer with the period and the duty cycle */
   }
   else if(query_type == 'B')
   {
      sprintf(inp_arr,"%d",led_information.led_duty_cycle);           /* Creating a buffer with the period and the duty cycle */
   }
   else if(query_type == 'C')
   {
      sprintf(inp_arr,"%d",led_information.led_status);           /* Creating a buffer with the period and the duty cycle */
   }
   else if(query_type == 'D')
   {
      sprintf(inp_arr,"%d %d %d",led_information.led_period,led_information.led_duty_cycle,led_information.led_status); 
   }
   
   error_count = copy_to_user(buffer, inp_arr, 20);      /* Copy from kernel space to user space */
   if (error_count==0){            
      return (0);  
   }
   else {
      printk(KERN_INFO "Driver_Read: Failed to send few characters \n");
      return -EFAULT;              
   }
   return 0;
}

static ssize_t device_driver_write(struct file *filep, const char *buffer, size_t len, loff_t *offset){
   int return_val;
   char *buf = (char*)kmalloc((len), GFP_KERNEL);
   
   if (copy_from_user(buf, buffer, len))   /* copy input buffer, which is in the user’s address space, into buf */
        return -EFAULT;

   sscanf( buf, "%d %d %d %d %d %c", &period, &duty_cycle, &on_period, &off_period, &status,&query_type );
 
   led_information.led_duty_cycle = duty_cycle;
   led_information.led_period = period;
   led_information.led_status = status;

   printk(KERN_INFO "Write: The period is %d \n",period);
   printk(KERN_INFO "Write: The duty_cycle is %d \n",duty_cycle);
   printk(KERN_INFO "Write: The on_period is %d \n",on_period);
   printk(KERN_INFO "Write: The off_period is %d \n",off_period);
   printk(KERN_INFO "Write: The status is %d \n",status);
   printk(KERN_INFO "Write: The query_char is %c \n",query_type);
   
   if(status != 0)
   {
      led_value = true;                               /* LED Value */
      gpio_set_value(BBG_LED,led_value);  
      setup_timer( &new_timer, callback_timer, 0 );   /* Setting the timer */ 
      return_val = mod_timer( &new_timer, jiffies + msecs_to_jiffies(on_period) );  /* Modifies the expires field for the timer */
      if (return_val) printk("Write: Mod timer Error\n");
   }
   else
   {
      led_value = false;                               /* LED Value */
      gpio_set_value(BBG_LED,led_value);  
      return_val = del_timer_sync( &new_timer );     /* Stop timer */
      if (return_val) printk("Write: Timer off Error\n");
   }
   
   if(buf != NULL)
   {
      kfree(buf);
      buf = NULL;
   }
   filep->private_data = (void *)&led_information;
   return 0;
}

static int device_driver_release(struct inode *inodep, struct file *filep){ //called when a file structure is being released
   printk(KERN_INFO "Driver_Release: Device closed\n");
   return 0;
}

module_init(mod_init);
module_exit(mod_exit);