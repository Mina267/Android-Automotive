# Question 1

## 1. List three Linux Distributions
	1- fedora
	2- Red Hat
	3- Solus 
	4- ZORIN 
	5- Linux Mint
	6- debian 
	7- archlinux 	
	8- BlackArch 
	9- Kubuntu 
	10- CentOS 
	11- Manjaro
## 2. From the slides what is the man command used for?
### man command
 System-wide documentation system that provides short reference manuals (pages) for individual
 commands,API functions, concepts, configuration file syntax, file formats and is organized in sections
 (1 for user commands, 2 for system calls...). That's the traditional Unix documentation system    

## 3. What is the difference between rm and rmdir using man command?
### I- rm
```shell
    rm removes each specified file. By default, it does not remove directories.
    If the -I or - -interactive=once option is given, and there are more
    than three files or the -r, -R, or -- recursive are given, then rm
    prompts the user for whether to proceed with the entire operation.
    If the response is not affirmative, the entire command is aborted.
```
### II- rmdir
```shell
    Remove the DIRECTORY(ies), if they are empty.
    -- ignore-fail-on-non-empty
        ignore each failure that is solely because a directory
        is non-empty
    -P, -- parents
        remove DIRECTORY and its ancestors; e.g., 'rmdir -p a/b/c' is similar to 'rmdir a/b/c a/b a'
    -v, -- verbose
        output a diagnostic for every directory processed
    -- help display this help and exit
    -- version
        output version information and exit
```
## 4. Create the following hierarchy under your home directory:
<p align="center">
	<img src="https://github.com/Mina267/GP_4M_SV2_Intake3_FOTA_18/assets/71601701/88e5b617-e1b6-4544-89a7-2597d186d621" width=40% height=40% />
</p>

### a. Remove dir11 with rmdir in one-step. What did you notice? And how did you  overcome that? 
<p align="center">
	<img src="https://github.com/Mina267/GP_4M_SV2_Intake3_FOTA_18/assets/71601701/7a8a5f4d-ec9c-4da0-a2f5-23443c0de6b0" width=40% height=40% />
</p>

#### What Did You Notice?
	The rmdir command will fail with an error message because dir11 is not empty. The rmdir command only removes empty directories.
	To remove a directory and all its contents, you can use the rm -r command instead of rmdir.
<p align="center">
	<img src="https://github.com/Mina267/GP_4M_SV2_Intake3_FOTA_18/assets/71601701/0c3e9f39-b4c7-4c2d-b15e-d0f3aabae252" width=40% height=40% />
</p>

### b. Then remove OldFiles using rmdir –p command. State what happened to the  hierarchy (Note: you are in your home directory). 
<p align="center">
	<img src="https://github.com/Mina267/GP_4M_SV2_Intake3_FOTA_18/assets/71601701/662bdf03-c24a-4cdf-8d8c-0f9d03d7ec46" width=40% height=40% />
</p>

#### What Happened to the Hierarchy?
	The rmdir -p command is used to remove a directory and its parent directories if they become empty. 
 	rmdir -p can only remove empty directories. Since OldFiles is a file, not an empty directory, the rmdir -p command will fail.
	To remove the file OldFiles and then the empty Documents directory, you would need to first delete the file and then remove the directory.



### c. The output of the command pwd was /home/user. Write the absolute and relative path for the file mycv.
#### relative path:
```shell
docs/mycv
```
#### absolute path. 
```shell
/home/user/docs/mycv
```

## 5. Copy the /etc/passwd file to your home directory making its name is mypasswd
    
```shell
cp /etc/passwd ~/mypasswd
```
<p align="center">
	<img src="https://github.com/Mina267/GP_4M_SV2_Intake3_FOTA_18/assets/71601701/52019423-d954-4780-8a81-9948b1317764" width=40% height=40% />
</p>

## 6. Rename this new file to be oldpasswd 
```shell
mv ~/mypasswd ~/oldpasswd
```
<p align="center">
	<img src="https://github.com/Mina267/GP_4M_SV2_Intake3_FOTA_18/assets/71601701/66fe9e76-1588-46d7-9050-22f5ef575466" width=40% height=40% />
</p>

## 7. You are in /usr/bin, list four ways to go to your home directory 
```shell
cd ~
cd /home/user
cd $HOME
cd
```


## 8. List Linux commands in /usr/bin that start with letter w
```shell	
ls /usr/bin/w*
```
<p align="center">
	<img src="https://github.com/Mina267/GP_4M_SV2_Intake3_FOTA_18/assets/71601701/0da028e9-54eb-40cf-a1e7-115b460ca2bb" width=40% height=40% />
</p>

## 9. What command type are used for? (from the slide)
 ### Command `type`
#### • Display information about command typ

## 10. Show 2 types of command file in /usr/bin that start with letter c
```shell
ls /usr/bin/c*
ls /usr/bin/c* | head -n 2
```
<p align="center">
	<img src="https://github.com/Mina267/GP_4M_SV2_Intake3_FOTA_18/assets/71601701/df05d3a5-bb2e-4e4c-ae9f-22a2c53ecff3" width=40% height=40% />
</p>


## 11. Using man command find the command to read file. (Note: man take option)
```shell
man -k read | grep file
```
<p align="center">
	<img src="https://github.com/Mina267/GP_4M_SV2_Intake3_FOTA_18/assets/71601701/24452a7f-a670-4f82-b827-b8359f3c36bb" width=40% height=40% />
</p>

## 12. What is the usage of apropos command?

The apropos command in Unix-like operating systems is used to search the manual page names and descriptions for a keyword or regular expression. It helps users find commands and topics related to a specific keyword by looking through the man page descriptions.
### Usage
 #### The basic syntax for apropos is:
```shell
apropos [keyword]
``` 
#### Practical Use
The apropos command is particularly useful when you remember part of a command's functionality but not the exact command name. It helps you quickly locate relevant man pages without needing to know the exact names.

# Last Exercice

```bash
git clone https://github.com/Mina267/Embedded-Linux.git

cd Embedded-Linux

git checkout -b Task1_adminLinux main

mkdir AdminLinx_Task1

echo '#!/bin/bash' > AdminLinux_Task1/script.sh

git add AdminLinux_Task1/script.sh

git commit -m "Add empty script to AdminLinux_Task1"

git checkout main

git merge Task1_adminLinux

git push origin main
```

<p align="center">
	<img src="https://github.com/Mina267/GP_4M_SV2_Intake3_FOTA_18/assets/71601701/b62693c9-504c-47f8-a9fb-6e4f7cda4859" width=40% height=40% />
</p>
