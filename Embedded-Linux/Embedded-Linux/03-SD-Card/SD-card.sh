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