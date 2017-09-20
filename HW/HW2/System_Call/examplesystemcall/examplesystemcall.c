#include <linux/kernel.h>
#include<linux/syscalls.h>
#include<linux/slab.h>
#include<linux/gfp.h>

SYSCALL_DEFINE3(examplesystemcall,int32_t*, input_buffer, size_t, input_size, int32_t*, output_buffer)
{
	int32_t i = 0;
	int32_t j = 0;
	int32_t temp_var = 0;										/* Temporary variable */
	int32_t *buf = (int32_t*)kmalloc((sizeof(int32_t)*input_size), GFP_KERNEL);	/* Allocate memory */

	if(input_buffer == NULL)									/* Checks if input buffer is Null*/
		return ENODATA;

	if(output_buffer == NULL)									/* Checks if output buffer is Null*/
		return ENODATA;	

	if(input_size < 1)											/* Check the input buffer size */
	{
		return ENODATA;
	}	
	
	if(buf == NULL)												/* Checks if the allocated memory is Null*/
		return ENODATA;

	printk("Enter_Time\n");
	printk("The size of the buffer is %ld\n",input_size);
    
    if (copy_from_user(buf, input_buffer, input_size*sizeof(int32_t)))	/* copy input buffer, which is in the user’s address space, into buf */
        return -EFAULT;

    printk("Sorting the buffer started\n");

    for(i=0;i<input_size;i++)											/* Sort */
	{
	    for(j=0;j<input_size-i-1;j++)
	    {
	        if((*(buf+j)) < (*(buf+j+1)))
	        {
	            temp_var = *(buf+j);
	            *(buf+j) = *(buf+j+1);
	            *(buf+j+1) = temp_var;
	        }
	    }
	}

    printk("Sorting Completed\n");

    if (copy_to_user(output_buffer, buf, input_size*sizeof(int32_t)))	/* copy buf into output buffer, which is in the user’s address space */
        return -EFAULT;

    kfree(buf);															/* Free the allocated memory */
    printk("Exit Time\n");
	return 0;
}