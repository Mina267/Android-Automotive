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
    printk(KERN_INFO "Hello from write Mina\n");

    /* Buffer in kernel space to hold copied data */
    char kernel_buffer[128];

    /* Adjust count if it exceeds the buffer size */
    if (count > sizeof(kernel_buffer))
        count = sizeof(kernel_buffer);

    /* Copy data from user space to kernel space using copy_from_user()
     * Note: buff is a user space address, not directly dereferenceable in kernel space.
     */
    if (copy_from_user(kernel_buffer, buff, count)) {
        printk(KERN_ERR "Failed to copy data from user space\n");
        return -EFAULT; // Return error if copy fails
    }

    /* Log the first byte of the data copied to the kernel buffer */
    printk(KERN_INFO "First byte = %c\n", kernel_buffer[0]);

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