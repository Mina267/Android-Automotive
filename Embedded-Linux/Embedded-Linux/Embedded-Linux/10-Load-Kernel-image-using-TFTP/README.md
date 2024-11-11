
# TFTP Server Setup on Linux

To set up and use a TFTP server on a Linux machine comprehensively, including all necessary details and additional context, follow these steps:

## 1. Install the TFTP Package

### Install the TFTP Server

```bash
sudo apt-get install tftpd-hpa
```

This command installs the TFTP daemon `tftpd-hpa`, which is a highly configurable TFTP server.

### Verify the Installation

After installation, ensure that the TFTP server is running and listening on the default TFTP port (69):

```bash
sudo ss -tulpn | grep :69
```
or
```bash
sudo systemctl status tftpd-hpa
```

These commands check if the TFTP server is active and listening on the correct port.

## 2. Configure the TFTP Server

### Edit the Configuration File

The configuration file for the TFTP server is located at `/etc/default/tftpd-hpa`. Open it with your preferred text editor:

```bash
sudo vim /etc/default/tftpd-hpa
```

Inside this file, you will see some default configurations. Modify or add the following line:

```bash
TFTP_OPTIONS="--secure --create"
```

- `--secure`: Restricts the TFTP server to a specific directory, enhancing security by preventing access to files outside this directory.
- `--create`: Allows the creation of new files on the server during file uploads. Without this option, the TFTP server might only allow reading or overwriting existing files but not creating new ones.

### Restart the TFTP Service

After making changes to the configuration file, restart the TFTP service to apply the new settings:

```bash
sudo systemctl restart tftpd-hpa
```

### Ensure the Service is Running

Verify that the TFTP service is running with the updated configuration:

```bash
sudo systemctl status tftpd-hpa
```

## 3. Set Up the TFTP Directory

### Default TFTP Directory

By default, the TFTP server uses `/srv/tftp` as the directory to serve files. Ensure this directory exists:

```bash
sudo mkdir -p /srv/tftp
```

### Change Ownership of the Directory

Change the ownership of the TFTP directory to the `tftp` user and group to ensure the TFTP server has the appropriate permissions:

```bash
sudo chown tftp:tftp /srv/tftp
```

## 4. Flash Through the TFTP Server

### U-Boot Configuration

If you're using U-Boot to load the kernel and other files via TFTP, configure the U-Boot environment variables appropriately.

### Place Files in the TFTP Directory

Place the necessary files such as `zImage` (compressed Linux kernel image) and `.dtb` (Device Tree Blob) in the `/srv/tftp` directory. For example:

- `zImage`: This is the compressed Linux kernel image used during the boot process.
- `.dtb`: The Device Tree Blob describes the hardware components of the system to the Linux kernel, allowing it to understand the hardware it is running on without needing hardcoded details in the kernel.

### Set U-Boot Environment Variables

On the target device, configure U-Boot to specify the TFTP server IP and the files to load:

```bash
setenv serverip <TFTP_SERVER_IP>
setenv ipaddr <TARGET_DEVICE_IP>
tftp $kernel_addr_r zImage
tftp $fdt_addr_r <DEVICE_TREE_FILE>.dtb
```

- `serverip`: The IP address of the TFTP server.
- `ipaddr`: The IP address of the target device.
- `tftp $kernel_addr_r zImage`: Loads the `zImage` from the TFTP server to the specified address in RAM.
- `tftp $fdt_addr_r <DEVICE_TREE_FILE>.dtb`: Loads the device tree file from the TFTP server to the specified address in RAM.

## Additional Information

### Verify the Package Installation

To check the files installed by the `tftpd-hpa` package, use the following command:

```bash
dpkg -L tftpd-hpa
```

This command lists all the files installed by the `tftpd-hpa` package.

### Manage the TFTP Service

The TFTP service can be managed using the `init.d` scripts. You can start, stop, restart, and check the status of the TFTP service with these commands:

```bash
sudo /etc/init.d/tftpd-hpa start
sudo /etc/init.d/tftpd-hpa stop
sudo /etc/init.d/tftpd-hpa restart
sudo /etc/init.d/tftpd-hpa status
```

## U-Boot and TFTP Interaction

- **U-Boot**: A popular bootloader used in embedded systems. It can load the kernel and other necessary files over TFTP, making it easier to update the kernel without physical access to the device.
- **TFTP Server**: The server from which the U-Boot bootloader retrieves files. The TFTP server must be correctly configured and accessible from the network.


<br>

---




# Example 


### Copy kernel image and dtb to TFTP server `srv/tftp`
```sh
sudo cp ~/linux/arch/arm/boot/zImage /srv/tftp/
sudo cp ~/linux/arch/arm/boot/dts/arm/vexpress-v2p-ca9.dtb /srv/tftp/
```


### Make small script to load zImage and dtb to RAM
```sh
sudo mkimage -A arm -T script -C none -a 0x62000000 -e 0x62000000 -n 'load Script' -d TFTP_script.txt ~/SD-card/boot/TFTP_script.img
```
#### TFTP_script.txt
```bash
setenv ipaddr 192.168.1.9
setenv serverip 192.168.1.8


 if ping 192.168.1.8; then
        echo "Network connection available, loading from network..."
        tftp $kernel_addr_r zImage
        tftp $fdt_addr_r vexpress-v2p-ca9.dtb
        bootz $kernel_addr_r - $fdt_addr_r
 fi
```

## U-boot
### Save script in bootcmd
```sh
editenv bootcmd
edit: fatload mmc 0:1 0x62000000 /TFTP_script.img; source 0x62000000
saveenv 
```
### Run qemu again

```sh
sudo qemu-system-arm -M vexpress-a9 -m 128M -nographic -kernel u-boot -sd ~/SD-card/sd.img  -net tap,script=./qemu-ifup -net nic

```
### Kernel will start, but it will panic 
<p align="center">
	<img src="https://github.com/user-attachments/assets/3f7f046b-594b-4c8d-a5ca-38709bb61b7d" width=100% height=100% />
</p>