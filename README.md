# Install BusyBox
## Download Busy Box
```sh
git clone https://github.com/mirror/busybox.git

```
## Configure your Cross-Compiler and the Target Architecture
```sh
export CROSS_COMPILE=path/to/compiler/arm-cortexa9_neon-linux-musleabihf-
export ARCH=arm
```

## make menuconfig
* Select The Linking Type in the build process (Static)

* Select Settings and then go to Build option and select build static library

* Then Save and exit

## Build the commands source files
```sh
make
make install
file BusyBox
```

# reate Root File System (rootfs) for Embedded Linux Target

```sh
mkdir rootfs
```

## Copy the Content of ~/busybox/_install to rootfs_Static by unsing "cp or rsync"
```sh
rsync -av /path/to/source /path/to/destination
```
## Copy the Dynamic Kernel modules

## In rootfs Directory, create the other root directories manually
```sh
mkdir boot dev etc home mnt proc root srv sys
```

## Create a startup script called rcS in etc/init.d/ to do initialization tasks when booting the kernel
```sh
mkdir etc/init.d
touch etc/init.d/rcS
```
### Open rcS file and write the following commands then change its permission to make it executable :
```sh
vim etc/init.d/rcS
```
```sh
#!/bin/sh
# mount a filesystem of type `proc` to /proc
mount -t proc nodev /proc
# mount a filesystem of type `sysfs` to /sys
mount -t sysfs nodev /sys
# mount devtmpfs if you forget to configure it in Kernel menuconfig
#there is two options uncomment one of them  
#option1: mount -t devtmpfs devtempfs /dev
#option2: mdev -s 
```

## Change the Script permission to make it executable
```sh
chmod +x etc/init.d/rcS
```

## Create a Configuration file called inittab in etc directory
```sh
touch etc/inittab
```


### Open the file and write the follow lines on it:
```sh
vim etc/inittab
```
```sh
# inittab file 
#-------------------------------------------------------
#When system startup,will execute "rcS" script
::sysinit:/etc/init.d/rcS
#Start"askfirst" shell on the console (Ask the user firslty to press any key) 
ttyAMA0::askfirst:-/bin/sh
#when restarting the init process,will execute "init" 
::restart:/sbin/init
```


## Check Who is the owner of rootfs_Static files that is will be the rootfs of target.
```sh
ls -lh ~/rootfs
```
```sh
sudo chown -R root:root ~/rootfs
```

## Attach SD Image to Loop device
### Copy the all the contents under ~/rootf to the ext4 partition (p2) in SD card
* Mount rootfs of SD Card to host file system
* Copy the Contents of ~/rootfs_Static to /media/anas/rootfs
```sh
cp -rp ~/rootfs/* /media/mina/rootfs
```
### Copy the zImage s mount the boot partition (p1) of SD card(our kernel image) and vexpress DTB file to the boot partition in SD card.
* mount the boot partition (p1) of SD card
```sh
sudo cp  ~/linux/arch/arm/boot/zImage /media/mina/boot/
```

* Copy Vexpress DTB file to boot partition in SD card
```sh
sudo cp ~/linux/arch/arm/boot/dts/arm/*-ca9.dtb /media/mina/boot
```


# Boot the Kernel
## 1. Run Qemu
### Go to U-boot directory and run this command
```sh
qemu-system-arm -M vexpress-a9 -m 128M -nographic -kernel path/u-boot -sd path/sd.img
```
## 2- Set U-boot Environment variables
* is a variable that holds the command line arguments passed to the Linux kernel during the boot process. The bootargs variable is typically used to specify various parameters
* Command Line Parameters: The bootargs variable contains a string that represents the command line parameters passed to the Linux kernel.

```sh
setenv bootargs 'console=ttyAMA0 root=/dev/mmcblk0p2 rootfstype=ext4 rw rootwait init=/sbin/init' 
```

* bootargs: It is used to store command line arguments that will be passed to the Linux kernel during boot.
* 'console=ttyAMA0 root=/dev/mmcblk0p2 rootfstype=ext4 rw rootwait init=/sbin/init': This is the value assigned to the bootargs variable. It represents the command line arguments that will be passed to the Linux kernel during boot. Let's break down the components of these arguments:
* console=ttyAMA0: Specifies the console device. It's set to the serial port (ttyAMA0).
* root=/dev/mmcblk0p2: Specifies the root filesystem's block device. It indicates that the root filesystem is located on the SD card partition 2 (/dev/mmcblk0p2).
* rootfstype=ext4: Specifies the filesystem type of the root filesystem, it's set to ext4.
* rw: Indicates that the root filesystem should be mounted as read-write.
* rootwait: Causes the kernel to wait for the root device to become available before proceeding with the boot process.
* init=/sbin/init: Specifies the path to the init process, which is the first process started by the Linux kernel.


## Boot the zImage and DTB file from SD card
### Load the zImage from SD card (fat partition) to Target (Vexpress) RAM
```sh
fatload mmc 0:1 $kernel_addr_r zImage
```
* Check The Ram Content in kernel_addr_r
```sh
md $Zimag_RAM_Add
```

### Load Vexpress DTB file from SD card (fat partition) to Target (Vexpress) RAM
```sh
fatload mmc 0:1 $fdt_addr_r vexpress-v2p-ca9.dtb
```
* Check The Ram Content in dtb_hardware_Add
```sh
md $dtb_hardware_Add
```
### Booting the Kernel and DTB file
```sh
bootz $Zimag_RAM_Add - $dtb_hardware_Add
```









