
# Writing Custom `do_compile()` and `do_install()` Functions in Bitbake

When working with Yocto and Bitbake, you may need to write custom functions to handle the compilation and installation of your application. Below is a guide on how to do this and some common issues you might encounter.

### **Customizing the `do_compile()` Function**

The `do_compile()` function in a Yocto recipe is responsible for compiling the source code. By default, Yocto uses standard procedures for compiling, but you can override this function to define custom compilation steps.

#### **Basic `do_compile()` Example**

In this example, we'll compile a simple C program (`main.c`) and output the executable to the build directory (`${B}`).

```bash
do_compile() {
    ${CC} ${CFLAGS} main.c -o ${B}/myapp
}
```

- **`${CC}`**: The compiler (e.g., `gcc`) used for compilation.
- **`${CFLAGS}`**: Compiler flags used to modify the compilation process.
- **`${B}`**: The build directory where the compiled output will be stored.

#### **Handling Source Files with `SRC_URI` and `FILESPATH`**

When you try to build the package using `bitbake <recipe>`, you might encounter an error during the fetch phase, such as:

```bash
ERROR: do_fetch: Fetcher failure for URL: 'file://main.c'. Unable to fetch URL from any source.
```

This error occurs because the `main.c` file is not in the expected location. Yocto's fetcher can't find the file because it hasn't been correctly specified in the `SRC_URI` or `FILESPATH`.

##### **Solution: Specify the Correct Path**

1. **Define `SRC_URI`**: Ensure that `SRC_URI` correctly points to the location of `main.c`. If the file is local, use the `file://` schema.

   ```bash
   SRC_URI = "file://main.c"
   ```

2. **Set `FILESPATH`**: `FILESPATH` is a variable that tells BitBake where to look for files specified in `SRC_URI`. If `main.c` is located in a specific directory, append that directory to `FILESPATH`.

   ```bash
   FILESPATH:append = " :${THISDIR}/mina:"
   ```

   - **`${THISDIR}`**: Points to the directory where the recipe file (`.bb`) is located.
   - **`:append`**: Ensures the path is appended to any existing paths in `FILESPATH`.

3. **Update `do_compile()`**: Now, reference the `main.c` file using `${WORKDIR}`.

   ```bash
   do_compile() {
       ${CC} ${CFLAGS} ${WORKDIR}/main.c -o ${B}/myapp
   }
   ```

   - **`${WORKDIR}`**: The working directory where BitBake stages the source files.
   - Here, `${WORKDIR}/main.c` points to the `main.c` file in the working directory.
    - `${B}` is the directory where intermediate build files are placed.

#### **Common Error: Missing `main.c`**

If you encounter an error like:

```bash
do_compile() failed: No such file or directory: main.c
```

This error usually means that `main.c` is not found in `${WORKDIR}` because `SRC_URI` or `FILESPATH` is not set correctly.

- **Check `SRC_URI`**: Ensure that `SRC_URI` correctly fetches `main.c` to `${WORKDIR}`.
- **Verify `FILESPATH`**: Make sure that `FILESPATH` includes the directory where `main.c` is stored.

### **Customizing the `do_install()` Function**

The `do_install()` function is used to copy the compiled output to the target directory within the build system. This is where you define where the final files should be installed.

```bash
do_install() {
    mkdir -p ${D}/usr/bin
    cp ${B}/myapp ${D}/usr/bin
}
```

- **`${D}`**: The destination directory for the final installation.
- **`mkdir -p`**: Ensures that the `/usr/bin` directory exists in the destination.
- **`cp ${B}/myapp ${D}/usr/bin`**: Copies the compiled application from `${B}` to the target directory `${D}`.

### **Overriding Local Variables**

In Yocto recipes, local variables and functions can be overridden within the recipe file itself. This allows you to change the behavior of the build process by modifying these variables.

- **Weak Assignments**: Variables in Yocto are often assigned using a weak assignment (`=`), which means they can be overridden.
- **Override Example**: You might want to change the compiler flags or the install directory in different recipes or configurations.

## Some important recipe variables

### **1. `FILESPATH`**
- `FILESPATH` is a variable that BitBake uses to determine the directories it should search in when trying to fetch files specified in `SRC_URI` with `file://` URLs.
- By appending a directory to `FILESPATH`, you tell BitBake to include that directory in its search paths.

  **Example**:
  ```bash
  FILESPATH:append = ":${THISDIR}/mina"
  ```
  - Here, `${THISDIR}/mina` is the directory containing your source file, `main.c`.

### **2. `SRC_URI`**
- `SRC_URI` is where you define the source files and their locations that BitBake should fetch.
- When using `file://` in `SRC_URI`, BitBake will look for the file in the directories specified by `FILESPATH`.

  **Example**:
  ```bash
  SRC_URI = "file://main.c"
  ```
  - This tells BitBake to look for `main.c` in the directories listed in `FILESPATH`.

### **3. `WORKDIR`**
- Once BitBake finds the file using `SRC_URI` and `FILESPATH`, it fetches the file and places it into the `WORKDIR`.
- `WORKDIR` is a directory specific to the task where BitBake unpacks and prepares the sources for building.

  **Example**:
  ```bash
  do_compile() {
      ${CC} ${CFLAGS} ${WORKDIR}/main.c -o ${B}/myapp
  }
  ```
  - `${WORKDIR}/main.c` points to the `main.c` file that has been fetched and placed in `WORKDIR`.

### **Process Flow**:
1. **Set `FILESPATH`**: Append your source file directory to `FILESPATH`.
2. **Define `SRC_URI`**: Use `file://main.c` in `SRC_URI` to tell BitBake where to find your source file.
3. **Fetch & Place in `WORKDIR`**: BitBake fetches `main.c` using `FILESPATH` and places it in `WORKDIR`.
4. **Compile**: Use `${WORKDIR}/main.c` in `do_compile()` to compile the source code.

By correctly setting up `FILESPATH` and `SRC_URI`, BitBake can successfully fetch your local source files and place them in `WORKDIR`, where they are ready to be compiled and used in the build process.

### **Summary**

1. **FILESPATH**: Append the directory containing `main.c` to `FILESPATH`.
2. **SRC_URI**: Use `file://main.c` to fetch the file from `FILESPATH`.
3. **do_compile()**: Compile the code, ensuring paths are correct.
4. **do_install()**: Install the compiled binary into the target filesystem.
5. **Override Variables**: Local variables can be overridden in the recipe for flexibility.