# Creating the Root File System
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
# Path to ramfs script 
sh PATH_SCRIPT
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

# initramfs Script 
#### To select between two root filesystems rootfs1 and rootfs1 or quitting and use ramfs. `bin/RamfsScript` 
``` bash
#!/bin/sh
echo "Select your desired booting option:"
echo "1) rootfs1"
echo "2) rootfs2"
echo "3) Resume in initRamfs"
read -r choice

case $choice in
    1)
        echo "Launching rootfs one"
        mkdir -p /mnt/rootfs1
        mount -t ext4 /dev/mmcblk0p2 /mnt/rootfs1
        chroot /mnt/rootfs1
        ;;
    2)
        echo "Launching rootfs two"
        mkdir -p /mnt/rootfs2
        mount -t ext4 /dev/mmcblk0p3 /mnt/rootfs2
        chroot /mnt/rootfs2
        ;;
    3)
        echo "Resume in initRamfs"
        exit 0
        ;;
    *)
        echo "Wrong selection"
        ;;
esac


```
Make the script executable:

```sh
chmod +x ./RamfsScript
```
# Creating initramfs
* initramfs (initial ramdisk filesystem) is a temporary, early root filesystem that is mounted before the real root filesystem becomes available during the Linux kernel's initialization process. It is commonly used in the boot process to perform tasks such as loading essential kernel modules, configuring devices, and preparing the system for the transition to the actual root filesystem.

```sh
cd ~/rootfs
find . | cpio -H newc -ov --owner root:root > ../initramfs.cpio
cd ..
gzip initramfs.cpio
mkimage -A arm -O linux -T ramdisk -d initramfs.cpio.gz uRamdisk

sudo cp -rp uRamdisk /media/mina/boot

```


# Script to Booting with initramfs from bootcmd 


#### Copy uRamdisk you created earlier in this section to the boot partition on the microSD card, and then use it to boot to point that you get a U-Boot prompt. Then enter these commands:

```sh
sudo cp ./uRamdisk /media/mina
```
```bash
# In bootargs variable you need to configure like this
setenv bootargs "console=tty0 console=ttyAMA0, 38400n8 rdinit=/sbin/init"

# make sure the variable initramfs doesn't overwrite the dtb and zimage variables
setenv initramfs 0x60900000

fatload mmc 0:1 $kernel_addr_r zImage
fatload mmc 0:1 $fdt_addr_r vexpress-v2p-ca9.dtb
fatload mmc 0:1 $initramfs uRamdisk

bootz $kernel_addr_r $initramfs $fdt_addr_r


```

```sh
sudo mkimage -A arm -T script -C none -a 0x62000000 -e 0x62000000 -n 'load Script' -d RAMfs.txt /media/mina/boot/RAMfs.img
```


# Virtual SD Card Partitioning and Management

This project demonstrates how to create, partition, and manage a virtual SD card using loop devices in Ubuntu.

## Steps

1. **Create a Virtual Memory File:**

   ```bash
   dd if=/dev/zero of=sd.img bs=1M count=1024
   ```

2. **Setup Loop Device:**

   ```bash
   sudo losetup -f --show --partscan sd2.img
   ```

   Assume the loop device is `/dev/loop0`.

3. **Partition the Virtual Disk:**

   ```bash
   sudo cfdisk /dev/loop0
   ```

   In `fdisk`:
   - Press `o` to create a new empty DOS partition table.
   - Press `n` to create new partitions:
     - `boot`    (200MB)
     - `rootfs1` (400MB)
     - `rootfs2` (400MB)

4. **Format the Partitions:**

   ```bash
   sudo mkfs.vfat -F 16 -n boot /dev/loop0p1
   sudo mkfs.ext4 -L rootfs /dev/loop0p2
   sudo mkfs.ext4 -L rootfs /dev/loop0p3
   ```

5. **Mount the Partitions:**

   ```bash
   sudo mkdir -p ./boot ./rootfs1 ./rootfs2
   sudo mount /dev/loop0p1 ./boot
   sudo mount /dev/loop0p2 ./rootfs1
   sudo mount /dev/loop0p3 ./rootfs2
   ```

6. **Copy Files to New Partition:**

   ```bash
   sudo cp -r ~/rootfs/* ~/SD-card/rootfs1
   sudo cp -r ~/rootfs/* ~/SD-card/rootfs2
   ```


# running

```
sudo qemu-system-arm -M vexpress-a9 -m 128M -nographic -kernel u-boot -sd ~/SD-card/sd2.img  -net tap,script=./qemu-ifup -net nic
```

<p align="center">
	<img src="https://github.com/user-attachments/assets/26e99136-a684-44dd-b399-5edb116603a2" width=75% height=75% />
</p>

<p align="center">
	<img src="https://github.com/user-attachments/assets/fc63cce3-c627-4f39-afd0-2d919cae4163" width=75% height=75% />
</p>

<p align="center">
	<img src="https://github.com/user-attachments/assets/e456fb4c-6d0f-484c-89cc-169cebc5ab69" width=75% height=75% />
</p>
