#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <semaphore.h>

sem_t th1_sem;
sem_t th2_sem;
pthread_mutex_t rsrcA;
char filename[100];

FILE *fp;
pthread_t thread1;
pthread_t thread2;
int32_t linecount, wordcount, charcount;
    
void sighandler(int signum)                         /* Signal Handler for the SIGUSR1,SIGUSR2,SIGTERM signals */
{
    printf("Received signal %d\n", signum);   
    if(signum == SIGUSR1)                           /* On receiving the SIGUSR1 signal */
    {
        if(sem_post(&th1_sem))                      /* Release the semaphore needed for analysing the file */
          perror("sem_post");
    }
    else if(signum == SIGUSR2)                      /* On receiving the SIGUSR2 signal */
    {
        if(sem_post(&th2_sem))                      /* Release the sempaphore needed for the print the results */
          perror("sem_post");
    }
    if(signum == SIGTERM)                           /* On receiving the SIGTERM signal */      
    {
       if(fp != NULL)                               /* Close the file */
           fclose(fp);               
      
       pthread_kill(thread1, SIGTERM);              /* Send a signal to a thread to terminate*/     
       pthread_kill(thread1, SIGTERM);              /* Send a signal to a thread to terminate*/
        
       sem_destroy(&th1_sem);                       /* Destroy semaphore */
       sem_destroy(&th2_sem);                       /* Destroy semaphore */
       pthread_mutex_destroy(&rsrcA);               /* Destroys the mutex object */            
      
       printf("Graceful exit \n");
       exit(0);  
    }
}

void *thread1_fn()                                  /* Function for analysing the file */ 
{
    
    char ch;
    while(1)
    {
        if(sem_wait(&th1_sem))                      /* Wait for a semaphore - gets the sem on receiveing SIGUSR1 */ 
            printf("sem_wait error\n");
        else
        {
            printf("File Analysis\n");
            pthread_mutex_lock(&rsrcA);             /* Fetching the mutex lock */
            fp = fopen(filename,"r");               /* Open file */
            if (!fp )
            {
               printf("File could not be opened\n");
            }
            else
            {
                linecount = 0;
                wordcount = 0;
                charcount = 0;
                while ((ch=getc(fp)) != EOF) 
                {
        		    if (ch != ' ' && ch != '\n') { ++charcount; }
        		    if (ch == ' ' || ch == '\n') { ++wordcount; }
        		    if (ch == '\n') { ++linecount; }
                }
                /*
                if (charcount > 0) 
                {
        		    ++linecount;
        		    ++wordcount;
        	    }
                */
            }
            fclose(fp);                             /* Close the file */
            fp = NULL;

          pthread_mutex_unlock(&rsrcA);             /* Release the mutex */
        }
    }
}
            
void *thread2_fn()                                  /* Function for printing the results */ 
{
    while(1)
    {
        if(sem_wait(&th2_sem))                      /* WAit on the semaphore which gets released on receiving the SIGUSR2 */
          printf("sem_wait error\n");
        else {
          printf("Results of the File Analysis\n");
          pthread_mutex_lock(&rsrcA);               /* Fetching the mutex lock */
          printf("Lines : %d \n", linecount);
          printf("Words : %d \n", wordcount);
          printf("Characters : %d \n", charcount);
          pthread_mutex_unlock(&rsrcA);             /* Release the mutex */
        }
    }
}

int main()
{
    
    struct sigaction act;
    //FILE *fp;
    int ch;
    
    memset(&act, 0, sizeof(act));
    act.sa_handler = sighandler;
    sigaction(SIGUSR1, &act, NULL);             /* Change the signal action - use diff signal handler */
    sigaction(SIGUSR2, &act, NULL);             /* Change the signal action - use diff signal handler */
    sigaction(SIGTERM, &act, NULL);             /* Change the signal action - use diff signal handler */
    
    sem_init(&th1_sem, 0, 0);                   /* Init semaphore, count = 0, 0 - semaphore is shared between the threads of a process*/
    sem_init(&th2_sem, 0, 0);                   /* Init semaphore */
    pthread_mutex_init(&rsrcA, NULL);
    
    printf("Enter a filename :");
    scanf("%s",filename);
    //gets(filename);
    fp = fopen(filename,"w");                   /* Open file */
    if (!fp )
    {
       printf("File could not be opened\n");
    }
    else
    {
        printf("Enter text into file (characters after * are ignored)\n");
        while(1)                                /* Insert character by character */
        {
            scanf("%c",(char*)&ch);
            if((char)ch == '*')
            {
                break;
            }
            fputc(ch, fp);
        }
    }
    fclose(fp);                                 /* Close file */
    fp = NULL;
    printf("Waiting for signals\n");
    if(pthread_create(&thread1, NULL, &thread1_fn, NULL))   /* Create first thread */
    {
        printf("Error creating thread 1\n");
		return 1;
    }
    if(pthread_create(&thread2, NULL, &thread2_fn, NULL))   /* Create second thread */
    {
        printf("Error creating thread 2\n");
		return 1;
    }
    if(pthread_join(thread1, NULL)) {                       /* Waits for the thread1 to terminate  */
		printf("Error joining thread\n");
		return 2;
	}  
	if(pthread_join(thread2, NULL)) {                       /* Waits for the thread2 to terminate  */
		printf("Error joining thread\n");
		return 2;
	}  
	
	if(pthread_mutex_destroy(&rsrcA) != 0)                 /* Destroy the mutex */
        perror("mutex A destroy");
    if(sem_destroy(&th1_sem))                              /* Destroy the semaphore */
        perror("sem destroy"); 
    if(sem_destroy(&th2_sem))                              /* Destroy the semaphore */
        perror("sem destroy");     
    return 0;
}