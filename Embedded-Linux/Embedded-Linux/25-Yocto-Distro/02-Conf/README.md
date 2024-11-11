# Yocto Configuration Files

### Configuration Files Path
All configuration files are located in:
```
/home/mina/yocto/poky/build/conf
```

## 1. `bblayer.conf`
This file is crucial for managing the layers used in your Yocto build.

- **BBLAYERS**: 
  - **Purpose**: This variable lists the layers to enable during the build. It is defined in the `bblayers.conf` configuration file and tells BitBake which layers to include.
  - **Example Command**: To add a new layer, you can use the following BitBake command:
    ```bash
    bitbake-layers add-layer ../../<meta-name>
    ```
  - **Layer Path**: Ensure that the paths to the layers are correct and relative to the build directory. Layers typically reside in directories like `meta-`, `meta-yocto`, `meta-poky`, etc.

## 2. `local.conf`
This is one of the primary configuration files used by BitBake to customize the build process.

### Machine Configuration
- **MACHINE**: 
  - **Purpose**: This variable sets the target hardware for your build. The machine type is defined in a `.conf` file within a BSP (Board Support Package) layer.
  - **Example Configurations**: Here are some example configurations for default QEMU machines:
    ```bash
    #MACHINE ?= "qemuarm"
    #MACHINE ?= "qemuarm64"
    #MACHINE ?= "qemumips"
    #MACHINE ?= "qemumips64"
    #MACHINE ?= "qemuppc"
    #MACHINE ?= "qemux86"
    #MACHINE ?= "qemux86-64"
    #
    # There are also the following hardware board target machines included for 
    # demonstration purposes:
    #
    #MACHINE ?= "beaglebone-yocto"
    #MACHINE ?= "genericx86"
    #MACHINE ?= "genericx86-64"
    #MACHINE ?= "edgerouter"
    #
    # This sets the default machine to be qemux86-64 if no other machine is selected:
    MACHINE ??= "qemux86-64"
    ```

#### Machine Configuration Files Path

<p align="center">
	<img src="https://github.com/user-attachments/assets/9e8d065e-9f7b-461f-94e6-2925fb69ec49" width=85% height=85% />
</p>

- **Location**: Machine configurations are located in:
  ```
  /home/mina/yocto/poky/meta/conf/machine
  ```
  This folder contains reference configurations for various architectures, providing a starting point for your own machine configurations.
  
- **Raspberry Pi Example**: To configure for a Raspberry Pi, you might need to clone the relevant meta layer:
  ```bash
  git clone https://github.com/raspberrypi/meta-raspberrypi
  ```

### Important Variables in Machine Configuration
- **UBOOT_MACHINE**: 
  - **Purpose**: This variable specifies the value passed on the make command line when building a U-Boot image.
  - **Example**:
    ```bash
    UBOOT_MACHINE ?= "qemu-x86_64_defconfig"
    ```
  - **Note**: U-Boot is a popular bootloader for embedded systems, and this variable allows customization for different hardware platforms.

- **BeagleBone and Other Machines**: Some machines, like BeagleBone, have their configurations defined in:
  ```
  /home/mina/yocto/poky/meta-yocto-bsp/conf/machine
  ```
  These configurations might not be in the primary directory but are included in specific BSP layers provided by Yocto.

  <p align="center">
	<img src="https://github.com/user-attachments/assets/c95dcd46-a701-46ec-bda3-b3de4cce7e17" width=85% height=85% />
  </p>



### Machine Configuration Hierarchy
- **Hierarchy**:
  ```
  layer
    └── machine
          └── machineName.conf
  ```
- **Setting the Machine in `local.conf`**: After identifying or creating the correct machine configuration, set the `MACHINE` variable in `local.conf` to point to your desired machine.

### Interaction Between Recipes and Kernel
- **Recipes**: 
  - Recipes define how software packages are built and installed. They interact with the kernel through system calls, for example, placing binaries in `/usr/bin/`.
  - **Board Support Package (BSP)**: The BSP communicates directly with the kernel, often inserting modules with commands like `insmod`.

### Additional Important Variables in `local.conf`
- **DL_DIR**: 
  - **Purpose**: This variable defines the central directory for storing downloaded files during the build process. By default, it is set to the `downloads` directory within the build directory.
  - **Customization**: You can change this path to a shared location to save bandwidth and time across multiple builds.

- **SSTATE_DIR**: 
  - **Purpose**: This is the directory for the shared state cache, which stores the status of tasks that have already run. It speeds up subsequent builds by avoiding redundant task execution.
  - **Optimization**: Setting this directory to a shared or networked location can optimize build times across different machines.

- **TMPDIR**: 
  - **Purpose**: The working directory for all recipes. This is where temporary files, build artifacts, and intermediate outputs are stored.
  - **Deployment**: The final image output from this directory can be deployed to an SD card using tools like `dd`.

### Distribution Configuration (`DISTRO`)
- **DISTRO**: 
  - **Purpose**: Represents the distribution name. If this variable is left blank, Yocto will default to the configuration file at `meta/conf/distro/defaultsetup.conf`.
  - **Customization**: This allows you to specify a unique name for your custom distribution.

## Creating a New Distribution

### Distribution Configuration Hierarchy
- **Hierarchy**:
  ```
  layer (meta)
    └── conf
          └── distro
                └── DistroName.conf
  ```
- **Example**: For the Poky distribution, the configuration file is located at:
  ```
  /home/mina/yocto/poky/meta-poky/conf/distro/poky.conf
  ```

### Steps to Create Your Own Distribution
- Use the same hierarchy when creating your own distribution. For example:
  ```
  /home/mina/yocto/meta-mina/conf/distro/almaza.conf
  ```
- Include the Poky configuration to leverage existing settings and simplify your setup:
  ```bash
  include meta-poky/conf/distro/poky.conf
  ```

### Key Variables to Customize in Your Distribution
```bash
DISTRO = "Mina"
DISTRO_NAME = "Almaza"
#DISTRO_VERSION = "3.4+snapshot-${METADATA_REVISION}"
DISTRO_VERSION = "4.0.20"
DISTRO_CODENAME = "kirkstone"
MAINTAINER = "Mina@outlook.com"
```


### Differences Between Yocto Distributions

### 1. Package Manager
Different distributions use different package managers for handling packages:
- **IPK**: Used by OpenEmbedded-based systems.
- **RPM**: Used by distributions like Fedora.
- **DEB**: Used by Debian-based systems.

  **Example Path for RPM Packages**:
  ```
  /home/mina/yocto/poky/build/tmp/deploy/rpm
  ```
  - Packages in this directory can be installed on the target image if it uses RPM as its package manager.

### 2. Library
The choice of C library affects the compatibility and features available in the system:
- **glibc**: The GNU C Library, the most commonly used.
- **uclibc**: A smaller alternative to glibc, used in resource-constrained environments.
- **musl**: Another lightweight C library aimed at simplicity and correctness.

### 3. Init Process
Different distributions use different init systems to manage system services:
- **BusyBox**: Provides a lightweight init system along with many common Unix utilities.
- **systemd**: A modern and complex init system used by many contemporary Linux distributions.
- **SystemV**: The traditional Unix System V init system.

### 4. Kernel Version
Distributions may use different versions of the Linux kernel, which can impact hardware support and feature availability. To change the kernel configuration for a specific machine, modify the `machine.conf` file:
- **Location**:
  ```
  /home/mina/yocto/poky/meta/conf/machine
  ```
- **Configuration Example**:
  ```bash
  KERNEL_VERSION = "5.10"
  ```

### 5. U-Boot Version
U-Boot is a popular bootloader for embedded systems. Different distributions might use different versions, which can affect bootloader capabilities and features.

## Important Yocto Configuration Variables

### PACKAGE_CLASSES
Defines the packaging format used by the build system. This can include RPM, DEB, IPK, etc.
- **Example Configuration**:
  ```bash
  PACKAGE_CLASSES = "package_rpm"
  ```

### PATCHRESOLVE
Controls how patch resolution is handled during the build process:
- **`PATCHRESOLVE = "noop"`**: No interactive patch resolution; errors will be reported in the terminal.
- **`PATCHRESOLVE = "user"`**: Interactive patch resolution; a new terminal will open to help resolve errors.

### BB_DISKMON_DIRS
Monitors disk space and inodes during the build process and can control the build based on these parameters:
- **Purpose**: Helps prevent builds from failing due to insufficient disk space or inodes.
- **Example Configuration**:
  ```bash
  BB_DISKMON_DIRS = "STAGING, TMPDIR"
  ```

### CONF_VERSION
Tracks the version of `local.conf`. This variable is incremented whenever there are incompatible changes in build/conf/:
- **Purpose**: Ensures that configuration changes are tracked and managed properly.
- **Example Configuration**:
  ```bash
  CONF_VERSION = "1"
  ```

### INHERIT
Used to include additional classes or functionality in the build process. It allows for extending the build system with custom classes:
- **Example Configuration**:
  ```bash
  INHERIT += "rm_work"
  ```
  - **`rm_work`**: Class to remove work directories after successful build to save space.





### Additional Customization Tips
- **Layer Priority**: When creating a new distribution, consider layer priorities (`BBFILE_PRIORITY`) to ensure your custom settings take precedence over defaults.
- **Package Management**: Customize package management settings (e.g., `PACKAGE_CLASSES`, `PACKAGE_FEED_BASE_PATH`) to define how your distribution handles binary packages.
- **Image Customization**: Define custom images (e.g., `core-image-mina`) in a separate recipe file to bundle specific packages and features in your final image.






