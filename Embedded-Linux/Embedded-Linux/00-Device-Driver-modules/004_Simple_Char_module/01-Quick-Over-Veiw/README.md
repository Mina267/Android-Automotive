
# Creating a Character Device Driver in Linux Kernel

## Introduction
This guide walks you through the process of creating a pseudo character device driver in the Linux kernel. The driver will enable user-space applications to interact with the device through a file in `/dev`, allowing data storage and retrieval.

## Workflow Overview
1. **alloc_chrdev_region**: Allocates major and minor numbers (`dev_t`).
2. **cdev_init**: Initializes a `cdev` structure with the file operation structure.
3. **cdev_add**: Adds the character device to the kernel, linking the `cdev` object and `dev_t`.
4. **class_create**: Creates a new class in `/sys/class`.
5. **device_create**: Creates a device in the new class using `dev_t`.

    - Adds power subsystem and `uevent` to the device for udev to manage it under `/dev/`.

## Steps to Implement the Character Device Driver

### Step 1: Define Device File Operations
- Create `file_operations.h` to define operations like opening, closing, reading, and writing to the device.

### Step 2: Implement Driver Logic
- Implement the device driver logic in `file_operations.c`.
- Define a buffer to store data and implement the read and write operations.

### Step 3: Main Driver Initialization
- In `main.c`, initialize the driver and register it with the kernel.
  - Define the device name, class name, and other structures.
  - Allocate device numbers using `alloc_chrdev_region`.
  - Initialize the `cdev` structure with `cdev_init`.
  - Register the character device using `cdev_add`.
  - Create a device class with `class_create`.
  - Create the device file in `/dev` using `device_create`.

### Step 4: Makefile
- Write a Makefile to compile the driver modules.
  - Specify source files and dependencies.
  - Use `obj-m` and `obj-y` variables to specify the modules to build.

### Step 5: Compilation and Installation
- Run `make` to compile the driver modules.
- Install the driver modules with `insmod`.
- Verify installation with `lsmod` and `dmesg`.

### Step 6: Testing
- Use `echo` to write data to the device file (e.g., `/dev/your_device`).
- Use `cat` to read data from the device file and verify correct behavior.
  - Ensure data is appended on subsequent writes and displayed on reads.

### Step 7: Cleanup
- Unload the driver modules using `rmmod`.
- Remove the device file from `/dev`.
- Clean up any allocated resources.

