# *permissions*
## list
```sh
ls -lh
```

> \- | --- | --- | --- | owner : group myfile

> *File type* | *owner* | *group* | *other*
> ## File type
> - `-`: Regular file, (main.c, .txt)
> - `b`: Block device.
> - `e`: Character device series.
> - `n`: Network device
> - `d`: Directory device

## Owner of file
> #### *The one who create the file*

- *Example*
```sh
touch newFile
mkdir myDir
```

## Group
> #### *Primary group of owner*

> ### Each user has 
- *Primary group* only one group when user `created`.
- Secondary group user can associate with Infinite number of secondary groups.
- Secondary group when we include user in another group.

```sh
adduser USER_NAME
```

### User Creation and Skeleton Directory (`/etc/skel`)

When a new user is created on a Unix-like system, the system copies the contents of the `/etc/skel` directory to the new user's home directory. The `/etc/skel` directory contains default configuration files that ensure each user starts with a standardized set of configurations.

### Contents of `/etc/skel`

The `/etc/skel` directory typically includes the following files:
- `.profile`
- `.bashrc`
- `.bash_logout`

### Example Files

- `/etc/skel/.profile`: Configuration file for login shells.
- `/etc/skel/.bashrc`: Configuration file for interactive non-login shells.
- `/etc/skel/.bash_logout`: Script to execute upon logout.

## User Creation Process

When a new user is created, the following steps are performed:

1. **Create a New User:**
> ```sh
>adduser USER_NAME
>```
> - `/etc/passwd`: user in device.
> - `/etc/shadow`: passwords.
> - `/etc/group`: group.
> 
>  - The contents of `/etc/skel` are copied to `/home/newuser`.
>
2. **Verify the New User's Home Directory:**
>   ```sh
>   ls -a /home/newuser
>   ```
> - The home directory will contain `.profile`, `.bashrc`, and other files copied from `/etc/skel`.

## Customization for Each User

Each user can customize their environment by modifying the `.profile`, `.bashrc`, and other dot files in their home directory. This allows for personalized settings while ensuring a consistent initial configuration provided by `/etc/skel`.



## Example
```sh
touch myFile
-rw-rw-r-- mina mina myFile
# -         | rw-  |  rw-   | r-- 
# File type | user |  grpup | other
```


> ```sh
> adduser NewUser
> ```
> - Not owner ❌
> - Not in same group ❌
> - Other ✅
> 
> ```sh
> cat myFile 
> ```
>  - Can read the file ✅
> ```sh
> echo 1 >> myFile 
> ```
> - Write permission denied ❌
> - Other for that file only have read permission `r--`
---
## Read permission
> #### *File*: `cat` `less` `head` `tail` `less` `vim` `vi` `nano` 
> #### *Directory*: `ls`

## Write permission
> #### *File*:  `gedit` `echo` `vim` `vi` `nano` 
> #### *Directory*:  `touch` `mkdir` `rm`

## Excutable permission
> #### *File*:  `bash` `./` `source` 
> #### *Directory*:  `touch` `ls` `etc.` *All Commands*.
> directory permission `rw-` commans like 
```sh
touch myFile
cat myFile
```
> Will not premited if there is no *Excutable permission*
```sh
chmod +x myFile
```

---
### Note:
    - Kernel has only write and read permission only, there is no executable permission.
    - User space has executable permission 
---
## *How to change permission*
```
Owner | Group | Other 
  u   |   g   |   o
 ---  |  ---  |  ---
 rwx  |  rwx  |  rwx
```

## `chmod`
> ### *Octal*
> ``` 
> 111 = 7
> rwx
> 101 = 5
> r-x
> ```
> ``` bash
> # All have rwx permission  7 --> 111
> chmod 777 myFile
> # All have rw- permission  6 --> 011
> chmod 666 myFile
> 
> ```

> ### *alph*

> ``` bash
> # All have rwx permission  7 --> 111
> chmod ugo=x
> chmod ugo +x
> chmod +x
> chmod ug=rw
> ```



## Example 1
- File permission `-rw-rwr--`, To make user has ability to read and write to that file
### 1- `chmod`
```sh
chmod 666 myFile
```
### 2- Linux command used to add a user to a group
```sh
sudo usermod -aG GROUP_NAME USER_NAME
```
> `-aG`: These are options for the usermod command.
> - -a stands for "append," which means add the user to the supplementary group(s).
> - -G specifies the group(s) to which the user should be added.

> `vim /etc/group/` GROUP_NAME append USER_NAME

## Example 2
- Users: mina, NEW_USER
- *Group HR*: NEW_USER
- *Group mina*: mina;

Mina user
```sh
# rw-rw-r--
touch myFile 
```
### *Change Group of myFile*
```sh
ls -lh myFile
# -rw-rwr-- mina mina myFile
chgrp HR myfile
ls -lh myFile
# -rw-rwr-- mina HR myFile
chown  :HR myFile

```

### *Change Owner of myFile*
```sh
chown NEW_USER myFile
# -rw-rwr-- NEW_USER mina myFile
```
### *Change Owner and Group of myFile*

```sh
chown NEW_USER:HR myFile
# -rw-rwr-- NEW_USER HR myFile
```

### Who can change permission?
> - owner of file
> - sudo
> - root

### Who can change Owners& Groups?

> - sudo
> - root

rwx simple permission
<br>
<br>
<br>


---
# *Special permission*
## 1- Set User id (S)
* with Executable files

#### command `passwd` : 
> - change password of user
```sh
$ passwd
```
#### Show permission of shadow that change store password of users
```sh
ls -lh /etc/passwd
# -rw-r--r-- root root /etc/passwd
ls -lh /etc/shadow 
# -rw-r----- root shadow /etc/shadow
```
### How can users(Others) change their password in shadow if they have not write permission on the files?
> `passwd` Give root privalage in reading and write on file `/etc/shadow`


### Changing User Passwords with the `passwd` Command

The `passwd` command is used to change user passwords on Unix-like systems. It operates with special permissions (setuid) that allow normal users to change their own passwords and superusers to change any user's password.

### Using `passwd` to Change Your Own Password

1. **Open a Terminal.**
2. **Run the `passwd` command:**
   ```sh
   passwd
   ```
3. **Follow the Prompts:**
   - Enter your current password.
   - Enter your new password.
   - Confirm your new password.

### Example
```sh
$ passwd
Changing password for user your_username.
Current password:
New password:
Retype new password:
passwd: all authentication tokens updated successfully.
```

### Using `passwd` to Change Another User's Password

To change another user's password, you need superuser privileges.

1. **Open a Terminal.**
2. **Use `sudo` to Run the `passwd` Command with the Target Username:**
   ```sh
   sudo passwd username
   ```
3. **Follow the Prompts:**
   - Enter and confirm the new password for the specified user.

### Example
```sh
$ sudo passwd john
[sudo] password for your_username:
Enter new UNIX password:
Retype new UNIX password:
passwd: password updated successfully.
```

### Understanding setuid

The `setuid` (set user ID) permission allows a program to run with the privileges of the file's owner. The `passwd` command typically has the setuid bit set, which allows it to modify the `/etc/shadow` file where hashed passwords are stored.

### Checking setuid on `passwd`

You can verify if the `passwd` command has the setuid bit set by running:
```sh
ls -l /usr/bin/passwd
```

You should see an `s` in the file permissions:
```sh
-rwsr-xr-x 1 root root 54256 Apr  1  2023 /usr/bin/passwd
```

### Setting setuid on `passwd`

If the setuid bit is not set, you can set it using the `chmod` command as root:
```sh
sudo chmod u+s /usr/bin/passwd
```

## 1- *set group id* (S)
> - inherit group inside directory
> - Make new or directorty inherit group rather than the primary group of directory owner


### setgid (Set Group ID) 
The `setgid` (Set Group ID) permission is used in Linux systems to control the default group ownership of new files and directories created within a directory. When set on a directory, it ensures that new files and subdirectories inherit the group ownership of the directory, rather than the primary group of the user who created the file or subdirectory. This is useful for collaborative environments where multiple users need to work on the same set of files.

## Using `setgid` on a Directory

### 1. Setting the `setgid` Bit

To set the `setgid` bit on a directory, use the `chmod` command with the `g+s` option:

```sh
sudo chmod g+s directory_name
```

### 2. Verifying the `setgid` Bit

To verify that the `setgid` bit is set on a directory, use the `ls -l` command:

```sh
ls -ld directory_name
```

You should see an `s` in the group permissions:

```sh
drwxr-sr-x 2 user group 4096 Jul 16 12:34 directory_name
```

### 3. Inheriting Group Ownership

When the `setgid` bit is set on a directory, new files and subdirectories created within it inherit the group ownership of the directory, not the primary group of the user who created them.

### Example

1. **Create a Directory and Set the `setgid` Bit:**

```sh
sudo mkdir /path/to/shared_dir
sudo chmod g+s /path/to/shared_dir
sudo chown :sharedgroup /path/to/shared_dir
```

2. **Verify the `setgid` Bit:**

```sh
ls -ld /path/to/shared_dir
```

Output:

```sh
drwxr-sr-x 2 user sharedgroup 4096 Jul 16 12:34 /path/to/shared_dir
```

3. **Create a New File in the Directory:**

```sh
touch /path/to/shared_dir/newfile
```

4. **Verify the Group Ownership of the New File:**

```sh
ls -l /path/to/shared_dir/newfile
```

Output:

```sh
-rw-r--r-- 1 user sharedgroup 0 Jul 16 12:34 /path/to/shared_dir/newfile
```

The new file `newfile` inherits the group ownership `sharedgroup` from the directory `shared_dir`.

## Summary

The `setgid` bit on a directory ensures that new files and directories created within it inherit the group ownership of the directory. This is particularly useful in collaborative environments where multiple users need to work on shared files, as it maintains consistent group ownership and facilitates easier management of permissions.

By using the `setgid` permission, you can streamline collaboration and ensure that group ownership is properly maintained across shared resources.

## 3- Sticky Bit (`t`)


The sticky bit is a special permission used on directories to prevent users from deleting or renaming files in the directory unless they own the files or have superuser privileges. This is particularly useful in shared directories where you want to allow multiple users to create files but prevent them from deleting or modifying each other's files.

## Using the Sticky Bit on a Directory

### Scenario

Consider a directory called `shared_dir` with special permissions set for group ID (setgid). User `mina` is the owner of this directory and it belongs to the group `mina`, which includes two other users. When any user in the group creates a file in this directory, the file's owner will be the user who created it, and the group will be `mina`. However, without the sticky bit, any user in the group can delete or rename files created by other users.

To protect against this, you can set the sticky bit on the directory.

### Setting the Sticky Bit

To set the sticky bit on a directory, use the `chmod` command with the `+t` option:

```sh
sudo chmod +t directory_name
```

### Verifying the Sticky Bit

To verify that the sticky bit is set on a directory, use the `ls -l` command:

```sh
ls -ld directory_name
```

You should see a `t` at the end of the directory's permissions:

```sh
drwxrwsrwt 2 mina mina 4096 Jul 16 12:34 shared_dir
```

### Example

1. **Create a Directory and Set the `setgid` Bit:**
    ```sh
    sudo mkdir /path/to/shared_dir
    sudo chmod g+s /path/to/shared_dir
    sudo chown mina:mina /path/to/shared_dir
    ```

2. **Set the Sticky Bit on the Directory:**
    ```sh
    sudo chmod +t /path/to/shared_dir
    ```

3. **Verify the Sticky Bit:**
    ```sh
    ls -ld /path/to/shared_dir
    ```

    Output:

    ```sh
    drwxrwsrwt 2 mina mina 4096 Jul 16 12:34 /path/to/shared_dir
    ```

### Creating and Managing Files

1. **User `user1` Creates a File:**
    ```sh
    touch /path/to/shared_dir/file1
    ls -l /path/to/shared_dir/file1
    ```

    Output:

    ```sh
    -rw-r--r-- 1 user1 mina 0 Jul 16 12:35 /path/to/shared_dir/file1
    ```

2. **User `user2` Creates a File:**
    ```sh
    touch /path/to/shared_dir/file2
    ls -l /path/to/shared_dir/file2
    ```

    Output:

    ```sh
    -rw-r--r-- 1 user2 mina 0 Jul 16 12:36 /path/to/shared_dir/file2
    ```

3. **File Protection with Sticky Bit:**

    With the sticky bit set, `user1` cannot delete or rename `user2`'s file and vice versa. Only the file's owner or a superuser can delete or rename their files.

### Summary

The sticky bit ensures that only the owner of a file or a superuser can delete or rename files in a shared directory, preventing users from interfering with each other's files. This is particularly useful in collaborative environments where multiple users need to create and manage files in the same directory.

By using the sticky bit, you can maintain better control over file permissions and protect users' files from being deleted or modified by others.

---

# Set special permission
```
     USer   |     Group    |   Other
Set user id | set group id | sticky bit
   - - -    |     - - -    |   - - -
       s    |         s    |       t
       1    |         1    |       1
```

```sh
chmod    4       777   myFile
#     special  normal
chmod 1 777 myFile      
chmod o+t myFile
chmod u+s myFile
chmod g+s myFile
```

## Tips commands
```sh
# List member of the group
groupmems -g GROUP_NAME -l
#
group del
```

## Lab
## Issue and Solution

### Issue

Running `groupmems` without `sudo` results in the following error:

```sh
groupmems: cannot open /etc/gshadow
```

### Breakdown of the Solution

1. **Check Group Members:**

    ```sh
    groupmems -g hr -l
    ```

    This command failed because it couldn't access `/etc/gshadow`.

2. **Run with `sudo`:**

    ```sh
    sudo groupmems -g hr -l
    ```

    This worked and showed that `fady` is a member of the `hr` group, indicating that running with elevated privileges can access `/etc/gshadow`.

3. **Check Permissions on `/etc/gshadow`:**

    ```sh
    ls -lh /etc/gshadow
    ```

    Shows the file is owned by `root` and belongs to the `shadow` group with restricted permissions.

4. **Check `groupmems` Executable:**

    ```sh
    ls -lh /usr/sbin/groupmems
    ```

    Shows the `groupmems` executable with `rwxr-xr-x` permissions, owned by `root`.

5. **Set Setuid Bit:**

    ```sh
    sudo chmod u+s /usr/sbin/groupmems
    ```

    This sets the setuid bit on the `groupmems` executable, allowing it to run with the permissions of its owner (`root`).

6. **Verify Setuid Bit:**

    ```sh
    groupmems -g hr -l
    ```

    Now it works without `sudo`, indicating the setuid bit is set correctly.

7. **Remove Setuid Bit:**

    ```sh
    sudo chmod u-s /usr/sbin/groupmems
    ```

### Summary

Setting the setuid bit on the `groupmems` executable allows it to access `/etc/gshadow` without needing to use `sudo`. However, using the setuid bit should be done cautiously as it can have security implications. If running `groupmems` without `sudo` is a regular requirement, keeping the setuid bit set might be convenient. Otherwise, you can continue using `sudo` to maintain a higher security level.

## Example Commands

```sh
# Run without sudo (will fail initially)
groupmems -g hr -l

# Run with sudo (will succeed)
sudo groupmems -g hr -l

# Set the setuid bit to allow running without sudo
sudo chmod u+s /usr/sbin/groupmems

# Run without sudo (will succeed now)
groupmems -g hr -l

# Remove the setuid bit for security
sudo chmod u-s /usr/sbin/groupmems
```

By following these steps, you can manage group memberships using `groupmems` while understanding the security implications of using the setuid bit.


<br>
<br>

<br>

<br>

---
---
---
# Linux Processes and System Information

## Overview

This document provides a comprehensive guide to understanding and managing Linux processes, as well as accessing various system information through the `/proc` filesystem.

## Linux Processes

### Process IDs (PID and PPID)

- **PID**: Process ID, a unique identifier for each running process.
- **PPID**: Parent Process ID, the PID of the process that started the current process.

### The `/proc` Filesystem

The `/proc` filesystem is a virtual filesystem providing kernel and process information.

#### Key Characteristics

- **Virtual Filesystem**: Represents kernel data structures and process information.
- **Zero Size**: The directory itself takes up no space on disk as it is stored in RAM.

#### Example Commands

- `sudo du -sh /proc/`: Shows that `/proc` is zero in size.
- `cat /proc/consoles`: Displays console information.
- `cat /proc/cpuinfo`: Provides detailed CPU information.
- `sudo du -sh /proc/cpuinfo`: Shows that `/proc/cpuinfo` is zero in size.

## Process Information

### Priority

Processes have priorities ranging from -20 (highest) to 19 (lowest).

#### Managing Priorities

- `nice -n -5 ./script`: Start a process with a specified priority.
- `renice -n -20 -p PID`: Change the priority of an already running process.

### Process States

Non-preemptive priority system with states: `wait`, `ready`, `running`, `terminate`.

### CPU Architecture

Retrieve CPU information using:

- `cat /proc/cpuinfo`: Displays CPU details.

### Block Storage

Access block storage information with:

- `lsblk`: Lists information about block devices.
- `/proc/partitions`: Contains partition information.

## Kernel and Process Management

### General-Purpose Operating System

Linux kernel architecture and process management include:

- **Round-Robin Scheduling**: Time slicing among processes.
- **Monolithic Kernel**: If `main()` crashes, the whole system crashes.
- **Virtual Memory and Paging**: Managed by the MMU, affecting determinism.

### Real-Time Systems

Linux can act as an RTOS but is not certified. QNX is an example of a certified RTOS with a microkernel architecture.

## Process and Thread Management

### Process Creation

A process can spawn multiple threads running concurrently on different CPU cores:

```c
int main() {
    Create_thread1(); // fork
    Create_thread2(); // fork
}

void thread1() {
    // Runs on its own core and ALU
}

void thread2() {
    // Runs on its own core and ALU
}
```

# System monitor
### Commands to Manage Processes

- `ps -aux`: Lists all running processes.
- `ps -at`: Lists all processes created by any terminal.
- `ps -at`: Lists all processes created by current terminal.
- `strings /usr/bin/ps | grep proc`: Shows that `ps` parses `/proc` for information.
- `top`: real time system monitor.
- `pstree`: tree process.

### Signals
- `kill -9`: force Kill.
- `pkill PROCESS_NAME`: force kill.
- `cntrl + c`: force kill
- `cntrl + z`: halt process.
- `./script &`: run in background
- `job`: show all background process.
- `fg`: process running in background to run in forground.
- `bg`: process running in forground to run in background.




