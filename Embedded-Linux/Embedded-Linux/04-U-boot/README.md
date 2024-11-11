
# U-Boot Installation and Configuration  for Vexpress Cortex A9 (QEMU Emulator)



## 1. Clone the U-Boot Repository

First, clone the U-Boot repository from GitHub. This repository contains all the necessary source code and configurations for U-Boot.

```bash
git clone https://github.com/u-boot/u-boot.git
```

## 2. Navigate to the U-Boot Directory

Change your working directory to the newly cloned U-Boot directory.

```bash
cd u-boot/
```

## 3. List Available Machine Configurations

List the available configurations for different machines to find the configuration specific to your machine. For Vexpress Cortex A9, filter the results using `grep`.

```bash
ls configs/ | grep $MACHINE_NAME
# For Vexpress Cortex A9:
ls configs/ | grep vexpress_ca9x4_defconfig
```

## 4. Set the Cross Compiler

Set the environment variables for the cross-compiler. This step ensures that U-Boot uses the correct compiler for the ARM architecture. Here, we are using the ARM Cortex A9 compiler (`arm-cortexa9_neon-linux-musleabihf`).

```bash
export CROSS_COMPILE=path/to/cross/compiler/arm-cortexa9_neon-linux-musleabihf-
# Example path:
export CROSS_COMPILE=~/x-tools/arm-cortexa9_neon-linux-musleabihf/bin/arm-cortexa9_neon-linux-musleabihf-
export ARCH=arm
```

## 5. Use Default Configurations for ARM Vexpress Cortex A9

Load the default configuration for the Vexpress Cortex A9 machine.

```bash
make vexpress_ca9x4_defconfig
```

## 6. Configure U-Boot

Enter the U-Boot configuration menu to customize settings as needed.

```bash
make menuconfig
```

### a. Support `bootd`

The `bootd` command is used to boot an operating system image from a device.

1. Navigate to **Command line interface**.
2. Select **Boot commands**.
3. Enable `bootd`.

### b. Support `editenv`

The `editenv` command allows interactive editing of U-Boot environment variables.

1. Navigate to **Environment commands**.
2. Enable `editenv` and `saveenv`.

### c. Store Environment Variable in `uboot.env`

Ensure that U-Boot environment variables are stored persistently in a file called `uboot.env`.

1. Navigate to **Environments**.
2. Ensure the FAT file is named `uboot.env`.

### d. Configure Shell Prompt

Set a custom shell prompt for U-Boot.

1. Return to the **home menu**.
2. Select **Command line interface**.
3. Set the shell prompt to `Mina=>`.

### e. Unset Support of Flash

Disable support for flashing firmware to the flash memory of the target device.

1. Navigate to **Environment**.
2. Unselect `Environment in flash memory`.

### f. Support FAT File System

Enable support for the FAT file system and configure it to work with MMC (MultiMediaCard) storage devices.

1. Navigate to **Device access commands**.
2. Enable `lsblk` option.

### g. Configure FAT Interface to MMC

Specify settings that allow U-Boot to interact with MMC devices and access the FAT file system.

1. Default name is `mmc` (you can change the name if desired).

### h. Configure Partition for FAT Storage

Specify the partition on the MMC device where the FAT file system is stored.

1. Navigate to **Device and partition for where to store the environment in FAT**.
2. Set the value to `0:1`.

### i. Configure Auto Boot Delay

Set a delay for automatic booting.

1. Navigate to **Boot options**.
2. Select **Auto boot** and set your preferred time delay (e.g., 5 seconds).

### j. Configure `bootcmd` Value

Set the `bootcmd` value to display a custom message during boot.

1. Navigate to **Boot options**.
2. Write your preferred commands

## 7. Build U-Boot

After configuring U-Boot, build it.

```bash
make
```

## 8. Resolve Missing OpenSSL Error (if needed)

If you encounter an error related to missing OpenSSL headers, install the OpenSSL development library.

```bash
sudo apt-get install libssl-dev
```

## 9. Successful Build

Upon successful build, you should see the build process output. Any warnings can generally be ignored.

```bash
# Example successful build output:
...
Building u-boot
...
```

**Congratulations! All configurations are DONE.**

---

<br>

# U-Boot on Vexpress-a9 Using QEMU

This guide provides detailed instructions on how to test U-Boot on a Vexpress-a9 machine using the QEMU emulator.

## Prerequisites

- A Debian-based Linux system (e.g., Ubuntu)
- Internet connection
- Basic knowledge of terminal commands

## Steps

### 1. Install QEMU

If you haven't installed QEMU before, you will face errors when trying to run QEMU commands. Use the following command to install QEMU for the ARM architecture:

```sh
sudo apt install qemu-system-arm
```

#### Explanation

- **sudo**: Runs the command with superuser (administrator) privileges.
- **apt**: The package management tool for Debian-based systems.
- **install**: Specifies that you want to install a package.
- **qemu-system-arm**: The package that includes the QEMU emulator for the ARM architecture.

#### Verify Installation

To ensure that `qemu-system-arm` is installed correctly, check its version or search for the installed package:

```sh
qemu-system-arm --version
```

or

```sh
dpkg -l | grep qemu-system-arm
```

### 2. Run QEMU with Emulated SD Card

Once QEMU is installed, you can run it to emulate the Vexpress-a9 machine with an ARM Cortex-A9 processor.

#### QEMU Run Command

```sh
qemu-system-arm -M vexpress-a9 -m 128M -nographic -kernel path/u-boot/u-boot -sd path/sd.img
```

#### Explanation

- **qemu-system-arm**: Command to run the QEMU emulator for the ARM architecture.
- **-M vexpress-a9**: Specifies the machine type to emulate (Versatile Express development board with ARM Cortex-A9).
- **-m 128M**: Sets the amount of RAM available to the emulated system (128 megabytes).
- **-nographic**: Disables graphical output and redirects the console to the terminal.
- **-kernel path/u-boot/u-boot**: Specifies the kernel image to be used (U-Boot bootloader).
- **-sd path/sd.img**: Attaches a virtual SD card to the emulated system.

#### Example Run Command

```sh
qemu-system-arm -M vexpress-a9 -m 128M -nographic -kernel ~/u-boot/u-boot -sd ~/SD-card/sd.img
```

### 3. Creating a Virtual SD Card

If you haven't created a virtual SD card, follow these steps:

1. **Create an empty file**:

    ```sh
    dd if=/dev/zero of=sd.img bs=1M count=64
    ```

2. **Format the SD card image**:

    ```sh
    mkfs.vfat sd.img
    ```

3. **Mount the image** to copy files if needed.

### 4. Booting

After running the QEMU command with the appropriate parameters, the emulated system should start booting. Since `-nographic` is used, the output will be in the terminal window where you ran the QEMU command. You should see the boot process of U-Boot, followed by any other boot steps configured.

### Summary

1. **Install QEMU**:
   - `sudo apt install qemu-system-arm`
   - Verify installation with `qemu-system-arm --version` or `dpkg -l | grep qemu-system-arm`.

2. **Run QEMU**:
   - Use `qemu-system-arm -M vexpress-a9 -m 128M -nographic -kernel path/u-boot/u-boot -sd path/sd.img`.
   - Ensure you have a properly created and formatted virtual SD card image.

3. **Booting**:
   - The system should start and output the boot sequence to your terminal, allowing you to interact with it through the console.

By following these steps, you can effectively test U-Boot on a Vexpress-a9 machine using the QEMU emulator.

