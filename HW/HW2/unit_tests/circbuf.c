#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include "circbuf.h"

CB_status CB_init(CB_t **CB_buff_ptr, uint8_t len)
{
	*CB_buff_ptr = (CB_t*)malloc(sizeof(CB_t));
	
	if(*CB_buff_ptr == NULL)												/*checks if Null*/
		return BUFF_NULL;
	(*CB_buff_ptr)->buff_ptr = (uint32_t *)malloc(sizeof(uint32_t) * len);	/*allocate memory and return the pointer*/
	(*CB_buff_ptr)->head_ptr = (*CB_buff_ptr)->buff_ptr;					/*initialize the head pointer*/
	(*CB_buff_ptr)->tail_ptr = (*CB_buff_ptr)->buff_ptr;					/*initialize the tail pointer*/
	(*CB_buff_ptr)->total_length = len;										/*initializes the length of the buffer*/
	(*CB_buff_ptr)->count = 0;												/*initialize the number of items in the buffer*/

	return BUFF_NO_ERR;
}

CB_status CB_destroy(CB_t * CB_buff_ptr)
{
	if (CB_buff_ptr == NULL)			/*checks if Null*/
		return BUFF_NULL;

	if (CB_buff_ptr->buff_ptr == NULL)		/*checks if Null*/
		return BUFF_NULL;

	free((void*)CB_buff_ptr);		/*deallocate memory*/

	return BUFF_NO_ERR;
}

CB_status CB_is_full(CB_t * CB_buff_ptr)
{
	if (CB_buff_ptr == NULL)					/*checks if Null*/
		return BUFF_NULL;

	if (CB_buff_ptr->buff_ptr == NULL)			/*checks if Null*/
		return BUFF_NULL;


	if(CB_buff_ptr->count == CB_buff_ptr->total_length)	 /*checks if number of items added to the buffer is size of the buffer */
	{
		return BUFF_FULL;						/*Checks if the buffer is Full*/
	}
	return BUFF_NO_ERR;
}

CB_status CB_is_empty(CB_t * CB_buff_ptr)
{
	if (CB_buff_ptr == NULL)					/*checks if Null*/
		return BUFF_NULL;

	if (CB_buff_ptr->buff_ptr == NULL)			/*checks if Null*/
		return BUFF_NULL;

	if ((CB_buff_ptr->head_ptr == CB_buff_ptr->tail_ptr) && ((CB_buff_ptr->count) == 0))	/*checks if head pointer and tail pointer are pointing to the same location*/
		return BUFF_EMPTY;

	return BUFF_NO_ERR;
}

CB_status CB_buffer_add_item(CB_t * CB_buff_ptr, uint32_t data)
{
	if (CB_buff_ptr == NULL)						/*checks if Null*/
		return BUFF_NULL;

	if (CB_buff_ptr->buff_ptr == NULL)				/*checks if Null*/
		return BUFF_NULL;

	if(CB_is_full(CB_buff_ptr) == BUFF_FULL)		/*checks if buffer is full*/
		return BUFF_ERROR;

	*(CB_buff_ptr->head_ptr) = data;				/*data added to the buffer*/

	if(CB_buff_ptr->head_ptr == CB_buff_ptr->buff_ptr + (CB_buff_ptr->total_length - 1)) /*check if head pointer has reached end of the buffer*/
	{
		CB_buff_ptr->head_ptr = CB_buff_ptr->buff_ptr;		/*head pointer points to the buffer pointer*/
	}
	else
	{
		(CB_buff_ptr->head_ptr)++;					/*increment the head pointer*/
	}
	CB_buff_ptr->count++;
	return BUFF_NO_ERR;
}

CB_status CB_buffer_remove_item(CB_t * CB_buff_ptr, uint32_t *temp_data)
{
	if (CB_buff_ptr == NULL)					/*checks if Null*/
		return BUFF_NULL;

	if (CB_buff_ptr->buff_ptr == NULL)			/*checks if Null*/
		return BUFF_NULL;

	if(CB_is_empty(CB_buff_ptr) == BUFF_EMPTY)	/*checks if buffer is empty*/
		return BUFF_ERROR;

	*temp_data = *(CB_buff_ptr->tail_ptr);		/*store the data to be removed in a temporary varirable*/

	if(CB_buff_ptr->tail_ptr == CB_buff_ptr->buff_ptr + CB_buff_ptr->total_length - 1) /*check if tail pointer has reached end of the buffer*/
	{
		CB_buff_ptr->tail_ptr = CB_buff_ptr->buff_ptr;		/*head pointer points to the buffer pointer*/
	}
	else
	{
		(CB_buff_ptr->tail_ptr)++;				/*increment the tail pointer*/
	}
	(CB_buff_ptr->count)--;						/*decrement the count*/
	return BUFF_NO_ERR;
}

void CB_buff_dump(CB_t *CB_buff_ptr)
{
    CB_status buffer_status;    
    uint32_t removed_data;
    while(CB_buff_ptr->count)
    {
        buffer_status = CB_buffer_remove_item(CB_buff_ptr,&removed_data);
        printf("%d | ",removed_data);
    }
    printf("\n");
}

uint32_t CB_size(CB_t *CB_buff_ptr)
{
    return CB_buff_ptr->count;
}