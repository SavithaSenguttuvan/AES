#include "doubly_linked_list.h"

DB_node_status add_node(DB_node_t **head_node, uint32_t data_val, uint32_t index_num)
{
    uint32_t index_val = index_num;
    DB_node_t *current_node = *head_node; 
    
    DB_node_t *new_node = (DB_node_t*) malloc(sizeof(DB_node_t));               /* Allocate mry to new node */
    new_node->data = data_val;                                                  /* Assign the data value */
    
    
    if(current_node == NULL)
    {
        
        if(index_num != 1)                                                      /* Error if not the first node */
        {           
            return LIST_ERROR;        
        }
        else
        {
            new_node->next_node = NULL;                                         /* Adding first node */        
            new_node->prev_node = NULL;
            *head_node = new_node;
            return LIST_NO_ERR; 
        }
    }
    
        while((--index_num)>1)                                                  
        {
            if(current_node != NULL)
            {
                current_node = current_node->next_node;                         /* Move to the next node */
            }
            else
            {
                return LIST_ERROR;
            }
        }
            if(index_val == 1)                                                  /* If the new node if the first node */
            {
                new_node->next_node = *head_node;                               
                new_node->prev_node = NULL; 
                *head_node = new_node; 
                return LIST_NO_ERR;    
            }
        else if(current_node->next_node == NULL)                                /* If last node */
        {   
          new_node->next_node = NULL; 
        }
        else 
        {                                                                       /* If node is added in between */
          new_node->next_node = current_node->next_node;         
          current_node->next_node->prev_node = new_node;
        }
    	
        new_node->prev_node = current_node; 
        current_node->next_node = new_node; 
    
    
    return LIST_NO_ERR; 
}

void print_nodes(DB_node_t * head_node)
{
    DB_node_t * current_node = head_node;
    size_t i = 1;
    while(current_node != NULL)                                                 /* Print until the node is NULL */
    {
        printf("Data_value %ld, %d \n", i, current_node->data);
        i++;
        current_node = current_node->next_node;
    }
    if(i==1)
    {
        printf("List Empty\n");                                                 /* If list empty */
    }
}

DB_node_status remove_node(DB_node_t **head_node, uint32_t *data_val, uint32_t index_num)
{
    DB_node_t* current = *head_node;
    DB_node_t* previous = NULL;
    uint32_t i = 1;
    if(*head_node == NULL)                                                      /* If list is empty */
    {
        return LIST_EMPTY;
    }
    while(i < index_num)
    {
        if(current->next_node != NULL)                                          /* Shift until the node is found */
        {
            previous = current;
            current = current->next_node;
        }
        else
        {
            return LIST_ERROR;
        }
        i++;
    }
    if(current == *head_node)                                                   /* If the node to be removed is the first node */
    {
        DB_node_t *tempLink = *head_node;
        if(current->next_node != NULL)
        {
            *head_node = (*head_node)->next_node;
            (*head_node)->prev_node = NULL;
        }
        else
        {
            *head_node = NULL;
        }
        *data_val = tempLink->data;
        free(tempLink);
    }
    else if(current->next_node == NULL)                                         /* If the node to be removed is the last node */
    {
        DB_node_t *tempLink = current;
        previous->next_node = NULL;
        *data_val = tempLink->data;
        free(tempLink);
    }
    else
    {
        DB_node_t *tempLink = current;
        current->prev_node->next_node = current->next_node;
        current->next_node->prev_node = current->prev_node;
        *data_val = tempLink->data;
        free(tempLink);
    }
    return LIST_NO_ERR;
}

DB_node_status destroy(DB_node_t **head_node)
{
    DB_node_t *tempLink = *head_node;
    if(tempLink == NULL)
    {
        return LIST_EMPTY;
    }
    //while(size_count--)
    while(*head_node != NULL)                                                   /* Shift until last node */
    {
        if((*head_node)->next_node != NULL)                                     
        {
            tempLink = *head_node;
            *head_node = (*head_node)->next_node;                               /* Assign new head */
            free(tempLink);                                                     /* Remove the node */
        }
        else
        {
            tempLink = *head_node;                                              /* If last node */
            *head_node = NULL;                                                  
            free(tempLink);                                                     /* Remove the node */
        }
    }
    return LIST_NO_ERR;
}

DB_node_status search(DB_node_t *head_node,uint32_t *index_num, uint32_t data_val)
{
    uint32_t i = 1;
    DB_node_t *ptr = head_node;
    if(head_node == NULL)
    {
        return LIST_EMPTY;
    }
    while(ptr != NULL)                                                          
    {
        if(ptr->data == data_val)                                               /* Shift until the node with the data_val is found */
        {   
            *index_num = i;                                                     /* Index location of the data value */
            return LIST_NO_ERR;
        }
        else
        {
            ptr = ptr->next_node;
        }
        i++;
    }
    return LIST_ERROR;
}

uint32_t size(DB_node_t *head_node)
{
    uint32_t count = 0;
    DB_node_t *ptr = head_node;
    while(ptr != NULL) {                                                        /* Count until the last node */
        ptr = ptr->next_node;
        count++;
    }
    return count;
}
