# Day3 questions.

## Section 1:

### `.bashrc` script get run once you open the terminal run over bash, and handle the design of bash terminal
* Design the terminal shape.
* Set variable during open terminal and alias.
* Run Applications.

`Path: ~/.bashrc`  

* `HELLO` exported so it will be available in all child processes of the shell.
* `LOCAL` is added to the .bashrc file without the export , it a local variable within the current shell session.

* The .bashrc file will now contain the new variable definitions.
* `HELLO`' will be an environment variable available to child processes and will have the value of the HOSTNAME environment variable.
* LOCAL will be a local variable not exported and will have the value returned by the whoami command, which is the current username.

<p align="center">
	<img src="https://github.com/Mina267/Embedded-Linux/assets/71601701/62f24ba6-e161-4e73-aeaf-e49054146c84" width=60% height=60% />
</p>

```bash
#!/bin/bash

if [ -f "$HOME/.bashrc" ]; then
  echo "export HELLO=\$HOSTNAME" >> "$HOME/.bashrc"
  echo "LOCAL=\$(whoami)" >> "$HOME/.bashrc"
fi

gnome-terminal
```
---
# Section 2:
## 1. List the user commands and redirect the output to `/tmp/commands.list`  

### Command `compgen -c`:
* The `compgen -c` command lists all commands that you can run in your current shell environment. It outputs a list of all executable names found in directories listed in your PATH environment variable.

### Redirect Output to a File:

* Use the > operator to redirect the output of the command to a file



<p align="center">
	<img src="https://github.com/Mina267/Embedded-Linux/assets/71601701/2701fcad-aca9-4248-8b43-a014a8aa67b9" width=60% height=60% />
</p>

<p align="center">
	<img src="https://github.com/Mina267/Embedded-Linux/assets/71601701/6fb4c3de-13d2-47d3-8428-00ddbdfcdf9c" width=60% height=60% />
</p>

---
### 2. Edit in your profile to display date at login and change your prompt permanently. 

### `.profile` 
* Each user has this file.
* Run once you login to your user.
* Run anything program etc. in login.

`Path: ~/.profile`

<p align="center">
	<img src="https://github.com/Mina267/Embedded-Linux/assets/71601701/82ee3cf8-c3ef-4f91-824d-f1e2f859dc12" width=60% height=60% />
</p>

<p align="center">
	<img src="https://github.com/Mina267/Embedded-Linux/assets/71601701/9f7040cf-0e73-4385-a378-2e65f38b3fb5" width=60% height=60% />
</p>

---
### 3. What is the command to count the word in a file or number of file in directory. 
## Count the number of words in a file
```bash
wc -w filename
```

## Count the number of files in a directory
```bash
ls -1 | wc -l
```

## a- Count the number of user commands 
```bash
history | wc -l
```

`history command`
* The history command in Unix-like operating systems displays the list of commands previously entered by the user in the terminal. Each command in the history list is usually prefixed with a number, which indicates the order in which the commands were entered.

`Pipe (|):`
* The pipe symbol (|) is used to pass the output of one command as the input to another command. In this case, the output of the history command is passed as input to the wc -l command.

`wc -l:`
* The wc (word count) command is used to count lines, words, and characters in a text. The -l option tells wc to count the number of lines.
When wc -l receives input, it counts the number of newline characters, effectively giving the number of lines.

<p align="center">
	<img src="https://github.com/Mina267/Embedded-Linux/assets/71601701/09be9d12-be93-4815-b6ed-57f2e254b49e" width=60% height=60% />
</p>


---
## 4. What happens if you execute:
`a- cat filename1 | cat filename2`

The first cat filename1 command reads and outputs the contents of filename1.
The pipe (|) will passes the output as input to the second cat filename2 command.

This command doesn't achieve anything. The cat command doesn't expect input when a filename argument is given, so the second cat command will  ignore the piped input and display the contents of filename2.


<p align="center">
	<img src="https://github.com/Mina267/Embedded-Linux/assets/71601701/327ef993-66e3-4f0a-9594-c0a460723fc3" width=60% height=60% />
</p>

`b. ls | rm`

* The ls command lists the files and directories in the current directory.
The pipe (|) then passes this list as input to the rm command.
* rm doesn't expect a list of filenames as input from a pipe. 
* In many shells, rm will return an error indicating that it is missing operands or arguments.

<p align="center">
	<img src="https://github.com/Mina267/Embedded-Linux/assets/71601701/5b3c7d96-e3b3-4eae-816d-59e39f1bc086" width=60% height=60% />
</p>


`c. ls /etc/passwd | wc -l`
This command combines ls and wc -l:

* ls /etc/passwd lists the /etc/passwd file 
* wc -l counts the number of lines in the input it receives.

---
## 5. Write a command to search for all files on the system that, its name is “.profile”.
<p align="center">
	<img src="https://github.com/Mina267/Embedded-Linux/assets/71601701/ab2ea4f3-9b59-43f7-8a2c-25a536f8fb8a" width=60% height=60% />
</p>
---

## 6. List the inode numbers of /, /etc, /etc/hosts.


<p align="center">
	<img src="https://github.com/Mina267/Embedded-Linux/assets/71601701/744040c1-6a61-4cc7-8d6d-e55de646838b" width=60% height=60% />
</p>


## 7. Create a symbolic link of /etc/passwd in /boot.

```bash
sudo ln -s /etc/passwd /boot/passwd
```

## 8. Create a hard link of /etc/passwd in /boot. Could you? Why?


<p align="center">
	<img src="https://github.com/Mina267/Embedded-Linux/assets/71601701/53e8aca4-f824-4373-a824-1ca06842a86a" width=60% height=60% />
</p>

*  Hard Links Within Same File System: Hard links can only be created for files within the same file system.  /etc and /boot often reside on separate file systems. The /etc directory typically resides on the root file system, while /boot might be on its own partition optimized for booting.

*  Hard Links for Files Only: Hard links can only be created for files, not directories. While  /etc/passwd is a file, attempting to create a hard link of a directory like  /etc itself wouldn't be possible.

### 9. Echo \ it will jump to the next line, and will print `>`  Notice the prompt ”>” what is that? and how can you change it from `>` to `:`. 

* The `>` prompt in Bash appears when a command is not completed and the shell expects more input.
* when a command is not fully closed or if there is an escape character (like `\`) at the end of a line, indicating continuation.
* `\` at the end of the first line causes the shell to display the > prompt, waiting for the continuation of the command.

#### *Changing the Continuation Prompt*
* The continuation prompt can be customized using the PS2 variable. By default, PS2 is set to `>`, we can change it. 

<p align="center">
	<img src="https://github.com/Mina267/Embedded-Linux/assets/71601701/c7a474df-5606-4fd5-a4e1-01fb9499bc73" width=60% height=60% />
</p>

<p align="center">
	<img src="https://github.com/Mina267/Embedded-Linux/assets/71601701/34f2c5ab-a915-43fc-9b8d-f1021a8c7372" width=60% height=60% />
</p>
