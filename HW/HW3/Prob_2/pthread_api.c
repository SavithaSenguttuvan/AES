#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>

#define ARRAY_SIZE 		(10)
#define SORT 			(1)


int32_t a[ARRAY_SIZE] = {10,8,4,3,7,1,5,2,6,9};
pthread_mutex_t rsrcA;
pthread_cond_t  cond_1;

/* this function is run by the second thread */
void *sort(void *input_arr_pointer)									/* Function to sort in descending order */
{
	int32_t *arr_pointer = (int32_t *)input_arr_pointer;
	int32_t i,j,temp_var;
	int s;
	
    pthread_attr_t attr;
    long guard_size;
	
	s = pthread_getattr_np(pthread_self(), &attr);					/* Getting the attribute to verify the increased guard size */
	if (s != 0)
    	printf("Error in main thread attributes\n");
    s = pthread_attr_getguardsize(&attr, &guard_size);
    if (s != 0)
    	printf("Error in getting the pthread guard size\n");           
    printf("Guard size = %ld bytes\n",guard_size);
	
	
	
	printf("In funtion, sort_thread id = %ld\n", pthread_self());

	pthread_mutex_lock(&rsrcA);										/* Fetching the mutex */
	//while(pthread_mutex_trylock(&rsrcA));							/* Mutex try_lock - loop until the lock is acquired */

	pthread_cond_wait(&cond_1, &rsrcA);								/* waits if the shared varalble is set flase and releases the mutex */ 

	printf("Before Sorting\n");
	for(i=0;i<ARRAY_SIZE;i++)	
	{
		printf("%d ",*(arr_pointer+i));								/* Print the array before sort */
	}
	printf("\n");

	if(!SORT)
	{
		pthread_exit(NULL);											/* Terminates the thread */
	}
	for(i=0;i<ARRAY_SIZE;i++)										/* Sort */
	{
	    for(j=0;j<ARRAY_SIZE-i-1;j++)
	    {
	        if((*(arr_pointer+j)) < (*(arr_pointer+j+1)))
	        {
	        	
	            temp_var = *(arr_pointer+j);
	            *(arr_pointer+j) = *(arr_pointer+j+1);
	            *(arr_pointer+j+1) = temp_var;
	        }
	    }
	}

	printf("After Sorting\n");
	for(i=0;i<ARRAY_SIZE;i++)										/* Print the sorted thread */
	{
		printf("%d ",*(arr_pointer+i));
	}
	printf("\n");	
	pthread_mutex_unlock(&rsrcA);									/* Release the mutex */
	
}

/* this function is run by the second thread */
void *sort_asc(void *input_arr_pointer)
{
	int32_t *arr_pointer = (int32_t *)input_arr_pointer;
	int32_t i,j,temp_var;
	int s;
	
    pthread_attr_t attr;
    long guard_size;
	
	s = pthread_getattr_np(pthread_self(), &attr);
	if (s != 0)
    	printf("Error in main thread attributes\n");
    s = pthread_attr_getguardsize(&attr, &guard_size);				/* Check the guard size */
    if (s != 0)
    	printf("Error in getting the pthread guard size\n");           
    printf("Guard size = %ld bytes\n",guard_size);

	printf("In funtion, print_thread id = %ld\n", pthread_self());
	pthread_mutex_lock(&rsrcA);										/* Acquire the mutex */
	//while(pthread_mutex_trylock(&rsrcA));
	printf("Before Sorting in asc\n");
	for(i=0;i<ARRAY_SIZE;i++)
	{
		printf("%d ",*(arr_pointer+i));								/* Print the unsorted array */
	}
	printf("\n");

	if(!SORT)
	{
		pthread_exit(NULL);
	}

	for(i=0;i<ARRAY_SIZE;i++)										/* Sort */
	{
	    for(j=0;j<ARRAY_SIZE-i-1;j++)
	    {
	        if((*(arr_pointer+j)) > (*(arr_pointer+j+1)))
	        {
	        	
	            temp_var = *(arr_pointer+j);
	            *(arr_pointer+j) = *(arr_pointer+j+1);
	            *(arr_pointer+j+1) = temp_var;
	        }
	    }
	}

	printf("After Sorting in asc\n");
	for(i=0;i<ARRAY_SIZE;i++)
	{
		printf("%d ",*(arr_pointer+i));								/* Print sorted array */
	}
	printf("\n");	
	//printf("hi\n");
	if(pthread_cond_signal(&cond_1))								/* Setting the shared variable to true */
	{
		printf("Error in signalling\n");
	}
	//printf("hi_2\n");
	pthread_mutex_unlock(&rsrcA);									/* Release the mutex */
}

int main()
{
	/* Thread Names */
	pthread_t sort_thread;
	pthread_t sort_asc_thread;
	/* Thread attributes name */
    pthread_attr_t attr;
    pthread_attr_t attr1;
    pthread_attr_t attr2;
    /* Thread attributes values */
    long stack_size, guard_size;
    void *stack_addr;
	/* Thread schedule parameters */
	struct sched_param sort_thread_param;
	struct sched_param sort_asc_thread_param;
	struct sched_param main_param;	
	
    int s;
	
	/* Getting the attributes of the main thread*/
	s = pthread_getattr_np(pthread_self(), &attr);
	if (s != 0)
    	printf("Error in main thread attributes\n");
    s = pthread_attr_getguardsize(&attr, &guard_size);
    if (s != 0)
    	printf("Error in getting the pthread guard size\n");           
    printf("Guard size = %ld bytes\n",guard_size);	
	s = pthread_attr_getstack(&attr, &stack_addr, &stack_size);
    if (s != 0)
    	printf("Error in getting the stack details\n"); 
    printf("Stack address       = %p", stack_addr);
    printf("Stack size = (%ld) bytes\n",stack_size);
    
    
    /* Initialize two new attributes for the two threads resp */
    s = pthread_attr_init(&attr1);
	if (s != 0)
    	printf("pthread attribute init error\n");
    	
    s = pthread_attr_init(&attr2);
	if (s != 0)
    	printf("pthread attribute init error\n");
    	
    	
    /* Changing the guard size for the first thread */	
	s = pthread_attr_setguardsize(&attr1, (guard_size+4100));
    if (s != 0)
        printf("pthread attribute guard size error\n");
    /*Changing Scheduling Priority*/
	
	sched_getparam(pthread_self(), &main_param);
	printf("main thread prio %d\n",main_param.sched_priority);					/* Setting the attributes */
	main_param.sched_priority = 30;
	sort_thread_param.sched_priority = (main_param.sched_priority) - 1;
	sort_asc_thread_param.sched_priority = (main_param.sched_priority) - 10; 
	
#if 1
	/*Assigning Scheduling policy of threads*/
	pthread_attr_setinheritsched(&attr1, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&attr1, SCHED_FIFO);

	pthread_attr_setinheritsched(&attr2, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&attr2, SCHED_FIFO);
#endif	

    /* Setting the scheduling priority for the threads */    
	int retVal = pthread_attr_setschedparam(&attr1, &sort_thread_param);
	printf("schedparam 1 retval %d %d\n",retVal, EINVAL);
    if (retVal != 0){
	perror("setting sched param 1 error\n");}
	retVal = pthread_attr_setschedparam(&attr2, &sort_asc_thread_param);
	printf("schedparam 2 retval %d\n",retVal);
    if (retVal != 0){
	perror("setting sched param 2 error\n");}

	printf("func retval is %d\n", sched_setscheduler(pthread_self(), SCHED_FIFO, &main_param));	/* Requires sudo - because the changing the running thread properties */

	sched_getparam(pthread_self(), &main_param);
	printf("main thread prio %d\n",main_param.sched_priority);

	/* Mutex Init */
	pthread_mutex_init(&rsrcA, NULL);							/* Initialize the mutex */
	/* Condition Init */
	if(pthread_cond_init(&cond_1, NULL))						/* Initilaize the condition variable */
	{
		printf("Error in condition create\n");
	}
	/* Creating first thread */
	if(pthread_create(&sort_thread, &attr1, sort, a)) {			/* Create the thread */
		perror("Error creating thread 1\n");
		return 1;
	}
	/* Creating second thread */
	if(pthread_create(&sort_asc_thread, &attr2, sort_asc, a)) {	/* Create the thread */
		printf("Error creating thread 2\n");
		return 1;
	}

    cpu_set_t cpuset; 
	CPU_ZERO(&cpuset); 
	CPU_SET(0,&cpuset);
    pthread_setaffinity_np(sort_thread,sizeof(cpu_set_t),&cpuset); 			/* Run the thread in core 0 */
    pthread_setaffinity_np(sort_asc_thread,sizeof(cpu_set_t),&cpuset); 		/* Run the thread in core 0 */

    pthread_attr_getschedparam(&attr1, &sort_thread_param);								
	pthread_attr_getschedparam(&attr2, &sort_asc_thread_param);

	printf("sort_thread_param prio %d\n",sort_thread_param.sched_priority);
	printf("sort_asc_thread_param prio %d\n",sort_asc_thread_param.sched_priority);

	printf("In main the sort thread's id is = %ld\n", sort_thread);
	printf("In main the sort_asc thread's id is = %ld\n", sort_asc_thread);

	/* wait for the threads to finish */
	if(pthread_join(sort_thread, NULL)) {							/* Wait until the thread completes execution */
		printf("Error joining thread\n");
		return 2;
	}
	if(pthread_join(sort_asc_thread, NULL)) {						/* Wait until the thread completes execution */
		printf("Error joining thread\n");	
		return 2;
	}
	/* Destroy condition attributes */
	if(pthread_cond_destroy(&cond_1))
	{
		printf("Error\n");
	}
	/* Destroy mutex */
	if(pthread_mutex_destroy(&rsrcA) != 0)
     perror("error in mutex A destroy");

	
}
