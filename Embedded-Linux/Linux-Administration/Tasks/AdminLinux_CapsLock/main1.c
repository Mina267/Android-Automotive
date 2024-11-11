#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define DEBUG  0

#define SYSFS_PATH "/sys/class/leds/input2::capslock/brightness"
#define OUTPUT_PATH "/home/mina/LecTask/output"

int main(void) {
    char var = 0;
    int fdBrightness = 0;
    int fdOutput = 0;
    /* Open a file and get its file descriptor in brightness */
    fdBrightness = open(SYSFS_PATH, O_RDONLY);
    /* Open a file and get its file descriptor output file*/
    fdOutput = open(OUTPUT_PATH, O_WRONLY);
    
    #if DEBUG == 1
    /* Print the file descriptor */
    printf("My file descriptor brightness:%d \n", fdBrightness);
    /* Print the file descriptor */
    printf("My file descriptor output:%d \n", fdOutput);
    #endif
    /* Read from brightness file descriptor */
    int r = read(fdBrightness, &var, 1);
    if (r > 0)
    {
    	printf("Value of the caps Lock brightness extracted to output file\n");
    	/* Write the content to the output file */
    	write(fdOutput, &var, 1);
    	
    }
    
    return 0;
}
