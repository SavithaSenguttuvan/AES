#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "circbuf.h"

CB_t CircBuffer;
CB_t * CircBufferPtr = &CircBuffer;

int main()
{
    CB_status buffer_status;
	size_t buffer_length = 7;
	uint32_t no_of_items = 10;
	uint32_t data = 1;
	uint32_t removed_data;
	
	buffer_status = CB_init(&CircBufferPtr,buffer_length);		/* Initializing the circular buffer with length buffer_length */
	
	if(buffer_status == BUFF_NO_ERR)
	{
	    while(no_of_items)
	    {
	        if((CB_is_full(CircBufferPtr)) == BUFF_NO_ERR)
    	    {
        	    buffer_status = CB_buffer_add_item(CircBufferPtr,data++);		/* Add items into the buffer */
    	    }
    	    else
            {
                printf("Buffer full\n");
                break;
            }
	        no_of_items--;
	    }
	    printf("The current number of elements in the buffer is %d\n",CB_size(CircBufferPtr));
	    printf("Dumping\n");
	    CB_buff_dump(CircBufferPtr);											/* Print the values in the buffer */
	    
	    no_of_items = 10;
	    while(no_of_items)
	    {
	        if((CB_is_full(CircBufferPtr)) == BUFF_NO_ERR)
    	    {
        	    buffer_status = CB_buffer_add_item(CircBufferPtr,data++);		/* Add new items into the buffer */
    	    }
    	    else
            {
                printf("Buffer full\n");
                break;
            }
	        no_of_items--;
	    }
	    no_of_items = 10;
	    while(no_of_items)
	    {
	        if((CB_is_empty(CircBufferPtr)) == BUFF_NO_ERR)
    	    {
        	    buffer_status = CB_buffer_remove_item(CircBufferPtr,&removed_data);	/*Remove the item from the buffer */
        	    printf("The value is %d\n",removed_data);
        	    
    	    }
    	    else
    	    {
    	        printf("Buffer Empty\n");
    	        break;
    	    }
    	    no_of_items--;
	    }
	    
	}

}