#include "file_operations.h"
#include <linux/uaccess.h>  // Required for copy_to_user, copy_from_user

#define BUFFER_SIZE 1024  // Size of the internal buffer

static char device_buffer[BUFFER_SIZE];  // Buffer to store data
static ssize_t buffer_pointer = 0;  // Points to the current position in the buffer

// Open function
int driver_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device opened\n");
    return 0;
}

// Close function
int driver_close(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device closed\n");
    return 0;
}

// Write function
ssize_t driver_write(struct file *file, const char __user *buf, size_t len, loff_t *off) {
    size_t to_copy, not_copied, delta;
    int space_available = BUFFER_SIZE - buffer_pointer;

    to_copy = min(len, (size_t)space_available);
    not_copied = copy_from_user(device_buffer + buffer_pointer, buf, to_copy);

    buffer_pointer += to_copy - not_copied;
    delta = to_copy - not_copied;

    printk(KERN_INFO "Received %ld bytes, %ld bytes copied to buffer\n", len, delta);
    return delta;
}

// Read function
ssize_t driver_read(struct file *file, char __user *buf, size_t len, loff_t *off) {
    size_t to_copy, not_copied, delta;

    to_copy = min(len, (size_t)buffer_pointer);
    if (to_copy == 0) {
        printk(KERN_INFO "No data to read\n");
        return 0;  // EOF
    }

    not_copied = copy_to_user(buf, device_buffer, to_copy);
    buffer_pointer -= to_copy - not_copied;
    delta = to_copy - not_copied;

    printk(KERN_INFO "Sent %ld bytes, %ld bytes copied to user\n", len, delta);
    return delta;
}