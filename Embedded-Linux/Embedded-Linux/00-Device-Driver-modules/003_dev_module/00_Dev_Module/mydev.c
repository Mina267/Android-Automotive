#include <linux/init.h>       // Macros used to mark up functions e.g., __init, __exit
#include <linux/module.h>     // Core header for loading LKMs into the kernel
#include <linux/kernel.h>     // Contains types, macros, functions for the kernel
#include <linux/fs.h>         // File system support, defines file operations
#include <linux/cdev.h>       // Character device structure
#include <linux/device.h>     // Device class support
#include <linux/uaccess.h>    // User space memory access functions

// Define constants for the driver and device names
#define DRIVER_NAME "my_char_device"
#define CLASS_NAME  "my_new_char_class"
#define DEVICE1_NAME "mydevice1"

// Define the buffer size for data storage
#define BUFFER_SIZE 1024

// Global variables
char buffer[BUFFER_SIZE];                // Buffer for storing data
static dev_t mydevice_id;                // Device number (major + minor)
static struct class *mydevice_class;     // Device class structure
static struct cdev cdev_object;          // Character device structure

// Function prototypes for file operations
int driver_open(struct inode *device_file, struct file *instance);
int driver_close(struct inode *device_file, struct file *instance);
ssize_t driver_read(struct file *file, char __user *user_buffer, size_t size, loff_t *offset);
ssize_t driver_write(struct file *file, const char __user *user_buffer, size_t size, loff_t *offset);

// File operations structure defining the driver's capabilities
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = driver_read,
    .write = driver_write,
    .release = driver_close,
    .open = driver_open,
};

/********************* File operation functions ***********************/

// This function is called when the device file is opened
int driver_open(struct inode *device_file, struct file *instance) {
    printk("Device file opened\n");
    return 0;  // Return success
}

// This function is called when the device file is closed
int driver_close(struct inode *device_file, struct file *instance) {
    printk("Device file closed\n");
    return 0;  // Return success
}

// This function is called when the device file is read from
ssize_t driver_read(struct file *file, char __user *user_buffer, size_t size, loff_t *offset) {
    printk("Read operation called\n");
    // You would typically copy data from the kernel buffer to user space using copy_to_user()
    return size;  // Return the number of bytes read (currently just returning the size requested)
}

// This function is called when the device file is written to
ssize_t driver_write(struct file *file, const char __user *user_buffer, size_t size, loff_t *offset) {
    printk("Write operation called\n");
    // You would typically copy data from user space to the kernel buffer using copy_from_user()
    return size;  // Return the number of bytes written
}

/* 
 * Initialization function: Called when the module is loaded into the kernel.
 */
static int __init myModule_init(void) {
    printk("Initializing Character Device\n");

    // Request allocation of a device number (major + minor)
    if (alloc_chrdev_region(&mydevice_id, 0, 1, DRIVER_NAME) < 0) {
        printk(KERN_ERR "Device number allocation failed\n");
        return -1;  // Return failure
    }

    // Extract and print the major and minor numbers
    printk("Device registered: Major %d, Minor %d\n", MAJOR(mydevice_id), MINOR(mydevice_id));

    // Create a device class in the /sys/class directory
    mydevice_class = class_create(CLASS_NAME);
    if (IS_ERR(mydevice_class)) {
        unregister_chrdev_region(mydevice_id, 1);
        printk(KERN_ERR "Device class creation failed\n");
        return PTR_ERR(mydevice_class);  // Return failure
    }

    // Create a device and register it with sysfs, making it available in /dev/
    if (device_create(mydevice_class, NULL, mydevice_id, NULL, DEVICE1_NAME) == NULL) {
        class_destroy(mydevice_class);
        unregister_chrdev_region(mydevice_id, 1);
        printk(KERN_ERR "Device creation failed\n");
        return -1;  // Return failure
    }

    // Initialize the cdev structure and add it to the kernel
    cdev_init(&cdev_object, &fops);
    cdev_object.owner = THIS_MODULE;

    // Add the character device to the system
    if (cdev_add(&cdev_object, mydevice_id, 1) < 0) {
        device_destroy(mydevice_class, mydevice_id);
        class_destroy(mydevice_class);
        unregister_chrdev_region(mydevice_id, 1);
        printk(KERN_ERR "Failed to add cdev\n");
        return -1;  // Return failure
    }

    printk("Device initialized successfully\n");
    return 0;  // Return success
}

/* 
 * Cleanup function: Called when the module is removed from the kernel.
 */
static void __exit myModule_deinit(void) {
    // Destroy the device created with device_create()
    device_destroy(mydevice_class, mydevice_id);

    // Destroy the device class created with class_create()
    class_destroy(mydevice_class);

    // Remove the cdev object from the system
    cdev_del(&cdev_object);

    // Unregister the allocated device number
    unregister_chrdev_region(mydevice_id, 1);
    printk("Character Device Unregistered\n");
}

// Register the initialization and cleanup functions
module_init(myModule_init);
module_exit(myModule_deinit);

MODULE_LICENSE("GPL");  // Specify the license for the module
MODULE_AUTHOR("Mina");  // Specify the author of the module
MODULE_DESCRIPTION("A simple character device driver example.");  // Describe the module
