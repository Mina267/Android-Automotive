#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include "file_operations.h"

// Define constants for the driver and device names
#define DRIVER_NAME "my_char_device"
#define CLASS_NAME  "my_new_char_class"
#define DEVICE1_NAME "mydevice1"

static dev_t mydevice_id;  // Holds the major and minor numbers
static struct cdev cdev_object;  // Represents the char device structure
static struct class *mydevice_class;  // Holds the device class
static struct device *my_device;

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = driver_open,
    .release = driver_close,
    .read = driver_read,
    .write = driver_write,
};



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

    // Create a device class in the /sys/class directory
    mydevice_class = class_create(CLASS_NAME);
    if (IS_ERR(mydevice_class)) {
        unregister_chrdev_region(mydevice_id, 1);
        printk(KERN_ERR "Device class creation failed\n");
        return PTR_ERR(mydevice_class);  // Return failure
    }

    // Create a device and register it with sysfs, making it available in /dev/
    my_device = device_create(mydevice_class, NULL, mydevice_id, NULL, DRIVER_NAME);
    if (my_device == NULL) {
        class_destroy(mydevice_class);
        unregister_chrdev_region(mydevice_id, 1);
        printk(KERN_ERR "Device creation failed\n");
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
