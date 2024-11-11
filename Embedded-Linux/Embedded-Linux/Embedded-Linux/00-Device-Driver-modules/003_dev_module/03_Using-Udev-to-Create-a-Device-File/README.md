# Using Udev to Create a Device File Under `/dev`

When working with the Linux kernel and device drivers, you can use the `udev` device manager to automatically create device files under the `/dev` directory. This process involves detecting your custom device in the `/sys/class` directory and mapping it to a file in `/dev`.

#### Overview of the Process:

1. **Device Creation in `/sys/class`:**
   - When a kernel module (like `mydev.ko`) is loaded, it creates a device entry in the `/sys/class` directory. This directory contains subdirectories for various device classes managed by the kernel.

2. **Udev's Role:**
   - `udev` is responsible for managing device files in the `/dev` directory. It scans the `/sys/class` directory to detect newly created devices.
   - Based on the information it finds (such as the device's major and minor numbers), `udev` creates a corresponding device file in `/dev`.

#### Example Steps:

1. **View Existing Devices in `/sys/class`:**
   ```bash
   ls /sys/class
   ls /sys/class/tty
   ls /sys/class/tty/tty
   cat /sys/class/tty/tty/uevent
   cat /sys/class/tty/tty/dev
   ```























# Character Device Driver Example

This example demonstrates how to create a simple character device driver in Linux. The driver registers a device with a unique major and minor number, interacts with `udev` to create a corresponding device file in `/dev`, and properly cleans up upon module removal.

## Prerequisites

- Basic knowledge of C programming and Linux kernel modules.
- A Linux environment with kernel headers installed (for module compilation).

## Kernel Module Code

### Headers Used

```c
#include <linux/init.h>       // Include macros used to mark up functions, e.g., __init and __exit
#include <linux/module.h>     // Include the core header needed for loading Linux Kernel Modules (LKMs)
#include <linux/kernel.h>     // Include definitions for types, macros, and functions for the kernel
#include <linux/fs.h>         // Include support for file systems, including device registration
#include <linux/cdev.h>       // Include definitions for character device structure and operations
#include <linux/device.h>     // Include support for creating and managing device classes
#include <linux/uaccess.h>    // Include functions for user space memory access
#include <linux/proc_fs.h>    // Include support for the proc filesystem (if needed)
#include <linux/gpio.h>       // Include support for GPIO operations (if needed)

// Define the name of the device driver
#define DRIVER_NAME "my_char_device"

// Define the name of the device class
#define CLASS_NAME  "my_new_char_class"

// Define the name of the device
#define DEVICE1_NAME "mydevice1"

// Define the buffer size for data handling
#define BUFFER_SIZE 1024

// Declare a buffer for storing data, size defined by BUFFER_SIZE
char buffer[BUFFER_SIZE];

// Declare variables for device number and device class
static dev_t mydevice_id;                   // Variable to hold the device number (major + minor)
static struct class *mydevice_class;        // Pointer to hold the device class structure

/* 
 * Initialization function: This function is called when the module is loaded into the kernel.
 */
static int __init myModule_init(void)
{
    // Log a message indicating the initialization of the character device
    printk(KERN_INFO "Initializing Character Device\n");

    /* 
     * Request allocation of a device number.
     * The major number is allocated dynamically and minor number starts from 0.
     * If allocation fails, print an error message and return an error code.
     */
    if (alloc_chrdev_region(&mydevice_id, 0, 1, DRIVER_NAME) < 0) {
        printk(KERN_ERR "Device number allocation failed\n");
        return -1; // Return error code if device number allocation fails
    }

    /* 
     * Extract and print the major and minor numbers assigned to the device.
     * Major number is used by the kernel to identify the device driver,
     * Minor number is used to identify the specific device.
     */
    printk(KERN_INFO "Device registered: Major %d, Minor %d\n", MAJOR(mydevice_id), MINOR(mydevice_id));

    // Create a device class with the specified CLASS_NAME
    mydevice_class = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(mydevice_class)) {
        // If class creation fails, unregister the device number and print an error message
        unregister_chrdev_region(mydevice_id, 1);
        printk(KERN_ERR "Device class creation failed\n");
        return PTR_ERR(mydevice_class); // Return the error code from class creation
    }

    /* 
     * Create a device and register it with sysfs.
     * This function creates a device node in /sys/class/<class_name>/<device_name>.
     * If creation fails, clean up by destroying the class and unregistering the device number.
     */
    if (device_create(mydevice_class, NULL, mydevice_id, NULL, DEVICE1_NAME) == NULL) {
        class_destroy(mydevice_class);                // Destroy the device class
        unregister_chrdev_region(mydevice_id, 1);     // Unregister the device number
        printk(KERN_ERR "Device creation failed\n");  // Print an error message
        return -1; // Return error code if device creation fails
    }

    return 0; // Return 0 to indicate successful module loading
}

/* 
 * Cleanup function: This function is called when the module is removed from the kernel.
 */
static void __exit myModule_deinit(void)
{
    /* 
     * Destroy the device node created in /dev.
     * This function removes the device file from /dev/<device_name>.
     */
    device_destroy(mydevice_class, mydevice_id);

    /* 
     * Destroy the device class.
     * This function removes the class directory from /sys/class.
     */
    class_destroy(mydevice_class); 
    
    /* 
     * Unregister the device number.
     * This function releases the major and minor numbers allocated for the device.
     */
    unregister_chrdev_region(mydevice_id, 1);

    // Log a message indicating that the character device has been unregistered
    printk(KERN_INFO "Character Device Unregistered\n");
}

// Macros to specify the initialization and cleanup functions for the module
module_init(myModule_init);    // Register the initialization function
module_exit(myModule_deinit);  // Register the cleanup function

// Module information
MODULE_LICENSE("GPL");          // License type
MODULE_AUTHOR("Mina");         // Author of the module
MODULE_DESCRIPTION("A simple character device driver example."); // Description of the module

```

## Compiling the Kernel Module

1. **Create the `Makefile`:**

   ```Makefile
   obj-m += mydev.o

    all:
    	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules

    clean:
    	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean

   ```

2. **Compile the module:**

   Run the following command in the terminal:

   ```bash
   make
   ```

   This command compiles the module and generates a `mydev.ko` file.

## Loading the Kernel Module

1. **Load the Module:**

   ```bash
   sudo dmesg -c > /dev/null     # Clear the kernel ring buffer
   sudo insmod mydev.ko          # Load the module
   ```

2. **Verify Device Creation:**

   ```bash
   ls -lh /sys/class/ | grep my_new_char_class
   ls -lh /sys/class/my_new_char_class/
   ls -lh /sys/class/my_new_char_class/mydevice1
   ```

   The device `mydevice1` should be visible in the `/sys/class/my_new_char_class/` directory.

3. **Check Major and Minor Numbers:**

   ```bash
   cat /sys/class/my_new_char_class/mydevice1/dev
   ```

   This command displays the major and minor numbers assigned to the device.

4. **Verify Device File in `/dev`:**

   ```bash
   ls -lh /dev/ | grep mydevice1
   ```

   The device file `/dev/mydevice1` should be present.

## Interacting with the Device

Once the device is created, you can interact with it using standard file operations (`read`, `write`, etc.). You may need to implement these operations in the driver code if not done already.

## Unloading the Kernel Module

To clean up and remove the device:

```bash
sudo rmmod mydev
```

This command removes the kernel module, unregisters the device, and deletes the device file.

## Additional Information

- **`udev` Interaction:** `udev` is responsible for creating the device file in `/dev/`. When the module is loaded, `udev` detects the device and creates the corresponding file using the major and minor numbers assigned by the kernel.

- **Error Handling:** Ensure proper error handling is implemented in the driver to avoid resource leaks, especially in complex drivers with multiple devices or resources.

- **Expansion:** This basic driver can be expanded to include custom `read`, `write`, `ioctl`, and other operations as needed.

## Conclusion

This guide provided a step-by-step approach to creating a simple character device driver in Linux, including device file creation and module management. It serves as a foundation for developing more complex drivers with additional functionality.