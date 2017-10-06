#define _GNU_SOURCE				//RUSAGE_THREAD
#include <stdio.h>
#include <sys/resource.h>       //struct rusage
#include <sys/time.h>           //struct rusage
#include <sys/types.h>          //pid_t
#include <unistd.h>             //pid_t
#include <stdlib.h>             //for exit function
#include <pthread.h>
#include <stdint.h>
#include <sys/wait.h>
#include <sys/times.h>


#define ARRAY_SIZE 		(10)
int32_t a[ARRAY_SIZE] = {10,8,4,3,7,1,5,2,6,9};



/* this function is run by the second thread */
void *sort(void *input_arr_pointer)
{
	int32_t *arr_pointer = (int32_t *)input_arr_pointer;
	int32_t i,j,temp_var;
	int s;
	printf("Before Sorting\n");
	for(i=0;i<ARRAY_SIZE;i++)
	{
		printf("%d ",*(arr_pointer+i));
	}
	printf("\n");

	for(i=0;i<ARRAY_SIZE;i++)									/* Sort Function */
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
	for(i=0;i<ARRAY_SIZE;i++)
	{
		printf("%d ",*(arr_pointer+i));
	}
	printf("\n");	
	
}


int main()
{
    
    pthread_t sort_thread;


    uint64_t time_taken = 0;
	struct timespec initial_time;
    struct timespec end_time;

    uint64_t time_taken_2 = 0;
	struct timespec initial_time_2;
    struct timespec end_time_2;
    pid_t pid;
    int status = 0;
 

 	if(clock_gettime(CLOCK_THREAD_CPUTIME_ID,&initial_time))           /* Get the current time */
        printf("error \n");
 	if(pthread_create(&sort_thread, NULL, sort, a)) {
		printf("Error creating thread\n");
		return 1;
	}
	if(clock_gettime(CLOCK_THREAD_CPUTIME_ID,&end_time))           /* Get the current time */
        printf("error \n");
	//en_time = times(&en_cpu);
	//printf("Real Time: %jd, User Time %jd, System Time %jd\n", (intmax_t)(en_time - st_time), (intmax_t)(en_cpu.tms_utime - st_cpu.tms_utime), (intmax_t)(en_cpu.tms_stime - st_cpu.tms_stime));
	time_taken = (end_time.tv_sec*1000000000 + end_time.tv_nsec) - (initial_time.tv_sec*1000000000 + initial_time.tv_nsec); /* Total time in for pthread_create */
    printf("Total time taken to create: %ld ns\n", time_taken);

	if(pthread_join(sort_thread, NULL)) {
		printf("Error joining thread\n");
		return 2;
	}

 #if 0   
    printf("Before creating\n");
    getrusage(RUSAGE_SELF, &initial_time);
	if(pthread_create(&sort_thread, NULL, sort, a)) {
		printf("Error creating thread\n");
		return 1;
	}
	getrusage(RUSAGE_THREAD, &end_time);
    user_time = (end_time.ru_utime.tv_sec*1000000 + end_time.ru_utime.tv_usec) - (initial_time.ru_utime.tv_sec*1000000 + initial_time.ru_utime.tv_usec);
    kern_time = (end_time.ru_stime.tv_sec*1000000 + end_time.ru_stime.tv_usec)-(initial_time.ru_stime.tv_sec*1000000 + initial_time.ru_stime.tv_usec);
    printf("PARENT : Total user time for fork : %ld us\n", user_time);
    printf("PARENT : Total kern time for fork : %ld us\n", kern_time);

    printf("Checking the valueeeeeeeeeeeeeeeeeeeeeeeeeeeeee\n");
	printf("PARENT : start user time for fork : %ld us\n", (initial_time.ru_utime.tv_sec*1000000 + initial_time.ru_utime.tv_usec));
    printf("PARENT : stop user time for fork : %ld us\n", (end_time.ru_utime.tv_sec*1000000 + end_time.ru_utime.tv_usec));
	printf("PARENT : start kern time for fork : %ld us\n", (initial_time.ru_stime.tv_sec*1000000 + initial_time.ru_stime.tv_usec));
    printf("PARENT : stop kern time for fork : %ld us\n", (end_time.ru_stime.tv_sec*1000000 + end_time.ru_stime.tv_usec));
	printf("Checking the valueeeeeeeeeeeeeeeeeeeeeeeeeeeeee\n");

	if(pthread_join(sort_thread, NULL)) {
		printf("Error joining thread\n");
		return 2;
	}
#endif    
    
#if 1    
    
    
    if(clock_gettime(CLOCK_THREAD_CPUTIME_ID,&initial_time_2))           /* Get the current time */
        printf("error \n");
	pid = fork();
	
	printf("Check if prints twice\n");
	
	if(pid)
	{
	    if(waitpid(pid, &status, 0) == -1)
			perror("wait error");
	    if(clock_gettime(CLOCK_THREAD_CPUTIME_ID,&end_time_2))           /* Get the current time */
        	printf("error \n");
        time_taken_2 = (end_time_2.tv_sec*1000000000 + end_time_2.tv_nsec) - (initial_time_2.tv_sec*1000000000 + initial_time_2.tv_nsec); /* Total time in for pthread_create */
    	printf("Total time taken to fork and exec: %ld ns\n", time_taken_2);		
	    
	}
	else if(pid == 0)
	{
	    printf("In Child process\n");
	    
	    char* argv[4];
	    argv[0] = "ls";
	    argv[1] = "-l";
	    argv[2] = "-F";
	    argv[3] = NULL;
	    execv(argv[0], argv);
	    
		//static char *argv[]={"ls", NULL};
		//execv("/bin/bash", argv);
		printf("after execv\n");
		exit(1);            
	}
	else 
	    perror("forking error");
#endif	    
	return 0;    
}