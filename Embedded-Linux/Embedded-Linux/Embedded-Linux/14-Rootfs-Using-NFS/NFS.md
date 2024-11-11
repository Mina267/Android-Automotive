# BusyBox with NFS

## Table of Contents
1. [BusyBox](#1-busybox)
   - [Why are all binaries and executables symbolic links to BusyBox?](#11-why-all-binaries-and-executables-are-symbolic-links-to-busybox)
   - [Embedded Linux Board RAM without BusyBox](#12-embedded-linux-board-ram-without-busybox)
   - [How BusyBox (Dynamically Compiled) deals with RAM](#13-how-busybox-dynamically-compiled-deals-with-ram)
2. [Network File System (NFS)](#2-network-file-system-nfs)
   - [Linux Network File System](#21-linux-network-file-system)
     - [NFS in Embedded Linux](#211-nfs-in-embedded-linux)
   - [Install NFS on Linux (Ubuntu)](#22-install-nfs-on-linux-ubuntu)
3. [Mount Root File System through NFS Server](#3-mount-root-file-system-through-nfs-server)
4. [U-Boot Configuration](#4-u-boot-configuration)
   - [Run QEMU](#41-run-qemu)
   - [Load the Kernel from TFTP Server](#42-load-the-kernel-from-tftp-server)
   - [Boot the Kernel and Mount RootFS from NFS Server](#43-boot-the-kernel-and-mount-rootfs-from-nfs-server)
   - [Navigate Your Own OS](#44-navigate-your-own-os)
5. [References](#5-references)

---

## 1. BusyBox

BusyBox is a single binary containing all the commands/binaries of a root file system (rootfs). All binaries in the rootfs are symbolic links to the BusyBox executable.

### 1.1. Why are all binaries and executables symbolic links to BusyBox?

Symbolic links map standard command names (e.g., `ls`, `cat`, `cp`) to the BusyBox binary. When you run a command, you invoke the BusyBox binary with the command name as an argument.

#### 1.1.1. Space Efficiency
BusyBox is designed for embedded systems with limited storage. Combining multiple utilities into a single binary saves space compared to having individual binaries for each utility.

#### 1.1.2. Simplified Maintenance
With a single BusyBox binary, maintenance and updating are simplified. Instead of updating multiple binaries, you only need to update the BusyBox binary.

#### 1.1.3. Reduced I/O Operations
Using symbolic links reduces the number of separate files that need to be read and executed, which can result in reduced I/O operations, beneficial in resource-constrained environments.

### 1.2. Embedded Linux Board RAM without BusyBox

### 1.3. How BusyBox (Dynamically Compiled) deals with RAM

When you run a command, the OS creates a new process for that command, allocating memory (RAM) to it, including memory for the binary (code, data, stack, and heap).

Each command in BusyBox may depend on shared libraries. When a command is executed, the dynamic linker (system loader) loads necessary shared libraries into RAM if they are not already loaded. Shared libraries are typically loaded once and shared among multiple processes.

Example command execution:
```bash
busybox ls
```
The `ls` argument tells BusyBox which command to execute.

## 2. Network File System (NFS)

NFS is a distributed file system protocol allowing a user on a client computer to access files over a network as if they were on the local file system. NFS enables seamless sharing of files and resources between computers in a network.

### 2.1. Linux Network File System

NFS allows a system (servers) to share directories and files with others (clients) over a network. Users and programs can access files on remote devices almost as if they were local files. The default port for NFS server communication is port 2049.

#### 2.1.1. NFS in Embedded Linux

- **Root File System Over NFS:** Mount the root file system of an embedded device over NFS during development or debugging, allowing changes to the file system on the host machine to be seen on the embedded device without frequent flashing or updating.
- **Cross-Compilation:** Developers can cross-compile applications on a more powerful host machine and deploy the binaries to the embedded device via NFS.
- **File Sharing and Collaboration:** NFS facilitates file sharing and collaboration among multiple embedded devices or development boards connected to the same network.
- **Remote Debugging:** NFS is useful for remote debugging of applications running on an embedded system.
- **Software Updates and Distribution:** NFS simplifies the process of distributing software updates to multiple embedded devices.

### 2.2. Install NFS on Linux (Ubuntu)

1. Install the NFS kernel server:
   ```bash
   sudo apt install nfs-kernel-server
   ```
2. Check if NFS is installed successfully:
   ```bash
   systemctl status nfs-kernel-server
   ```
3. Check if the NFS server is listening on the default port (2049):
   ```bash
   ss -tulpen | grep 2049
   ```
4. Ensure the NFS kernel modules are loaded:
   ```bash
   lsmod | grep nfs
   ```

After installation, configure the NFS server by editing the `/etc/exports` file to include the directories you want to export.

## 3. Mount Root File System through NFS Server

1. Create a directory for NFS sharing:
   ```bash
   sudo mkdir /srv/nfs-share
   ```
2. Copy your rootfs to the NFS share directory:
   ```bash
   sudo cp -rp ~/rootfs_Dynamic/* /srv/nfs-share
   ```
3. Find your host machine's IP address:
   ```bash
   sudo apt install net-tools
   ifconfig
   ```
4. Edit the `/etc/exports` file to add the NFS export:
   ```bash
   sudo vim /etc/exports
   ```
   Add the following line:
   ```
   /srv/nfs-share 192.168.1.100(rw,no_root_squash,no_subtree_check)
   ```
5. Refresh the exports configuration:
   ```bash
   sudo systemctl restart nfs-kernel-server
   sudo exportfs -r
   ```
6. Ensure the NFS server is running:
   ```bash
   ps -ef | grep nfs
   ```

## 4. U-Boot Configuration

Configure the new IP addresses for the server (computer) and client (QEMU). Boot the kernel from the TFTP server and mount the root file system of the target from the NFS server.

### 4.1. Run QEMU

Run QEMU with the following command:
```bash
sudo qemu-system-arm -M vexpress-a9 -m 128M -nographic -kernel u-boot -sd sd.img -net tap,script=./qemu-ifup -net nic
```
Edit the `qemu-ifup` script for server IP configuration.

### 4.2. Configure IP Addresses

Configure the IP addresses of the server (computer) and client (QEMU):
```bash
setenv serverip 192.168.1.4
setenv ipaddr 192.168.1.100
```

### 4.3. Set Bootargs Variable

Set the `bootargs` variable:
```bash
setenv bootargs 'console=ttyAMA0 root=/dev/nfs ip=192.168.1.100:::::eth0 nfsroot=192.168.1.4:/srv/nfs-share,nfsvers=3,tcp rw init=/sbin/init'
```

