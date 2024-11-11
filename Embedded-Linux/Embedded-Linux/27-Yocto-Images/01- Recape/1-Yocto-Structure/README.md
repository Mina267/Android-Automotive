# Yocto Recap

## Core Image Recipe (`core-image-minimal.bb`)
- The `core-image-minimal.bb` recipe is used by BitBake to build a minimal image that can boot a device.
- This image includes only the essential components needed to start the system.

### Steps to Build for Raspberry Pi:
1. **Clone Meta-Layer**: 
   - Clone the necessary meta-layer for Raspberry Pi support, such as `meta-raspberrypi`.
   
2. **Add Layer**:
   - Add the cloned layer to your Yocto build environment using `bitbake-layers add-layer`.

3. **Board Configuration (`conf/machine`)**:
   - Configure the machine settings in `conf/machine/` for the target board (e.g., Raspberry Pi).

4. **Edit `local.conf`**:
   - Set the machine name in `local.conf` to match your target board (e.g., `MACHINE = "raspberrypi4"`).

5. **Build the Image**:
   - Use the `core-image-minimal` recipe to build the image with BitBake:
     ```bash
     bitbake core-image-minimal
     ```

## Distribution Configuration (`distro.conf`)
This file defines key aspects of your distribution, including:
- **Kernel Version**: Specifies the version of the Linux kernel to use.
- **Library**: Defines the C library used (e.g., `glibc`, `musl`).
- **Init Process**: Selects the init system (e.g., `systemd`, `sysvinit`, `busybox`).
- **Package Manager**: Chooses the package format (`rpm`, `deb`, `ipk`).
- **U-Boot Version**: Specifies the version of U-Boot, the bootloader.

## Global Variables
- **Customizing Global Variables**:
  - You can override global variables in your meta-layer, but this change will not affect the global value for other layers. It only applies within the scope of your layer.

## Integrating a New Application into Root Filesystem (rootfs)
- BitBake executes tasks sequentially as defined in the recipe:
  ```bash
  do_fetch() {
      # Fetch the source
  }
  do_unpack() {
      # Unpack the source into WORKDIR
  }
  do_patch() {
      # Apply patches
  }
  do_configure() {
      # Configure the package
  }
  do_compile() {
      # Compile the source
  }
  do_install() {
      # Install into the destination directory (D)
  }
  ```

- **Final Installation**:
  - After the `do_install` step, the files are placed in the destination directory (`${D}`). However, this does not mean they are in the root filesystem yet.
  - The package feeder's job is to move the installed files from the destination directory to the root filesystem.
  - To include your recipe in the root filesystem, append it to the `IMAGE_INSTALL` variable:
    ```bash
    IMAGE_INSTALL:append = " <recipe>"
    ```

### Inspecting Task Execution
- To inspect how tasks work, use:
  ```bash
  bitbake -e <recipe> > destination_file
  ```

## Yocto Hierarchy
- BitBake parses all configuration and recipe files, producing the same output regardless of file locations.
- However, adhering to Yocto’s hierarchical structure and standards is crucial for:
  - Seamless debugging.
  - Better understanding of the project.
  - Providing a standardized reference for developers.

### Recipe Types
1. **Package Recipes**:
   - Define how to build and install software packages.
  
2. **BSP Recipes**:
   - Board Support Package (BSP) recipes configure and build the hardware-specific software.

### Example Yocto Directory Structure
```plaintext
meta-mina/
    ├── recipes-bsp/           # BSP Recipes
    ├── recipes-core/          # Package Recipes
    ├── conf/
    │   └── distro/
    │       └── mina.conf      # Distribution Configuration
    └── mina-image.bb          # Custom Image Recipe
```

### FILESPATH
- The default set of directories the OpenEmbedded build system uses when searching for patches and files. It is defined in the base.bbclass class found in meta/classes in the Source Directory. Do not hand-edit the FILESPATH variable.

### FILESEXTRAPATHS
- Extends the search path the OpenEmbedded build system uses when looking for files and patches as it processes recipes and append files.
- To add paths for `SRC_URI` do not append to  FILESPATH append to FILESEXTRAPATHS
