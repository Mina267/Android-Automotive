
# BusyBox Installation and Root Filesystem Creation for Embedded Linux

This guide provides a step-by-step process to install BusyBox, configure a cross-compiler, build the commands source files, create a root filesystem (rootfs) for an embedded Linux target, and boot the kernel using QEMU. Each step includes explanatory language for better understanding.

## 1. Download BusyBox

First, clone the BusyBox repository from GitHub:

```sh
git clone https://github.com/mirror/busybox.git
```

## 2. Configure Your Cross-Compiler and Target Architecture

Set the environment variables for the cross-compiler and target architecture. Adjust the `CROSS_COMPILE` path as per your setup:

```sh
export CROSS_COMPILE=path/to/compiler/arm-cortexa9_neon-linux-musleabihf-
export ARCH=arm
```

## 3. Configure BusyBox

Run the BusyBox configuration utility:

```sh
make menuconfig
```

### Configuration Steps:

1. **Select The Linking Type in the build process:**
   - Go to `Settings` > `Build Options`.
   - Select `Build Static Binary (no shared libs)`.

2. Save and exit the configuration menu.

## 4. Build the Commands Source Files

Build and install BusyBox:

```sh
make
make install
```

Verify the type of BusyBox binary:

```sh
file busybox
```

## 5. Create Root File System (rootfs) for Embedded Linux Target

Create a directory for the root filesystem:

```sh
mkdir rootfs
```

## 6. Copy BusyBox Installation to Root File System

Copy the contents of the BusyBox installation to the `rootfs` directory using `rsync`:

```sh
rsync -av /path/to/busybox/_install/ ~/rootfs
```

## 7. Create Additional Directories in rootfs

In the `rootfs` directory, create other necessary root directories manually:

```sh
mkdir  dev etc home mnt proc root srv sys

cp -r /home/mina/linux/lib/ ~/rootfs/

```

## 8. Create a Startup Script

Create a startup script called `rcS` in `etc/init.d/` to perform initialization tasks when booting the kernel:

```sh
mkdir -p etc/init.d
touch etc/init.d/rcS
```

Edit the `rcS` file:

```sh
vim etc/init.d/rcS
```

Add the following commands to the `rcS` script:

```sh
#!/bin/sh
# mount a filesystem of type `proc` to /proc
mount -t proc nodev /proc
# mount a filesystem of type `sysfs` to /sys
mount -t sysfs nodev /sys
# mount devtmpfs if you forget to configure it in Kernel menuconfig
mount -t devtmpfs devtmpfs /dev
```

Make the script executable:

```sh
chmod +x etc/init.d/rcS
```

## 9. Create a Configuration File (inittab)

Create an `inittab` file in the `etc` directory:

```sh
touch etc/inittab
```

Edit the `inittab` file:

```sh
vim etc/inittab
```

Add the following lines to the `inittab` file:

```sh
# inittab file 
#-------------------------------------------------------
# When system startup, will execute "rcS" script
::sysinit:/etc/init.d/rcS
# Start "askfirst" shell on the console (Ask the user firstly to press any key)
ttyAMA0::askfirst:-/bin/sh
# When restarting the init process, will execute "init"
::restart:/sbin/init
```

## 10. Set Ownership of rootfs Files

Ensure the ownership of `rootfs` files is set to `root`:

```sh
sudo chown -R root:root /path/to/rootfs

sudo chown -R root:root *
```

## 11. Prepare SD Card

### Copy Root Filesystem to SD Card

Mount the root filesystem of the SD card and copy the contents of `rootfs`:

```sh
cp -rp ~/rootfs/* /media/mina/rootfs
```

### Copy Kernel Image and DTB File

Mount the boot partition of the SD card and copy the kernel image and DTB file:

```sh
sudo mount /dev/loop0p1 /media/mina/boot
sudo cp /path/to/linux/arch/arm/boot/zImage /media/mina/boot/
sudo cp /path/to/linux/arch/arm/boot/dts/vexpress-v2p-ca9.dtb /mina/user/boot/
```

## 12. Boot the Kernel

### Run QEMU

Navigate to the U-Boot directory and run QEMU with the following command:

```sh
sudo qemu-system-arm -M vexpress-a9 -m 128M -nographic -kernel u-boot -sd ~/SD-card/sd.img  -net tap,script=./qemu-ifup -net nic
```

### Set U-Boot Environment Variables

Set the U-Boot `bootargs` environment variable:

```sh
setenv bootargs 'console=ttyAMA0 root=/dev/mmcblk0p2 rootfstype=ext4 rw rootwait init=/sbin/init'
```

Explanation of bootargs components:
- `console=ttyAMA0`: Specifies the console device (serial port).
- `root=/dev/mmcblk0p2`: Specifies the root filesystem's block device (SD card partition 2).
- `rootfstype=ext4`: Specifies the filesystem type (ext4).
- `rw`: Indicates the root filesystem should be mounted as read-write.
- `rootwait`: Causes the kernel to wait for the root device before proceeding.
- `init=/sbin/init`: Specifies the path to the init process.

### Load Kernel and DTB File into RAM

Load the kernel image:

```sh
fatload mmc 0:1 $kernel_addr_r zImage
```

Verify the RAM content:

```sh
md $kernel_addr_r
```

Load the DTB file:

```sh
fatload mmc 0:1 $fdt_addr_r vexpress-v2p-ca9.dtb
```

Verify the RAM content:

```sh
md $fdt_addr_r
```

### Boot the Kernel

Boot the kernel with the loaded image and DTB file:

```sh
bootz $kernel_addr_r - $fdt_addr_r
```

## Create script image and add to bootcmd
```sh 
setenv bootargs 'console=ttyAMA0 root=/dev/mmcblk0p2 rootfstype=ext4 rw rootwait init=/sbin/init'

fatload mmc 0:1 $kernel_addr_r zImage
fatload mmc 0:1 $fdt_addr_r vexpress-v2p-ca9.dtb
bootz $kernel_addr_r - $fdt_addr_r
```
``` sh
sudo mkimage -A arm -T script -C none -a 0x62000000 -e 0x62000000 -n 'load Script' -d BusyBox.txt /media/mina/boot/BusyBox.img
```

# Running
<p align="center">
	<img src="https://github.com/user-attachments/assets/ebc204f5-6efe-4ddb-b1fb-f32c336cc0f0" width=75% height=75% />
</p>

<p align="center">
	<img src="https://github.com/user-attachments/assets/af2d9bbd-c4e5-4a08-bdbc-9db1d25a6a4c" width=75% height=75% />
</p>


<p align="center">
	<img src="https://github.com/user-attachments/assets/82a2c2d1-cafd-4f19-a744-866c6ff73e30" width=75% height=75% />
</p>


By following these detailed steps, you will successfully install BusyBox, create a root filesystem, and boot the kernel for an embedded Linux target using QEMU.
