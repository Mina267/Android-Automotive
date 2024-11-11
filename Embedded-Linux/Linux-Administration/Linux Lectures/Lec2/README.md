
# Linux System Guide

## Table of Contents
1. [Linux Filesystem](#1-linux-filesystem)
2. [Variables](#2-variables)
   - [Global Variables](#global-environment)
   - [Local Variables](#local)
3. [Types of Commands](#3-types-of-commands)
   - [External Commands](#1-external-commands)
   - [Internal Commands](#2-internal-commands)
   - [Alias Commands](#alias-commands)
4. [Wildcard](#4-wildcard)
5. [Environment](#environment)
   - [File .bashrc](#file-bashrc)
   - [File .profile](#file-profile)
6. [Reading Files](#read-files)
   - [cat](#1-cat)
   - [less or more](#2-less-or-more)
   - [gedit](#3-gedit)
   - [VS Code](#4-vs-code)
7. [Editing Files](#edit-files)
   - [vi or vim](#5-vi-or-vim)
   - [nano](#6-nano)
8. [Head and Tail](#7-head-tail)
9. [Searching Files](#search-files)
   - [locate](#a-locate)
   - [find](#b-find)
   - [whereis](#c-whereis)
10. [Pattern Searching in Files](#pattern-searching-in-files)
   - [Using grep](#using-grep)
11. [Redirection and File Descriptors](#redirection-and-file-descriptors)
   - [Basic Redirection](#basic-redirection)
   - [File Descriptors Explained](#file-descriptors-explained)
12. [C Application Examples](#c-application-examples)
   - [Example 1](#example-1)
   - [Example 2](#example-2)
   - [Example 3](#example-3)
   - [Example 4](#example-4)
13. [Changing Output Destination](#changing-output-destination)
   - [Redirecting Output](#redirecting-output)
   - [Redirecting Errors](#redirecting-errors)
14. [Process and File Descriptor Management](#process-and-file-descriptor-management)
15. [Piping |](#Piping-|)  
16. [Links](#Links)


---

## 1. Linux Filesystem

The Linux filesystem is organized in a hierarchical structure, starting from the root directory (`/`). Each directory serves a specific purpose:

- **/etc:** Configuration files for the system.
- **/dev:** Device nodes.
- **/sys:** System files, including device registers.
- **/bin:** Essential command binaries for all users.
- **/sbin:** System binaries for administration.
- **/boot:** Files for booting (kernel, bootloader).
- **/home:** Home directories for all users.
- **/usr:** User binaries and headers.
- **/media:** Mount points for removable media like USB drives.
- **/mnt:** Mount points for temporarily mounted filesystems.


## 2. Variables

### Global (Environment)
Global variables are accessible to any child processes spawned by the parent process.

- Command to set a global variable:
  ```sh
  export GLOBAL=hi
  ```
- Commands to see all global variables:
  ```sh
  printenv
  set
  ```

### Display All Shell Variables and Functions
To display all shell variables and functions:
 ```sh
  set
  ```
### Setting Shell Options
You can use the -o option with set to enable or disable specific shell options. For example:

```sh
set -o option_name   # Enable the option
set +o option_name   # Disable the option
```
### Local
Local variables are only accessible within the shell session where they are defined.

- Command to set a local variable:
  ```sh
  LOCAL=hi
  ```

### Command to Print Variables
- `echo` command prints variables to the terminal:
  ```sh
  echo $VARIABLE_NAME
  ```

## 3. Types of Commands

### 1. External Commands
- Executable programs stored in `/bin`, `/usr/bin`, or other directories listed in the `$PATH`.

### 2. Internal Commands
- Built-in commands in the shell, such as `cd`, `echo`.

### Alias Commands
Aliases are shortcuts for longer commands.

- Create a shortcut for a command:
  ```sh
  alias ll='ls -la'
  ```
- Remove an alias:
  ```sh
  unalias ll
  ```

## 4. Wildcard
Wildcards are used to match patterns in file and directory names.

- `?`: Matches any single character.
- `*`: Matches any number of characters.
- `[]`: Matches any one of the enclosed characters.
- `{}`: Matches any of the patterns within the braces, e.g., `{*.pdf, *.c}`.

## Environment

### File .bashrc
The `.bashrc` file runs automatically when a new terminal session is opened. It is used to configure the terminal, set environment variables, and define aliases.

- Path: `~/.bashrc`
- Hidden files (like `.bashrc`) can be viewed using:
  ```sh
  ls -a
  ```

#### Key Configurations:
- **PS1**: Defines the terminal prompt appearance.
- To edit `.bashrc`, use a text editor:
  ```sh
  gedit ~/.bashrc
  ```

### File .profile
The `.profile` file runs once at login and is used to configure the user environment and run programs/scripts at login.

- Path: `~/.profile`

## Read Files

### 1. cat
The `cat` command prints the content of a file to the terminal.

- Example:
  ```sh
  cat filename
  ```

### 2. less or more
For viewing large files, `less` and `more` provide pagination.

- **less**: Allows scrolling through large files.
  - Search: `/search_term`
  - Next occurrence: `n`
  - Previous occurrence: `N`
  - Quit: `q`
- **more**: Similar to `less`, but only allows forward movement.

### 3. gedit
`gedit` is a GUI-based text editor.

- Example:
  ```sh
  gedit filename
  ```

### 4. VS Code
Visual Studio Code (VS Code) is a popular GUI-based code editor.

## Edit Files

### 5. vi or vim
`vi` or `vim` is a powerful text editor available in the terminal.

- Install `vim`:
  ```sh
  sudo apt install vim
  ```

#### Modes in `vim`:
- **Read mode**: Default mode.
  - Search: `/search_term`
  - Next occurrence: `n`
  - Previous occurrence: `N`
- **Insert mode**: Enter by pressing `i`.
  - Exit to read mode: `Esc`
- **Command mode**: Enter by pressing `:`.
  - Quit: `:q`
  - Force quit: `:q!`
  - Save and quit: `:wq`

#### Common Shortcuts:
- Delete line: `dd`
- Copy line: `yy`
- Paste: `p`
- Visual select: `v`

### 6. nano
`nano` is a simple terminal text editor.

- Save and exit:
  - `Ctrl + X`, then `Y`, and `Enter`

## 7. Head-Tail
The `head` and `tail` commands are used to print the beginning or end of a file, respectively.

- **head**: Prints the first 10 lines of a file.
  ```sh
  head filename
  ```
- **tail**: Prints the last 10 lines of a file.
  ```sh
  tail filename
  ```

## Search Files

### a. locate
The `locate` command searches a database of all files on the system.

- Install `locate`:
  ```sh
  sudo apt install locate
  ```
- Example:
  ```sh
  locate filename
  ```

### b. find
The `find` command searches for files in a directory hierarchy.

- Examples:
  ```sh
  find [PATH] -name filename
  find . -name main.c   # Case sensitive
  find . -iname main.c  # Case insensitive
  ```

### c. whereis
The `whereis` command locates the binary, source, and manual page files for a command.

- Example:
  ```sh
  whereis command
  ```

---

**Note:** If `.bashrc` or `.profile` is not found in the home directory, system-wide versions can be used as backups located in `/etc/`.


## Pattern Searching in Files

### Using `grep`
The `grep` command is used to search for a specific pattern within files.

- **Basic Syntax**:
  ```sh
  grep [pattern] [file]
  ```
  - `pattern`: The string or regex to search for.
  - `file`: The file to search within.

- **Recursive Search**:
  ```sh
  grep -R [pattern] [directory]
  ```
  - `-R`: Search recursively through the directory.

- **Common Options**:
  - `-n`: Print line number.
  - `-i`: Ignore case sensitivity.

Example:
```sh
grep -n "main" main.c
```

---

## Redirection and File Descriptors

### Basic Redirection
Redirection allows you to control where the output of a command goes, or where the input comes from.

- **Output Redirection**:
  ```sh
  command > file
  ```
  Redirects the output of the command to the specified file.

- **Append Output**:
  ```sh
  command >> file
  ```
  Appends the output to the specified file.

- **Error Redirection**:
  ```sh
  command 2> file
  ```
  Redirects the error output of the command to the specified file.

Example:
```sh
echo "Hello, World!" > output.txt
```

### File Descriptors Explained
File descriptors are integer handles used to identify an open file for a process. The default file descriptors are:
- `0`: Standard Input (stdin)
- `1`: Standard Output (stdout)
- `2`: Standard Error (stderr)

Example:
```sh
cat main.c > output.txt
```
This redirects the standard output (fd 1) of `cat` to `output.txt`.

---

## C Application Examples

### Example 1

```c
#include <stdio.h>

int main(void) {
    int var = 0;
    /* Print a message to the terminal */
    printf("hello\n");
    /* Take input from the terminal */
    scanf("%d", &var);
    /* Print the input value */
    printf("%d \n", var);
    return 0;
}
```

#### Building and Running
To compile and run the program:
```sh
gcc main.c -o myexe
./myexe
```

### Example 2

```c
#include <stdio.h>

int main(void) {
    int var = 0;
    /* Print an error message to stderr */
    fprintf(stderr, "hello\n");
    /* Take input from the terminal */
    scanf("%d", &var);
    /* Print the input value */
    printf("%d \n", var);
    return 0;
}
```

#### Redirecting Errors
To redirect errors to a file:
```sh
./myexe 2> output.txt
```

### Example 3

```c
#include <stdio.h>

int main(void) {
    char var = 0;
    /* Print an error message to stderr */
    fprintf(stderr, "hello from error\n");
    /* Print a message to the terminal */
    printf("hello from here\n");
    /* Print a message to stdout */
    fprintf(stdout, "hello from out\n");
    /* Take input from the terminal */
    scanf("%c", &var);
    /* Print the input value */
    printf("%c \n", var);
    return 0;
}
```

#### Running with Redirection
To redirect standard input, output, and error:
```sh
./myexe 2> error.txt > output.txt < input.txt
```

### Example 4

```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    char var = 0;
    int fd = 0;
    /* Open a file and get its file descriptor */
    fd = open("var.txt", O_RDWR);
    /* Print the file descriptor */
    printf("My file descriptor:%d \n", fd);
    /* Write to the file descriptor */
    write(fd, "hiiiii", 7);
    /* Print an error message to stderr */
    fprintf(stderr, "hello from error\n");
    /* Print a message to the terminal */
    printf("hello from here\n");
    /* Print a message to stdout */
    fprintf(stdout, "hello from out\n");
    /* Take input from the terminal */
    scanf("%c", &var);
    /* Print the input value */
    printf("%c \n", var);
    return 0;
}
```

#### Running with Redirection
To redirect to a specific file descriptor:
```sh
./myexe 3> output.txt
```

---

## Changing Output Destination

### Redirecting Output
To redirect the output of a program to a file instead of the terminal:
```sh
./myexe > output.txt
```

### Redirecting Errors
To redirect errors to a file:
```sh
./myexe 2> error.txt
```

---

## Process and File Descriptor Management

### Managing Processes
To view and manage processes, you can use the following commands:

- **List All Processes**:
  ```sh
  ps -aux
  ```
- **List Terminal Processes**:
  ```sh
  ps -at
  ```

- **Access Process Details**:
  ```sh
  cd /proc/[PID]
  ls -lh fd
  ```
  This will show file descriptors `0`, `1`, and `2` for the process.

### Changing Output File Descriptor
To change the output file descriptor from terminal to a file:
```sh
./myexe > output.txt
```
Then, inspect the file descriptors:
```sh
ls -lh /proc/[PID]/fd
```
File descriptor `1` will point to `output.txt` instead of the terminal.

---

# Piping |

IPC (Inter-Process Communication)

Each process has its own heap and stack. Each process is an application that can share resources with other processes. Piping allows the output of one process to be used as the input for another process.

Example:
```sh
cat main.c | grep [pattern]
find . --iname | grep ^/
```

# Links

## 1. Soft Link
A soft link (or symbolic link) acts as a shortcut to a file.

1. Run an application from another location.
2. Edit a file from another location.

When you create a file (e.g., `main.c`), it has a location in memory (inode). A soft link can access this file from another location without making a copy.

Command:
```sh
ln -s main.c mySoftLink
```
`mySoftLink` points to the location of `main.c`. The soft link has a different inode and is typically 8 bytes in size.

## 2. Hard Link
A hard link creates an alias to a file. Both the hard link and the original file share the same inode and location.

Command:
```sh
ln main.c myHardLink
```
Both `myHardLink` and `main.c` share the same inode and are essentially the same file.

**Differences Between Hard and Soft Links**:
- Soft links can work with directories, while hard links cannot.
- Hard links can only work with files.

