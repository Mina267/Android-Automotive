# Question 1

<p align="center">
	<img src="https://github.com/Mina267/Embedded-Linux/assets/71601701/3e320a3b-4b08-4e57-8cc9-7ae7de8c1a14" width=60% height=60% />
</p>

<p align="center">
	<img src="https://github.com/Mina267/Embedded-Linux/assets/71601701/a182ed40-327a-4bb2-887b-c202072f99d4" width=60% height=60% />
</p>

# Question 2

## System PATH Environment Variable:



#### When you move the binary to /usr/local/bin, it becomes part of the system's PATH. The PATH environment variable contains a list of directories that the shell searches through to find executables when a command is issued.

#### When you type a command in the terminal, the shell looks for the executable in the directories listed in the PATH environment variable.

#### local/bin Save collect of binary for specific user can be execute from any directory
<p align="center">
	<img src="https://github.com/Mina267/Embedded-Linux/assets/71601701/39b57284-c254-4b48-b2b7-8d4a1d786db0" width=60% height=60% />
</p>
 
#### By moving the binary to /usr/local/bin, it is placed in one of the directories that the shell searches for executables by default.


### Sudo Permissions:
The sudo mv command ensures that you have the necessary permissions to move the binary to a system directory like /usr/local/bin, which typically requires root access.


### Evidence
Location of the BinarySearch file:

<p align="center">
	<img src="https://github.com/Mina267/Embedded-Linux/assets/71601701/fe7d08b5-6809-4614-8f95-3b13080bebdc" width=60% height=60% />
</p>

<p align="center">
	<img src="https://github.com/Mina267/Embedded-Linux/assets/71601701/32e0c4ea-84d8-47e6-aa24-20a0a945f79d" width=60% height=60% />
</p>

#### here we can execute BinarySearch from various directories.


By moving your binary to /usr/local/bin with sudo permissions, you make it accessible from any working directory due to the inclusion of /usr/local/bin in the PATH environment variable. This enhances the usability and accessibility of your binary, allowing it to be executed without specifying its full path.






# Na2na2a

### 1. List the available shells in your system. 
<p align="center">
	<img src="https://github.com/Mina267/Embedded-Linux/assets/71601701/8a4f615d-0519-4530-ab4b-69f5ace78535" width=60% height=60% />
</p>

### 2. List the environment variables in your current shell. 
<p align="center">
	<img src="https://github.com/Mina267/Embedded-Linux/assets/71601701/b1154eb2-e6f0-47ab-b6f1-694cd35a0298" width=60% height=60% />
</p>

### 3. Display your current shell name. 
  <p align="center">
	<img src="https://github.com/Mina267/Embedded-Linux/assets/71601701/0d07f503-f7f1-4ed8-ab0b-12fb40045f37" width=60% height=60% />
</p>

### 4. Execute the following command :  echo \ then press enter   What is the purpose of    \   ?  
<p align="center">
	<img src="https://github.com/Mina267/Embedded-Linux/assets/71601701/1d2f3b14-1831-47b7-83c1-039688de3e06" width=60% height=60% />
</p>



tells the shell that the command continues on the next line. When you press enter after typing echo \, the shell waits for more input, allowing you to continue typing the command on the next line.

### 5. Create a Bash shell alias named PrintPath for the “echo $PATH” command 
<p align="center">
	<img src="https://github.com/Mina267/Embedded-Linux/assets/71601701/25eba349-17e7-45cf-9587-9e699b4b8bb0" width=60% height=60% />
</p>

<p align="center">
	<img src="https://github.com/Mina267/Embedded-Linux/assets/71601701/743ccc5d-7e55-4b98-9fec-08d5caeb2db1" width=60% height=60% />
</p>



# Available Shells in Unix-like Systems

## Shells Overview

### 1. Bash (Bourne Again Shell)
- **Path:** `/bin/bash`
- **Features:** Command history, tab completion, scripting capabilities.
- **Usage:** Default shell on many Linux distributions.

### 2. Sh (Bourne Shell)
- **Path:** `/bin/sh`
- **Features:** Basic shell, widely available, and used for scripting.
- **Usage:** Standard shell for Unix systems, and POSIX-compliant.

### 3. Zsh (Z Shell)
- **Path:** `/bin/zsh`
- **Features:** Advanced scripting, command completion, customization, and themes (e.g., Oh-My-Zsh).
- **Usage:** Popular among developers for its rich feature set.

### 4. Ksh (Korn Shell)
- **Path:** `/bin/ksh`
- **Features:** Combines features of C Shell and Bourne Shell, good for scripting.
- **Usage:** Used in some Unix systems, valued for scripting capabilities.

### 5. Csh (C Shell)
- **Path:** `/bin/csh`
- **Features:** C-like syntax, job control, history mechanism.
- **Usage:** Less common today, but historically used for its scripting features.

### 6. Tcsh (TENEX C Shell)
- **Path:** `/bin/tcsh`
- **Features:** Enhanced version of C Shell, with command-line editing and history.
- **Usage:** Sometimes preferred over Csh for its improvements.

## Checking Available Shells

To see which shells are available on your system, you can check the `/etc/shells` file:
```bash
cat /etc/shells
