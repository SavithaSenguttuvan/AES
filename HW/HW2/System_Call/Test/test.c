//#define _GNU_SOURCE
#include<unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main()
{
	size_t i_buff_size = 10;
	size_t invalid_buff_size = 0;
	int32_t i = 0;
	int32_t *i_buff = (int32_t*)malloc((sizeof(int32_t)*i_buff_size));	/* Input Buffer */
	int32_t *o_buff = (int32_t*)malloc((sizeof(int32_t)*i_buff_size));	/* Output Buffer */
	int32_t *invalid_input_buff = NULL;

	for(i=0;i<i_buff_size;i++)
	{
		*(i_buff+i) = ((int32_t)rand())%20;								/* Fill the input buffer with random numbers below 20 */
	}

	long int s = syscall(333,i_buff,i_buff_size,o_buff);				/* System call to sort the buffer */
	printf("The returned value is %ld\n",s);
	for(i=0;i<i_buff_size;i++)
	{
		printf("%d ",*(o_buff+i));										/* Output buffer after sorting */
	}
	printf("\n");	

	s = syscall(333,invalid_input_buff,i_buff_size,o_buff);				/* System call to sort the buffer */
	printf("The returned value if the input is invalid,  %ld\n",s);

	s = syscall(333,i_buff,invalid_buff_size,o_buff);				/* System call to sort the buffer */
	printf("The returned value if the input buffer size is invalid,  %ld\n",s);

}