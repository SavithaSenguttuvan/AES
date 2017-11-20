#include <stdio.h>
#include <errno.h>
#include <sys/socket.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h> 

#define PORT 5000
#define USR_BUFF_LEN 100

int main()
{
	int usr_socket;
    struct sockaddr_in bbg_addr;	
    char usr_msg[USR_BUFF_LEN];
    char usr_rec_buff[USR_BUFF_LEN];

    int32_t time_period;
    int32_t duty_cycle;
    int32_t on_period;
    int32_t off_period;
    int32_t status_led_send;
    char query_type;

	/* create socket on user apllication */
	if ((usr_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)       
    {
        printf("Unable to create socket on user side\n");
        return -1;
    }

    bbg_addr.sin_family = AF_INET;
    bbg_addr.sin_port = htons(PORT);

    /* Network byte order */
    if(inet_pton(AF_INET, "192.168.7.2", &bbg_addr.sin_addr)<=0) 
    {
        printf("Invalid address\n");
        return -1;
    }
    /* create a connection */
    if (connect(usr_socket, (struct sockaddr *)&bbg_addr, sizeof(bbg_addr)) < 0) 
    {
        printf("Unable to connect\n");
        return -1;
    }

    //sprintf(usr_msg, "%d %d %d %d", LED_period, LED_dutyCycle, LED_Toggle, read_query);
    sprintf(usr_msg, "%s", "SAVITHA");
    send(usr_socket , usr_msg , strlen(usr_msg) , 0 ); /* send to bbg application */

    if(read(usr_socket, usr_rec_buff, USR_BUFF_LEN) == -1)
        printf("user_Socket():error in reading\n"); 

    printf("%s\n",usr_rec_buff );


    time_period = 8000;
    duty_cycle = 70;
    status_led_send = 1;
    query_type = 'A';

    on_period = (float)time_period*((float)duty_cycle/(float)100);
    off_period = (time_period - on_period);
    printf("A: \n");
    sprintf(usr_msg,"%d %d %d %d %d %c",time_period,duty_cycle,on_period,off_period,status_led_send,query_type);
    send(usr_socket , usr_msg , strlen(usr_msg) , 0 ); /* send to bbg application */
    if(read(usr_socket, usr_rec_buff, USR_BUFF_LEN) == -1)
        printf("user_Socket():error in reading\n");
    printf("%s\n",usr_rec_buff );

    printf("B: \n");
    query_type = 'B';
    sprintf(usr_msg,"%d %d %d %d %d %c",time_period,duty_cycle,on_period,off_period,status_led_send,query_type);
    send(usr_socket , usr_msg , strlen(usr_msg) , 0 ); /* send to bbg application */
    if(read(usr_socket, usr_rec_buff, USR_BUFF_LEN) == -1)
        printf("user_Socket():error in reading\n");
    printf("%s\n",usr_rec_buff );

    printf("C: \n");
    query_type = 'C';
    sprintf(usr_msg,"%d %d %d %d %d %c",time_period,duty_cycle,on_period,off_period,status_led_send,query_type);
    send(usr_socket , usr_msg , strlen(usr_msg) , 0 ); /* send to bbg application */
    if(read(usr_socket, usr_rec_buff, USR_BUFF_LEN) == -1)
        printf("user_Socket():error in reading\n");
    printf("%s\n",usr_rec_buff );

    printf("D: \n");
    query_type = 'D';
    sprintf(usr_msg,"%d %d %d %d %d %c",time_period,duty_cycle,on_period,off_period,status_led_send,query_type);
    send(usr_socket , usr_msg , strlen(usr_msg) , 0 ); /* send to bbg application */
    if(read(usr_socket, usr_rec_buff, USR_BUFF_LEN) == -1)
        printf("user_Socket():error in reading\n");
    printf("%s\n",usr_rec_buff );

    return 0;
}
