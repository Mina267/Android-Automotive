# Yocto recipe Tasks
### 1. `do_fetch()`
- **Purpose**: Fetches the source code or files required for building the package.
- **Key Variables**:
  - `SRC_URI`: Specifies the locations (URLs or local paths) from where the source files are fetched.
  - `DL_DIR`: Directory where downloaded sources are stored. Defaults to `downloads/` in the build directory.
  - `FILESPATH`: The default set of directories the OpenEmbedded build system uses when searching for patches and files.
  - `FILESEXTRAPATHS`: Extends the search path the OpenEmbedded build system uses when looking for files and patches as it processes recipes and append files.
  - To add paths for `SRC_URI` do not append to  FILESPATH append to FILESEXTRAPATHS

### 2. `do_unpack()`
- **Purpose**: Unpacks the fetched source code into the working directory.
- **Key Variables**:
  - `WORKDIR`: The working directory for the current recipe. This is where the source code is unpacked and where all the recipe's tasks are performed.
  - `S`: The directory within `WORKDIR` where the unpacked source code is placed. By default, `S` is `WORKDIR`, but it can be modified in the recipe.

### 3. `do_patch()`
- **Purpose**: Applies patches to the unpacked source code.
- **Key Variables**:
  - `S`: The directory where the source code resides after unpacking, and where the patches are applied.
  - `PATCHES`: List of patches to be applied, typically derived from `SRC_URI`.
  - `PATCHTOOL`: The tool used to apply patches, such as `patch` or `quilt`.

### 4. `do_configure()`
- **Purpose**: Configures the package for building, often by running scripts like `./configure` or by setting up environment variables.
- **Key Variables**:
  - `S`: The directory where the source code is located and where the configuration scripts are run.
  - `CFLAGS`, `CPPFLAGS`, `LDFLAGS`: Compiler and linker flags that are often passed to the configuration scripts.
  - `BUILD_SYS`, `HOST_SYS`, `TARGET_SYS`: Variables that define the system on which the software is being built, the system on which it will run, and the target system for cross-compilation.

### 5. `do_compile()`
- **Purpose**: Compiles the source code into binaries or libraries.
- **Key Variables**:
  - `S`: The directory where the source code is compiled.
  - `B`: The build directory where the actual build process occurs. It may be different from `S` if out-of-tree builds are performed.
  - `CFLAGS`, `CPPFLAGS`, `LDFLAGS`: Compiler and linker flags used during the compilation process.

### 6. `do_install()`
- **Purpose**: Installs the compiled binaries or libraries into a temporary destination directory.
- **Key Variables**:
  - `D`: The destination directory where the compiled files are installed during the packaging process. This is not the final root filesystem but a staging area.
  - `bindir`, `libdir`, `includedir`, `sysconfdir`, etc.: Standard directories within `${D}` where different types of files (binaries, libraries, headers, config files) are placed.
  - `PN`: The package name, used to organize installed files within `D`.

---

### Example Summary of Key Variables by Function

- **do_fetch()**: `SRC_URI`, `DL_DIR`
- **do_unpack()**: `WORKDIR`, `S`
- **do_patch()**: `S`, `PATCHES`, `PATCHTOOL`
- **do_configure()**: `S`, `CFLAGS`, `CPPFLAGS`, `LDFLAGS`, `BUILD_SYS`, `HOST_SYS`, `TARGET_SYS`
- **do_compile()**: `S`, `B`, `CFLAGS`, `CPPFLAGS`, `LDFLAGS`
- **do_install()**: `D`, `bindir`, `libdir`, `includedir`, `sysconfdir`, `PN`

