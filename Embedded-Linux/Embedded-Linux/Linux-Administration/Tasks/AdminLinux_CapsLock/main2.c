#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define DEBUG  0
#define SYSFS_PATH "/sys/class/leds/input2::capslock/brightness"
#define OUTPUT_PATH "/home/mina/LecTask/output"
int main(void) 
{
    char var = 0;
    int fdBrightness = 0;
    int fdOutput = 0;
    
    /* Open a file and get its file descriptor in brightness */
    fdBrightness = open(SYSFS_PATH, O_WRONLY);
    
    /* Open a file and get its file descriptor output file*/
    fdOutput = open(OUTPUT_PATH, O_RDONLY);
    
    #if DEBUG == 1
    /* Print the file descriptor */
    printf("My file descriptor brightness:%d \n", fdBrightness);
    /* Print the file descriptor */
    printf("My file descriptor output:%d \n", fdOutput);
    /* Read from brightness file descriptor */
    #endif
    int r = read(fdOutput, &var, 1);
    if (r > 0)
    {
    	printf("Value of the output file extracted var = %c \n", var);
    	
    	if (var == '1')
    	{
    		/* Write the zero into the brightness file */
    		var = '0';
    	}
    	else if (var == '0')
    	{
    		/* Write the one into the brightness file */
		var = '1';
    	}
    	write(fdBrightness, &var, 1);
    	
    	
    }
    
    return 0;
}
