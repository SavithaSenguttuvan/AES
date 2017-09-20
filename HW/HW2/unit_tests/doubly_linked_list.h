#ifndef __DOUBLE_LINKED_LIST__
#define __DOUBLE_LINKED_LIST__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct DB_node_t{
	uint32_t data;                  /* Node's data value */
	struct DB_node_t *next_node;    /* Node's next node */
    struct DB_node_t *prev_node;    /* Node's previous node */
}DB_node_t;

typedef enum{
	LIST_EMPTY,						/*enum when list is Empty*/
	LIST_NO_ERR,					/*enum when there is no error*/
	LIST_ERROR,						/*enum when there is error*/
	LIST_NULL,						/*enum when the pointer is pointing to NULL*/
}DB_node_status;

/**
 * @brief function to add a node into a linked list
 *
 * This function implements functionality of allocating memory and adding a node to a linked list. 
 * The node is added to the linked list at the location specified by the index number
 * @return DB_node_status (enum)
 */

DB_node_status add_node(DB_node_t **head_node, uint32_t data_val, uint32_t index_num);


/**
 * @brief function to print the nodes in the linked list
 *
 * This function implements functionality printing the existing nodes in the linked list
 * 
 * @return None
 */
void print_nodes(DB_node_t * head_ptr);

/**
 * @brief function to remove a node from the linked list
 *
 * This function implements functionality removing a node from the linked list as specified by the index number
 * The removed node's data value is stored back in the data_val parameter passed
 * 
 * @return DB_node_status (enum)
 */
DB_node_status remove_node(DB_node_t **head_node, uint32_t *data_val, uint32_t index_num);

/**
 * @brief function to remove all the nodes from the linked list
 * 
 * @return DB_node_status (enum)
 * 
 */
DB_node_status destroy(DB_node_t **head_node);

/**
 * @brief function to search a node in the linked list
 *
 * This function implements functionality searching a node depending on the data value passed. 
 * The location at which the data value was found is stored back in the index_num pointer which is passed as a paramter
 * 
 * @return DB_node_status (enum)
 */
DB_node_status search(DB_node_t *head_node,uint32_t *index_num, uint32_t data_val);

/**
 * @brief function to determine the number of nodes in the linked list
 *
 * This function implements functionality determining the total number of nodes in the linked list
 * 
 * @return uint32_t data value
 */
uint32_t size(DB_node_t *head_node);

#endif

