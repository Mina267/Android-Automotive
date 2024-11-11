
# GNU/Linux Architecture Overview

This repository provides an overview of the architecture of the GNU/Linux operating system, focusing on the interaction between user applications, the GNU C Library (glibc), the System Call Interface, the kernel, and the hardware platform.

## Components

### User Space
- **User Applications**: These are programs written by users (or developers) that perform specific tasks, such as a text editor, a web browser, or a game. User applications typically need to perform various tasks, such as reading from a file, sending data over the network, or creating new processes.
- **GNU C Library (glibc)**: This is a standard library that provides a wide range of functionalities, such as input/output operations, memory management, and string manipulation, to user applications. glibc acts as an intermediary between user applications and the kernel by providing a convenient and standardized interface to make system calls. When a user application wants to perform an action that requires kernel intervention (e.g., reading a file), it uses functions provided by glibc.

### Kernel Space
- **System Call Interface**: This is the gateway through which user applications (via glibc) request services from the kernel. The kernel provides low-level operations, such as file operations, process control, and network communication. System calls are used to switch from user space to kernel space, where the actual operation is performed.
- **Kernel**: The core component of the operating system responsible for managing system resources, such as CPU, memory, and I/O devices. It handles process scheduling, memory management, hardware abstraction, and system security.
- **Architecture-Dependent Kernel Code**: This includes parts of the kernel that are specific to the hardware architecture (e.g., x86, ARM).

### Hardware Platform
- The physical components of a computer system, including the CPU, memory, storage devices, and I/O peripherals.

## Interaction Process

1. **User Applications**: When a user application wants to perform an operation, such as reading a file, it calls a function from glibc. For example, the application might call `fopen()` to open a file.
2. **GNU C Library (glibc)**: glibc provides the `fopen()` function, which simplifies the process for the application developer. Internally, `fopen()` might call another glibc function that prepares a system call. glibc converts this function call into a system call that the kernel understands. For example, `fopen()` might eventually result in the `open()` system call being invoked.
3. **System Call Interface**: The system call interface is part of the kernel that handles these requests. When glibc makes a system call, it uses a special CPU instruction to transition from user space to kernel space. The kernel receives the system call, performs the requested operation (e.g., opening the file), and returns the result to glibc.
4. **Kernel**: The kernel executes the requested operation (e.g., opening a file, allocating memory, or sending data over the network). Once the operation is completed, the kernel returns the result to the system call interface, which then transitions back to user space.
5. **Returning to User Application**: glibc receives the result from the kernel and returns it to the user application. The application then continues its execution with the result (e.g., a file descriptor from the `fopen()` call).


## Interaction Process summary

1. **User Applications**: Call functions from glibc to perform operations, such as reading a file.
2. **GNU C Library (glibc)**: Converts function calls into system calls understood by the kernel.
3. **System Call Interface**: Handles the transition from user space to kernel space and forwards the request to the kernel.
4. **Kernel**: Executes the requested operation and returns the result to glibc.
5. **glibc**: Returns the result to the user application.

<p align="center">
	<img src="https://github.com/user-attachments/assets/86bce8bf-c1c0-47c6-ab72-ed37b2beb2bf" width=75% height=75% />
</p>

## Why User Space is "Higher" Than glibc

- The hierarchy shown in the diagram doesn't imply that user applications are "higher" than glibc in terms of privilege. Instead, it represents the flow of execution and the dependency chain.
- User applications depend on glibc to provide a convenient interface for making system calls, and glibc, in turn, depends on the kernel to perform the actual hardware-related operations.

## Role of GNU C Library (glibc)

- **Abstraction**: glibc abstracts the complexity of making system calls directly. It provides user-friendly functions that developers can use without worrying about the underlying system call mechanism.
- **Standardization**: glibc ensures that applications can use a consistent set of functions across different Unix-like systems, making them more portable.
- **Convenience**: glibc includes a wide range of functions for common programming tasks, reducing the need for developers to write low-level code.

## Diagram

The following diagram represents the architecture of the GNU/Linux operating system:

<p align="center">
	<img src="https://github.com/user-attachments/assets/36858d0f-2773-4ebe-b210-1d2fad8a2397" width=75% height=75% />
</p>


## Summary

- **User Applications** call functions provided by **glibc** to perform various tasks.
- **glibc** translates these function calls into system calls and communicates with the **System Call Interface**.
- The **System Call Interface** allows the **Kernel** to execute these system calls.
- The result of the operation is passed back through **glibc** to the **User Applications**.

This layered architecture ensures modularity, ease of development, and system stability by isolating user applications from direct hardware manipulation.


<p align="center">
	<img src="https://github.com/user-attachments/assets/6c8c6014-aa87-45d4-8057-5254a5c3f342" width=75% height=75% />
</p>
