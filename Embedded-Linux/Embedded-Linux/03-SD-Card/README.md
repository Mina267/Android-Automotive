
# Creating a Virtual SD Card Image in Linux

This document provides a comprehensive guide on how to create a virtual SD card image in Linux. This includes creating an image file, configuring partitions, emulating the SD card, and mounting the partitions.

## Steps to Create a Virtual SD Card Image

### 1. Create a File Called "sd.img" with a Size of 1 GB
The following command creates a file named `sd.img` that is 1 GB in size, filled with zeros.

```bash
dd if=/dev/zero of=sd.img bs=1M count=1024
```

### 2. Configure the Partitions Table of the Virtual SD Card
Use `cfdisk` to partition the image file. This example creates a boot partition and a root filesystem partition.

```bash
cfdisk sd.img
```

#### In `cfdisk`:
1. Create a new partition for the boot:
    - Select "New" -> Enter size in MB -> Choose "Primary" -> Select "Type" -> Choose "FAT16" -> Select "Write".
2. Create a new partition for the root filesystem:
    - Select "New" -> Enter size in MB -> Choose "Extended" -> Select "Type" -> Choose "Linux" -> Select "Write".
3. Quit `cfdisk` after writing the partition table.

### 3. Emulate the `sd.img` as a Storage Device (SD card)

#### 3.1. Loop Device Driver
The following script sets up the image as a loop device and formats the partitions:

```bash
# Path to the image file
IMAGE_FILE="sd.img"

# Set up loop device and enable partition scanning
LOOP_DEVICE=$(sudo losetup -f --show --partscan "$IMAGE_FILE")

# Format the partitions
sudo mkfs.ext4 -L rootfs "${LOOP_DEVICE}p2"
sudo mkfs.vfat -F 16 -n boot "${LOOP_DEVICE}p1"

# List the block devices with their labels and file system types
lsblk -o NAME,LABEL,FSTYPE "${LOOP_DEVICE}"
```

### 4. Mount the Partitions
Create mount points and mount the partitions:

```bash
# Create mount points if they don't exist
BOOT_DIR=~/boot
ROOTFS_DIR=~/rootfs

mkdir -p "$BOOT_DIR" "$ROOTFS_DIR"

# Mount the partitions
sudo mount "${LOOP_DEVICE}p1" "$BOOT_DIR"
sudo mount "${LOOP_DEVICE}p2" "$ROOTFS_DIR"
```

### Summary
This guide walks you through creating a virtual SD card image, partitioning it, setting it up as a loop device, formatting the partitions, and finally mounting them. This process is useful for testing and development purposes when working with SD cards in a Linux environment.

## Additional Information
- Ensure you have `sudo` privileges to perform the above operations.
- The `dd` command is a powerful tool; use it with caution to avoid overwriting important data.
- The `losetup` command sets up and controls loop devices, which are used to mount files as block devices.

###  cfdisk sd.img Configuration

`cfdisk` is a partition editor that is used to create and modify the partition table on a disk or disk image. When you run `cfdisk` `sd.img`, you are performing the following tasks:

* *Creating Partitions*: You define the layout of the storage by creating partitions. For example, you might create a primary partition for the boot area and an extended partition for the root filesystem.
* *Setting Partition Types*: You specify the type of each partition (e.g., FAT16 for boot, Linux for the root filesystem).
* *Writing the Partition Table*: You save the partition layout to the disk image.
This step is crucial because it sets up the basic structure of the disk, indicating where different filesystems will be located.

###  sudo mkfs.ext4 -L rootfs "${LOOP_DEVICE}p2"
`mkfs.ext4` is a command used to create (format) a filesystem on a partition. When you run sudo `mkfs.ext4 -L rootfs "${LOOP_DEVICE}p2"`, you are performing the following tasks:

* *Formatting the Partition*: You create an ext4 filesystem on the specified partition `(${LOOP_DEVICE}p2)`. This process involves organizing the partition to store files in the `ext4` format.
* *Setting a Label*: The `-L` rootfs option sets a label for the filesystem, which can be used to identify it.

## Troubleshooting
- If you encounter issues with `losetup`, ensure the loop device modules are loaded using `sudo modprobe loop`.
- To check the status of loop devices, use `losetup -a`.
- Ensure the partitions are unmounted before detaching the loop device using `sudo umount /dev/loopXpY` and `sudo losetup -d /dev/loopX`.

Following these steps ensures effective creation and management of virtual SD card images in a Linux environment.

<br>

---

<br>
 
<p align="center">
	<img src="https://github.com/user-attachments/assets/41fbc223-a5a7-4243-91bd-a73b7a511ca2" width=70% height=70% />
</p>

```bash
#!/bin/bash

# Path to the image file
IMAGE_FILE="sd.img"

# Set up loop device and enable partition scanning
LOOP_DEVICE=$(sudo losetup -f --show --partscan "$IMAGE_FILE")

# Check if the loop device was successfully set up
if [ -z "$LOOP_DEVICE" ]; then
  echo "Failed to set up loop device."
  exit 1
fi

# Format the partitions
sudo mkfs.ext4 -L rootfs "${LOOP_DEVICE}p2"
sudo mkfs.vfat -F 16 -n boot "${LOOP_DEVICE}p1"

# List the block devices with their labels and file system types
lsblk -o NAME,LABEL,FSTYPE "${LOOP_DEVICE}"


# Create mount points if they don't exist, or remove them and recreate
BOOT_DIR=~/boot
ROOTFS_DIR=~/rootfs

if [ -d "$BOOT_DIR" ]; then
  rm -rf "$BOOT_DIR"
fi
mkdir -p 

if [ -d "$ROOTFS_DIR" ]; then
  rm -rf "$ROOTFS_DIR"
fi

# Create mount points
mkdir -p "$ROOTFS_DIR" "$BOOT_DIR"

# Mount the partitions
sudo mount "${LOOP_DEVICE}p1" ~/boot
sudo mount "${LOOP_DEVICE}p2" ~/rootfs

echo "Loop device set up as ${LOOP_DEVICE}"
```