/*
 * LED_Char_Module_Test.h 
 *
 * @author: Savitha Senguttuvan
 * @brief:  Header file to test the char driver
 */

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
 
#define BUFFER_LENGTH  (256)               /* Buffer length */
#define TIME_PERIOD    (10000)             /* (1/freq) */
#define DUTY           (20)                /* Duty cycle */
#define DEVICE_NAME    ("/dev/LED_Driver")

