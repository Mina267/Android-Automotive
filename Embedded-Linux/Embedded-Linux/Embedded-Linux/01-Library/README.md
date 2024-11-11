# Table of Contents

1. [Sysroot, Library, and Header Files](#sysroot-library-and-header-files)
2. [Other Tools in the Toolchain](#other-tools-in-the-toolchain)
3. [Components of the C Library](#components-of-the-c-library)
4. [Linking with Libraries](#linking-with-libraries)
   - [Static Libraries](#static-libraries)
   - [Shared Libraries](#shared-libraries)
5. [C Library Creation Example](#C-Library-Creation-Example)


## Sysroot, Library, and Header Files


Subdirectories in sysroot include:

- `lib`: Contains shared objects for the C library, dynamic linker/loader (`ld-linux`), static library archives, and other libraries.
- `usr/lib`: Contains static library archive files.
- `usr/include`: Contains headers for all the libraries.
- `usr/bin`: Contains utility programs that run on the target, such as the `ldd` command.
- `use/share`: Used for localization and internationalization.
- `sbin`: Provides the `ldconfig` utility for optimizing library loading paths.

Some of these are needed on the development host for compiling programs, while others (e.g., shared libraries and `ld-linux`) are needed on the target at runtime.

## Other Tools in the Toolchain

Here are various other components of a GNU toolchain along with brief descriptions:

| Command  | Description |
|----------|-------------|
| `addr2line` | Converts program addresses into filenames and numbers by reading debug symbol tables. |
| `ar`       | The archive utility for creating static libraries. |
| `as`       | The GNU assembler. |
| `c++filt`  | Demangles C++ and Java symbols. |
| `cpp`      | The C preprocessor. |
| `elfedit`  | Updates the ELF header of ELF files. |
| `g++`      | The GNU C++ frontend. |
| `gcc`      | The GNU C frontend. |
| `gcov`     | A code coverage tool. |
| `gdb`      | The GNU debugger. |
| `gprof`    | A program profiling tool. |
| `ld`       | The GNU linker. |
| `nm`       | Lists symbols from object files. |
| `objcopy`  | Copies and translates object files. |
| `objdump`  | Displays information from object files. |
| `ranlib`   | Creates or modifies an index in a static library. |
| `readelf`  | Displays information about ELF object format files. |
| `size`     | Lists section sizes and the total size. |
| `strings`  | Displays strings of printable characters in files. |
| `strip`    | Strips an object file of debug symbol tables. |

## Components of the C Library

The C library consists of four main parts implementing the POSIX API:

1. `libc`: The main C library with POSIX functions like `printf`, `open`, `close`, `read`, `write`, etc.
2. `libm`: Contains math functions such as `cos`, `exp`, `log`.
3. `libpthread`: Contains POSIX thread functions with names starting with `pthread_`.
4. `librt`: Contains real-time extensions to POSIX, including shared memory and asynchronous I/O.

## Linking with Libraries

Applications can link with libraries either statically or dynamically.

### Static Libraries

Static linking pulls all library functions and their dependencies from the library archive and binds them into the executable.

Example:

```sh
$ arm-cortex_a8-linux-gnueabihf-gcc -static helloworld.c -o helloworld-static
```

### Shared Libraries

Shared libraries are linked at runtime, allowing for more efficient use of storage and system memory. 

Example:

```sh
$ arm-cortex_a8-linux-gnueabihf-gcc helloworld.c -ltest -L../libs -I../libs -o helloworld
```

To create a shared library:

```sh
$ arm-cortex_a8-linux-gnueabihf-gcc -fPIC -c test1.c
$ arm-cortex_a8-linux-gnueabihf-gcc -fPIC -c test2.c
$ arm-cortex_a8-linux-gnueabihf-gcc -shared -o libtest.so test1.o test2.o
```



---
# C Library Creation Example

This project demonstrates the creation and use of static and dynamic libraries in C, along with automating the build process using a Makefile.

## Directory Structure

```
project/
├── app/
│   └── main.c
├── includes/
│   └── .h (files)
├── lib/
│   └── libmylib.so
│   └── libmylib.a
├── obj/
│   └── .o (files static)
├── objDynamic/
│   └── .o (files Dynamic)
├── src/
│   └── mylib.c
└── Makefile
```

<p align="center">
	<img src="https://github.com/user-attachments/assets/b26cf0b0-dc30-454d-96d0-3cce526220ae" width=100% height=100% />
</p>

## Static Library

1. **Compile Source Files to Object Files**

    ```sh
    gcc -c -Wall ./src/*.c -I ./includes/ && mv *.o ./obj/
    ```
    - `-c`: Compile source files without linking.
    - `-Wall`: Enable all compiler warnings.
    - `./src/*.c`: Compile all `.c` files in the `src` directory.
    - `-I ./includes/`: Specify the directory to search for header files.
    - `mv *.o ./obj/`: Move all generated object files to the `obj` directory.

2. **Create Static Library**

    ```sh
    ar -rcs libmylib.a ./obj/*.o && mv libmylib.a ./lib/
    ```
    - `ar -rcs libmylib.a ./obj/*.o`: Create an archive (static library) named `libmylib.a` from the object files in the `obj` directory.
    - `mv libmylib.a ./lib/`: Move the archive to the `lib` directory.

3. **Link Static Library with Main Program**

    ```sh
    gcc -static ./app/main.c -o Run -I ./includes/ -L./lib/ -lmylib
    ```
    - `-static`: Link the executable statically.
    - `./app/main.c`: The main program source file.
    - `-o Run`: Output executable named `Run`.
    - `-I ./includes/`: Include directory for header files.
    - `-L ./lib/`: Directory containing the library.
    - `-lmylib`: Link with the static library `libmylib.a`.

4. **Run the Executable**

    ```sh
    ./Run
    ```

## Dynamic Library

1. **Compile Source Files to Position-Independent Code (PIC) Object Files**

    ```sh
    gcc -c -fPIC -Wall ./src/*.c -I ./includes/ && mv *.o ./objDynamic/
    ```
    - `-fPIC`: Generate position-independent code.
    - `mv *.o ./objDynamic/`: Move all generated object files to the `objDynamic` directory.

2. **Create Shared Library**

    ```sh
    gcc -shared -o ./lib/libmylib.so ./objDynamic/*.o
    ```
    - `-shared`: Create a shared library.
    - `-o ./lib/libmylib.so`: Output shared library named `libmylib.so` in the `lib` directory.

3. **Show Symbol Table**

    ```sh
    objdump -T ./lib/libmylib.so
    ```
    - Display the symbol table of the shared library.

4. **Link Dynamic Library with Main Program**

    ```sh
    gcc ./app/main.c -o dynamicApp -I ./includes/ -L ./lib/ -lmylib -Wl,-rpath=./lib/
    ```
    - `-o dynamicApp`: Output executable named `dynamicApp`.
    - `-L ./lib/`: Directory containing the shared library.
    - `-lmylib`: Link with the shared library `libmylib.so`.
    - `-Wl,-rpath=./lib/`: Set runtime library search path to `./lib`.
> * *Alternative to -Wl,-rpath=*
> * `export LD-LIBRARY_PATH=./PATH`
> * Put under 'user/lib' directory

5. **Run the Dynamic Executable**

    ```sh
    ./dynamicApp
    ```

6. **Extract Printable Strings from the Executable**

    ```sh
    strings dynamicApp
    ```
    - Display printable strings in the executable.

7. **Print Shared Library Dependencies**

    ```sh
    ldd dynamicApp
    ```
    - Display shared library dependencies of the executable.


## Summary

- **Static Library**:
  - Compile source files to object files.
  - Archive object files into a static library.
  - Link the static library with the main program to create an executable.

- **Dynamic Library**:
  - Compile source files to position-independent object files.
  - Create a shared library from the object files.
  - Link the shared library with the main program to create an executable.

- **Utilities**:
  - `objdump -T` to show the symbol table of a shared library.
  - `strings` to extract printable strings from a binary file.
  - `ldd` to print shared library dependencies of an executable or a shared library.

---
