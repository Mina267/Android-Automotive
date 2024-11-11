## Module file
```c
#include <linux/init.h>       // Macros used to mark up functions e.g., __init __exit
#include <linux/module.h>     // Core header for loading LKMs into the kernel
#include <linux/kernel.h>     // Contains types, macros, functions for the kernel
#include <linux/fs.h>         // File system support
#include <linux/cdev.h>       // Character device structure
#include <linux/device.h>     // Device class support
#include <linux/uaccess.h>    // User space memory access functions
#include <linux/proc_fs.h>    // proc filesystem

/* Forward declaration of the read and write functions */
ssize_t	myread(struct file *files, char __user *buff, size_t size, loff_t *loff);
ssize_t	mywrite(struct file *files, const char __user *buff, size_t size, loff_t *loff);


// Define the proc file operations structure
const struct proc_ops proc_file_operations = 
{
    .proc_read = myread,    // Assign the read function
    .proc_write = mywrite   // Assign the write function
};

/* Pointer to the proc directory entry */
struct proc_dir_entry *entry;


/* 
 * Read function: Called when the /proc file is read 
 * This function logs a message and returns 0 indicating end of file.
 */
ssize_t myread(struct file *file, char __user *buff, size_t count, loff_t *pos)
{
    /* Print a message to the kernel log */
    printk("Hello from read Mina\n");
    return 0;   // Return 0 to indicate end of file
}


/* 
 * Write function: Called when the /proc file is written to.
 * This function logs a message, copies data from user space to kernel space,
 * and returns the number of bytes written.
 * 
 * Parameters:
 * - struct file *file: Pointer to the file structure
 * - const char __user *buff: Buffer in user space containing data to write
 * - size_t count: Number of bytes to write from the buffer
 * - loff_t *pos: Position in the file where the write should start
 */
ssize_t mywrite(struct file *file, const char __user *buff, size_t count, loff_t *pos)
{
    /* Print an informational message to the kernel log */
    printk("Hello from write Mina\n");

    /* Buffer in kernel space to hold copied data */
    char kernel_buffer[128];

    /* Adjust count if it exceeds the buffer size */
    if (count > sizeof(kernel_buffer))
        count = sizeof(kernel_buffer);

    /* Copy data from user space to kernel space using copy_from_user()
     * Note: buff is a user space address, not directly dereferenceable in kernel space.
     */
    if (copy_from_user(kernel_buffer, buff, count)) {
        printk("Failed to copy data from user space\n");
        return -EFAULT; // Return error if copy fails
    }

    /* Log the first byte of the data copied to the kernel buffer */
    printk("First byte = %c\n", kernel_buffer[0]);

    return count;   // Return the number of bytes written
}

/*  
 * Initialization function: Called when the module is loaded.
 * This function creates a /proc entry and logs a message.
 */
static __init int myModule_init(void) 
{
    printk("Proc file init\n");
    /* Create a /proc entry named "Mina" with read/write permissions */
    entry = proc_create("Mina", 0666, NULL, &proc_file_operations);
    /* File failed to create */
    if (!entry) {
        printk(KERN_ERR "Failed to create /proc entry\n");
        return 1;
    }

    return 0; // Return 0 if successfully loaded
}

/* 
 * Cleanup function: Called when the module is removed.
 * This function removes the /proc entry and logs a message.
 */
static void __exit myModule_deinit(void)
{
    /* Print an informational message to the kernel log */
    printk("Proc file deinit\n");
    /* Remove the /proc entry */
    proc_remove(entry);
}



module_init(myModule_init);
module_exit(myModule_deinit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mina");
MODULE_DESCRIPTION("A simple proc file module");
```



## Compiling the Module:
## Makefile
```mk
obj-m += myproc.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean

```











To test your kernel module that interacts with the proc filesystem, follow these steps:

### 1. **Compile the Module**

Make sure you have the correct kernel headers and build environment set up. Navigate to the directory containing your kernel module source code and run:

```bash
make
```

This should create a `.ko` file (e.g., `myproc.ko`).

### 2. **Insert the Module**

Use the `insmod` command to insert the module into the kernel:

```bash
sudo insmod myproc.ko
```

### 3. **Verify Module Loading**

Check that the module is loaded using:

```bash
lsmod | grep myproc
```

Or check the kernel log for messages:

```bash
sudo dmesg | tail
```

You should see messages from your `myModule_init` function indicating that the proc file entry was created.

### 4. **Check the /proc Entry**

After loading the module, verify that the `/proc` entry was created:

```bash
ls /proc/Mina
```

If it exists, the proc file was successfully created.

### 5. **Read from the /proc File**

Use the `cat` command to read from the proc file:

```bash
cat /proc/Mina
```

You should see the message "Hello from read Mina" in the kernel log, and `cat` will display an empty output since your `myread` function returns 0.

### 6. **Write to the /proc File**

Write data to the proc file using `echo` or `printf`:

```bash
echo "Test data" > /proc/Mina
```

You should see the message "Hello from write Mina" in the kernel log. The `mywrite` function will process the data, and you can see the first byte of the written data logged.

### 7. **Remove the Module**

To unload the module and remove the `/proc` entry:

```bash
sudo rmmod myproc
```

Verify that the module was removed:

```bash
lsmod | grep myproc
```

Check the kernel log to ensure that the `myModule_deinit` function executed and the proc file was removed:

```bash
sudo dmesg | tail
```

### Troubleshooting

If something doesn't work as expected:

1. **Check the Kernel Log**: Look for errors or warnings using `dmesg` to see if there are issues with loading or interacting with the module.
2. **Verify Permissions**: Ensure that your `/proc` entry has the correct permissions and that the file system supports proc operations.
3. **Check Module Dependencies**: Make sure that the kernel module doesn't have unmet dependencies.














# Additional Info.

## KERN_INFO
`KERN_INFO` is a macro used with the `printk` function in the Linux kernel to log informational messages. It specifies the log level of the message, which helps in categorizing and filtering log messages. Here's a detailed explanation and usage of `KERN_INFO`:

### `printk` Function

`printk` is the kernel's equivalent of the `printf` function in user space. It is used to print messages to the kernel log.

### Log Levels

The Linux kernel defines several log levels to categorize messages. These log levels are represented by macros:

- `KERN_EMERG`: Emergency messages, system is unusable.
- `KERN_ALERT`: Action must be taken immediately.
- `KERN_CRIT`: Critical conditions.
- `KERN_ERR`: Error conditions.
- `KERN_WARNING`: Warning conditions.
- `KERN_NOTICE`: Normal but significant condition.
- `KERN_INFO`: Informational messages.
- `KERN_DEBUG`: Debug-level messages.

### `KERN_INFO` Usage

`KERN_INFO` is used to log informational messages, which are important for understanding the system's behavior but do not indicate any errors or warnings.


## Returning the Count
The line return count; signifies that the function successfully wrote count bytes to the file. Returning the number of bytes written is a standard practice in file operations, as it informs the calling process (usually a user-space application) that the operation was successful and specifies how many bytes were processed.


<p align="center">
	<img src="https://github.com/user-attachments/assets/fd51289c-76f5-407b-b218-4579b9be8247" width=85% height=85% />
</p>

<p align="center">
	<img src="https://github.com/user-attachments/assets/dad30557-2789-4b05-a8b6-6a66bb0a8458" width=85% height=85% />
</p>
