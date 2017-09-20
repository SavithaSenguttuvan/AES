#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdint.h>

#include "doubly_linked_list.h"

/* This test is done to check if the node is correctly added into the linked list */
void test_dl_add_node(void **state)
{
	DB_node_t *head = NULL;
	uint32_t data_val = 10;
	uint32_t index_num = 1;
    assert_int_equal((add_node(&head,data_val,index_num)), LIST_NO_ERR);
    assert_int_equal((add_node(&head,data_val,index_num)), LIST_NO_ERR); 
    print_nodes(head);
    assert_int_equal((destroy(&head)), LIST_NO_ERR); 
}

/* This test is done to check if the node is correctly added at the head of the linked list */
void test_dl_add_head_node(void **state)
{
	DB_node_t *head = NULL;
	uint32_t data_val_1 = 10;
	uint32_t index_num_1 = 1;
	uint32_t data_val_2 = 20;
	uint32_t index_num_2 = 2;
	uint32_t data_val_3 = 30;
	uint32_t index_num_3 = 3;
	uint32_t head_data= 40;
	uint32_t head_index = 1;
	add_node(&head,data_val_1,index_num_1);
	add_node(&head,data_val_2,index_num_2);
	add_node(&head,data_val_3,index_num_3);

    assert_int_equal((add_node(&head,head_data,head_index)), LIST_NO_ERR); 
    print_nodes(head);
    assert_int_equal((destroy(&head)), LIST_NO_ERR); 
}
/* This test is done to check if the node is correctly added into the linked list as a last node */
void test_dl_add_last_node(void **state)
{
	DB_node_t *head = NULL;
	uint32_t data_val_1 = 10;
	uint32_t index_num_1 = 1;
	uint32_t data_val_2 = 20;
	uint32_t index_num_2 = 2;
	uint32_t data_val_3 = 30;
	uint32_t index_num_3 = 3;
	uint32_t head_data= 40;
	uint32_t head_index = 4;
	add_node(&head,data_val_1,index_num_1);
	add_node(&head,data_val_2,index_num_2);
	add_node(&head,data_val_3,index_num_3);

    assert_int_equal((add_node(&head,head_data,head_index)), LIST_NO_ERR); 
    print_nodes(head);
    assert_int_equal((destroy(&head)), LIST_NO_ERR); 
}
/* This test is done to check if the node is correctly added into the linked list */

void test_dl_add_middle_node(void **state)
{
	DB_node_t *head = NULL;
	uint32_t data_val_1 = 10;
	uint32_t index_num_1 = 1;
	uint32_t data_val_2 = 20;
	uint32_t index_num_2 = 2;
	uint32_t data_val_3 = 30;
	uint32_t index_num_3 = 3;
	uint32_t head_data= 40;
	uint32_t head_index = 2;
	add_node(&head,data_val_1,index_num_1);
	add_node(&head,data_val_2,index_num_2);
	add_node(&head,data_val_3,index_num_3);

    assert_int_equal((add_node(&head,head_data,head_index)), LIST_NO_ERR); 
    print_nodes(head);
    assert_int_equal((destroy(&head)), LIST_NO_ERR); 
}
/* This test is done to check if the node returns error if the node has to be included at a wrong index location */
void test_dl_add_invalid_index_node(void **state)
{
	DB_node_t *head = NULL;
	uint32_t data_val_1 = 10;
	uint32_t index_num_1 = 1;
	uint32_t data_val_2 = 20;
	uint32_t index_num_2 = 2;
	uint32_t data_val_3 = 30;
	uint32_t index_num_3 = 3;
	uint32_t head_data= 40;
	uint32_t head_index = 6;
	add_node(&head,data_val_1,index_num_1);
	add_node(&head,data_val_2,index_num_2);
	add_node(&head,data_val_3,index_num_3);

    assert_int_equal((add_node(&head,head_data,head_index)), LIST_ERROR); 
    print_nodes(head);
    assert_int_equal((destroy(&head)), LIST_NO_ERR); 
}
/* This test is done to check if the node is correctly removed from the linked list */

void test_dl_remove_node(void **state)
{
	DB_node_t *head = NULL;
	uint32_t data_val = 10;
	uint32_t index_num = 1;
	uint32_t ret_val = 0;
    assert_int_equal((add_node(&head,data_val,index_num)), LIST_NO_ERR); 
    assert_int_equal((remove_node(&head, &ret_val, index_num)), LIST_NO_ERR);
    assert_int_equal(ret_val,data_val);
    assert_int_equal((destroy(&head)), LIST_EMPTY); 
}
/* This test is done to check if the head node is correctly removed from the linked list */

void test_dl_remove_head_node(void **state)
{
	DB_node_t *head = NULL;
	uint32_t data_val_1 = 10;
	uint32_t index_num_1 = 1;
	uint32_t data_val_2 = 20;
	uint32_t index_num_2 = 2;
	uint32_t data_val_3 = 30;
	uint32_t index_num_3 = 3;
	uint32_t ret_val = 0;

	add_node(&head,data_val_1,index_num_1);
	add_node(&head,data_val_2,index_num_2);
	add_node(&head,data_val_3,index_num_3);
	print_nodes(head);
    assert_int_equal((remove_node(&head, &ret_val, index_num_1)), LIST_NO_ERR);
    assert_int_equal(ret_val,data_val_1);
    print_nodes(head);
    assert_int_equal((destroy(&head)), LIST_NO_ERR); 
}

/* This test is done to check if the last node is correctly removed from the linked list */

void test_dl_remove_last_node(void **state)
{
	DB_node_t *head = NULL;
	uint32_t data_val_1 = 10;
	uint32_t index_num_1 = 1;
	uint32_t data_val_2 = 20;
	uint32_t index_num_2 = 2;
	uint32_t data_val_3 = 30;
	uint32_t index_num_3 = 3;
	uint32_t ret_val = 0;

	add_node(&head,data_val_1,index_num_1);
	add_node(&head,data_val_2,index_num_2);
	add_node(&head,data_val_3,index_num_3);
	print_nodes(head);
    assert_int_equal((remove_node(&head, &ret_val, index_num_3)), LIST_NO_ERR);
    assert_int_equal(ret_val,data_val_3);
    print_nodes(head);
    assert_int_equal((destroy(&head)), LIST_NO_ERR); 
}

/* This test is done to check if the node is correctly removed from the linked list */

void test_dl_remove_middle_node(void **state)
{
	DB_node_t *head = NULL;
	uint32_t data_val_1 = 10;
	uint32_t index_num_1 = 1;
	uint32_t data_val_2 = 20;
	uint32_t index_num_2 = 2;
	uint32_t data_val_3 = 30;
	uint32_t index_num_3 = 3;
	uint32_t ret_val = 0;

	add_node(&head,data_val_1,index_num_1);
	add_node(&head,data_val_2,index_num_2);
	add_node(&head,data_val_3,index_num_3);
	print_nodes(head);
    assert_int_equal((remove_node(&head, &ret_val, index_num_2)), LIST_NO_ERR);
    assert_int_equal(ret_val,data_val_2);
    print_nodes(head);
    assert_int_equal((destroy(&head)), LIST_NO_ERR); 
}

/* This test is done to check linked list returns error on underflow condition */

void test_dl_remove_empty_list(void **state)
{
	DB_node_t *head = NULL;
	uint32_t index_num_2 = 2;
	uint32_t ret_val = 0;
    assert_int_equal((remove_node(&head, &ret_val, index_num_2)), LIST_EMPTY);
    assert_int_equal((destroy(&head)), LIST_EMPTY); 
}

/* This test is done to check if the node is asked to be removed from an invalid location */

void test_dl_remove_invalid_index_node(void **state)
{
	DB_node_t *head = NULL;
	uint32_t data_val_1 = 10;
	uint32_t index_num_1 = 1;
	uint32_t data_val_2 = 20;
	uint32_t index_num_2 = 2;
	uint32_t data_val_3 = 30;
	uint32_t index_num_3 = 3;
	uint32_t ret_val = 0;
	uint32_t invalid_index_number = 9;

	add_node(&head,data_val_1,index_num_1);
	add_node(&head,data_val_2,index_num_2);
	add_node(&head,data_val_3,index_num_3);
	print_nodes(head);
    assert_int_equal((remove_node(&head, &ret_val, invalid_index_number)), LIST_ERROR);
    print_nodes(head);
    assert_int_equal((destroy(&head)), LIST_NO_ERR); 
}

/* This test is done to check if the node is correctly present in the linked list */

void test_dl_search_node(void **state)
{
	DB_node_t *head = NULL;
	uint32_t data_val = 10;
	uint32_t index_num = 1;
	uint32_t ret_ind = 0;
    assert_int_equal((add_node(&head,data_val,index_num)), LIST_NO_ERR); 
    assert_int_equal((search(head,&ret_ind, data_val)), LIST_NO_ERR);
    assert_int_equal(ret_ind,index_num);
    assert_int_equal((destroy(&head)), LIST_NO_ERR); 
}

/* This test is done to check if the node is at the head of the linked list */

void test_dl_search_head_node(void **state)
{
	DB_node_t *head = NULL;
	uint32_t ret_ind = 0;

	uint32_t data_val_1 = 10;
	uint32_t index_num_1 = 1;
	uint32_t data_val_2 = 20;
	uint32_t index_num_2 = 2;
	uint32_t data_val_3 = 30;
	uint32_t index_num_3 = 3;

	add_node(&head,data_val_1,index_num_1);
	add_node(&head,data_val_2,index_num_2);
	add_node(&head,data_val_3,index_num_3);

    assert_int_equal((search(head,&ret_ind, data_val_1)), LIST_NO_ERR);
    assert_int_equal(ret_ind,index_num_1);
    assert_int_equal((destroy(&head)), LIST_NO_ERR); 
}

/* This test is done to check if the node is at the end the linked list */

void test_dl_search_last_node(void **state)
{
	DB_node_t *head = NULL;
	uint32_t ret_ind = 0;

	uint32_t data_val_1 = 10;
	uint32_t index_num_1 = 1;
	uint32_t data_val_2 = 20;
	uint32_t index_num_2 = 2;
	uint32_t data_val_3 = 30;
	uint32_t index_num_3 = 3;

	add_node(&head,data_val_1,index_num_1);
	add_node(&head,data_val_2,index_num_2);
	add_node(&head,data_val_3,index_num_3);

    assert_int_equal((search(head,&ret_ind, data_val_3)), LIST_NO_ERR);
    assert_int_equal(ret_ind,index_num_3);
    assert_int_equal((destroy(&head)), LIST_NO_ERR); 
}

/* This test is done to check if the node is in between the linked list */

void test_dl_search_middle_node(void **state)
{
	DB_node_t *head = NULL;
	uint32_t ret_ind = 0;

	uint32_t data_val_1 = 10;
	uint32_t index_num_1 = 1;
	uint32_t data_val_2 = 20;
	uint32_t index_num_2 = 2;
	uint32_t data_val_3 = 30;
	uint32_t index_num_3 = 3;

	add_node(&head,data_val_1,index_num_1);
	add_node(&head,data_val_2,index_num_2);
	add_node(&head,data_val_3,index_num_3);

    assert_int_equal((search(head,&ret_ind, data_val_2)), LIST_NO_ERR);
    assert_int_equal(ret_ind,index_num_2);
    assert_int_equal((destroy(&head)), LIST_NO_ERR); 
}

/* This test is done to check if the node to be searched is not present */

void test_dl_search_invalid_node(void **state)
{
	DB_node_t *head = NULL;
	uint32_t ret_ind = 0;

	uint32_t data_val_1 = 10;
	uint32_t index_num_1 = 1;
	uint32_t data_val_2 = 20;
	uint32_t index_num_2 = 2;
	uint32_t data_val_3 = 30;
	uint32_t index_num_3 = 3;
	uint32_t invalid_data = 40;

	add_node(&head,data_val_1,index_num_1);
	add_node(&head,data_val_2,index_num_2);
	add_node(&head,data_val_3,index_num_3);

    assert_int_equal((search(head,&ret_ind, invalid_data)), LIST_ERROR);
    assert_int_equal((destroy(&head)), LIST_NO_ERR); 
}

/* This test is done to check if the node is searched in an empty linked list */

void test_dl_search_empty_list(void **state)
{
	DB_node_t *head = NULL;
	uint32_t ret_ind = 0;
	uint32_t invalid_data = 40;

    assert_int_equal((search(head,&ret_ind, invalid_data)), LIST_EMPTY);
    assert_int_equal((destroy(&head)), LIST_EMPTY); 
}


/* This test is done to check if the linked list is destroyed */

void test_dl_destroy_node(void **state)
{
	DB_node_t *head = NULL;
	uint32_t data_val = 10;
	uint32_t index_num = 1;
    assert_int_equal((add_node(&head,data_val,index_num)), LIST_NO_ERR); 
    assert_int_equal((destroy(&head)), LIST_NO_ERR); 
}

/* This test is done to check if the empty linked list is destroyed */

void test_dl_destroy_empty(void **state)
{
	DB_node_t *head = NULL; 
    assert_int_equal((destroy(&head)), LIST_EMPTY); 
}

/* This test is done to check if the size of the linked list */
void test_dl_size_node(void **state)
{
	DB_node_t *head = NULL;
	uint32_t data_val = 10;
	uint32_t index_num = 1;
    assert_int_equal((add_node(&head,data_val,index_num)), LIST_NO_ERR); 
    assert_int_equal(size(head), 1); 
    assert_int_equal((destroy(&head)), LIST_NO_ERR); 
}



int main(int argc, char **argv)
{
	const struct CMUnitTest tests[] = {	
	/*circular buffer unit tests*/
	cmocka_unit_test(test_dl_add_node),
	cmocka_unit_test(test_dl_remove_node),
	cmocka_unit_test(test_dl_search_node),	
	cmocka_unit_test(test_dl_destroy_node),	
	cmocka_unit_test(test_dl_size_node),
	cmocka_unit_test(test_dl_size_node),
	cmocka_unit_test(test_dl_add_head_node),	
	cmocka_unit_test(test_dl_add_last_node),	
	cmocka_unit_test(test_dl_add_middle_node),
	cmocka_unit_test(test_dl_add_invalid_index_node),
	cmocka_unit_test(test_dl_remove_head_node),
	cmocka_unit_test(test_dl_remove_last_node),
	cmocka_unit_test(test_dl_remove_middle_node),
	cmocka_unit_test(test_dl_remove_empty_list),
	cmocka_unit_test(test_dl_remove_invalid_index_node),
	cmocka_unit_test(test_dl_destroy_empty),	
	cmocka_unit_test(test_dl_search_head_node),	
	cmocka_unit_test(test_dl_search_last_node),
	cmocka_unit_test(test_dl_search_middle_node),		
	cmocka_unit_test(test_dl_search_invalid_node),
	cmocka_unit_test(test_dl_destroy_empty),	
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}