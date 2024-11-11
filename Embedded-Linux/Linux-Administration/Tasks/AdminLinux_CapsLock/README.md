
# Caps Lock Brightness Control 

This consists of two C programs designed to manipulate the Caps Lock brightness indicator on a Linux system. The first program reads the current state of the Caps Lock brightness and writes it to an output file. The second program reads this output file and toggles the Caps Lock brightness based on its content. Additionally, a bash script is used to execute these programs in a loop with a delay, effectively toggling the Caps Lock brightness every 3 seconds.

## File Structure

- `myexe1.c`: Reads the current Caps Lock brightness state and writes it to an output file.
- `myexe2.c`: Reads the output file and toggles the Caps Lock brightness state.
- `run_script.sh`: Bash script to run both programs in a loop with a delay.

## Program 1: myexe1.c

This program reads the current state of the Caps Lock brightness and writes it to an output file.

```c
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

    // Open Caps Lock brightness file for reading
    fdBrightness = open(SYSFS_PATH, O_RDONLY);
    // Open output file for writing
    fdOutput = open(OUTPUT_PATH, O_WRONLY);
    
    #if DEBUG == 1
    printf("My file descriptor brightness:%d \n", fdBrightness);
    printf("My file descriptor output:%d \n", fdOutput);
    #endif

    // Read the Caps Lock brightness state
    int r = read(fdBrightness, &var, 1);
    if (r > 0) {
        printf("Value of the Caps Lock brightness extracted to output file\n");
        write(fdOutput, &var, 1);
    }
    
    return 0;
}
```

## Program 2: myexe2.c

This program reads the output file and toggles the Caps Lock brightness state.

```c
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
    
    // Open Caps Lock brightness file for writing
    fdBrightness = open(SYSFS_PATH, O_WRONLY);
    // Open output file for reading
    fdOutput = open(OUTPUT_PATH, O_RDONLY);
    
    #if DEBUG == 1
    printf("My file descriptor brightness:%d \n", fdBrightness);
    printf("My file descriptor output:%d \n", fdOutput);
    #endif

    // Read the output file state
    int r = read(fdOutput, &var, 1);
    if (r > 0) {
        printf("Value of the output file extracted var = %c \n", var);
        
        // Toggle the Caps Lock brightness state
        if (var == '1') {
            var = '0';
        } else if (var == '0') {
            var = '1';
        }
        write(fdBrightness, &var, 1);
    }
    
    return 0;
}
```

## Script: run_script.sh

This bash script runs both programs in a loop with a 3-second delay between each execution to toggle the Caps Lock brightness.

```bash
#!/bin/bash

while true; do
    echo "Starting script..."
    ./myexe1 | sudo ./myexe2
    sleep 3  # Pauses for 3 seconds
    echo "3 seconds have passed."
done
```

## Usage

1. Compile both C programs:

```bash
gcc -o myexe1 myexe1.c
gcc -o myexe2 myexe2.c
```

2. Make the script executable:

```bash
chmod +x run_script.sh
```

3. Run the script with superuser privileges:

```bash
./run_script.sh
```

This setup will continuously toggle the Caps Lock brightness every 3 seconds.
