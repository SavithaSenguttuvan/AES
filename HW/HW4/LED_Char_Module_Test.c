/*
 * LED_Char_Module_Test.c 
 *
 * @author: Savitha Senguttuvan
 * @brief:  C file to test the char driver
 */

#include "LED_Char_Module_Test.h"
#include <sys/socket.h> 
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 5000
#define BBG_BUFF_LEN 100

int main()
{
	int32_t ret, fd;
    int32_t on_period = 0;
    int32_t off_period = 0;
    int32_t received_period = 0;
    int32_t received_duty_cycle = 0;
    int32_t status_led_send = 0;
    int32_t status_led_receive = 0;
    char send_buff[BUFFER_LENGTH];
    char receive_buff[BUFFER_LENGTH];   /* Receive buffer */

    int32_t time_period;
    int32_t duty_cycle;
    char query_type;


    int bbg_serv_fd, conn_socket;
    struct sockaddr_in bbg_addr, usr_add;
    char bbg_buffer[BBG_BUFF_LEN];
    char bbg_to_usr[BUFFER_LENGTH] = "SAVITHA";


    if ((bbg_serv_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)     /* Socket creation */
    {
        printf("error in creating socket\n");
        return -1;
    }

    bbg_addr.sin_family = AF_INET;
    bbg_addr.sin_addr.s_addr = INADDR_ANY;
    bbg_addr.sin_port = htons( PORT );

    /* Bind address */
    if (bind(bbg_serv_fd, (struct sockaddr *)&bbg_addr, sizeof(bbg_addr))<0) 
    {
        printf("error in binding socket\n");
        return -1;
    }

    /* Listening on socket */
    if (listen(bbg_serv_fd, 7) < 0)       
    {
        printf("error in listening socket\n");
        return -1;
    }

    /* accept request */
    if ((conn_socket = accept(bbg_serv_fd, (struct sockaddr *)&usr_add, (socklen_t*)&usr_add))<0) 
    {
        printf("error in accepting socket\n");
        return -1;
    }

    if(read(conn_socket , bbg_buffer, BBG_BUFF_LEN) == -1)
        printf("Error in reading\n");

    printf("Data received from user is %s\n", bbg_buffer);
    
    send(conn_socket , bbg_to_usr , strlen(bbg_buffer), 0 );


    fd = open(DEVICE_NAME, O_RDWR);             // Open the device with read/write access
    if (fd < 0){
      perror("Test: Device open failure\n");
      return errno;
    }

    printf("A: in BBG_User_App\n");
    if(read(conn_socket , bbg_buffer, BBG_BUFF_LEN) == -1)
        printf("Error in reading\n");
    sscanf( bbg_buffer, "%d %d %d %d %d %c", &time_period,&duty_cycle,&on_period,&off_period,&status_led_send,&query_type );
    sprintf(send_buff,"%d %d %d %d %d %c",time_period,duty_cycle,on_period,off_period,status_led_send,query_type);

    ret = write(fd, send_buff, strlen(send_buff)); /* Write to the Module */
    if (ret < 0){
      perror("Test: Write msg failure");
      return errno;
    }

    ret = read(fd, receive_buff, BUFFER_LENGTH);       /* Read from the Module */
    if (ret < 0){
      perror("Test: Read msg failure");
      return errno;
    }
    printf("%s\n", receive_buff);
    send(conn_socket , receive_buff , strlen(receive_buff), 0 );

    printf("B: in BBG_User_App\n");
    if(read(conn_socket , bbg_buffer, BBG_BUFF_LEN) == -1)
        printf("Error in reading\n");
    sscanf( bbg_buffer, "%d %d %d %d %d %c", &time_period,&duty_cycle,&on_period,&off_period,&status_led_send,&query_type );
    sprintf(send_buff,"%d %d %d %d %d %c",time_period,duty_cycle,on_period,off_period,status_led_send,query_type);

    ret = write(fd, send_buff, strlen(send_buff)); /* Write to the Module */
    if (ret < 0){
      perror("Test: Write msg failure");
      return errno;
    }

    ret = read(fd, receive_buff, BUFFER_LENGTH);       /* Read from the Module */
    if (ret < 0){
      perror("Test: Read msg failure");
      return errno;
    }
    printf("%s\n", receive_buff);
    send(conn_socket , receive_buff , strlen(receive_buff), 0 );

    printf("C: in BBG_User_App\n");
    if(read(conn_socket , bbg_buffer, BBG_BUFF_LEN) == -1)
        printf("Error in reading\n");
    sscanf( bbg_buffer, "%d %d %d %d %d %c", &time_period,&duty_cycle,&on_period,&off_period,&status_led_send,&query_type );
    sprintf(send_buff,"%d %d %d %d %d %c",time_period,duty_cycle,on_period,off_period,status_led_send,query_type);

    ret = write(fd, send_buff, strlen(send_buff)); /* Write to the Module */
    if (ret < 0){
      perror("Test: Write msg failure");
      return errno;
    }

    ret = read(fd, receive_buff, BUFFER_LENGTH);       /* Read from the Module */
    if (ret < 0){
      perror("Test: Read msg failure");
      return errno;
    }
    printf("%s\n", receive_buff);
    send(conn_socket , receive_buff , strlen(receive_buff), 0 );

    printf("D: in BBG_User_App\n");
    if(read(conn_socket , bbg_buffer, BBG_BUFF_LEN) == -1)
        printf("Error in reading\n");
    sscanf( bbg_buffer, "%d %d %d %d %d %c", &time_period,&duty_cycle,&on_period,&off_period,&status_led_send,&query_type );
    sprintf(send_buff,"%d %d %d %d %d %c",time_period,duty_cycle,on_period,off_period,status_led_send,query_type);

    ret = write(fd, send_buff, strlen(send_buff)); /* Write to the Module */
    if (ret < 0){
      perror("Test: Write msg failure");
      return errno;
    }

    ret = read(fd, receive_buff, BUFFER_LENGTH);       /* Read from the Module */
    if (ret < 0){
      perror("Test: Read msg failure");
      return errno;
    }
    printf("%s\n", receive_buff);
    send(conn_socket , receive_buff , strlen(receive_buff), 0 );
    return 0;
} 