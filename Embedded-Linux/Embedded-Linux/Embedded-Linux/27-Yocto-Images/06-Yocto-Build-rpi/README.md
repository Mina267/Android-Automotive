

# Raspberry Pi Image with Yocto

This README provides a detailed guide to building a Yocto image for Raspberry Pi with systemd and Qt5 support. Follow the steps below to set up your Yocto environment, create a custom layer, and build the image.

## 1. Clone the `meta-raspberrypi` Layer

The `meta-raspberrypi` layer contains machine configurations and recipes for building images for Raspberry Pi.

```bash
cd ~/yocto
git clone -b kirkstone https://github.com/agherzan/meta-raspberrypi.git
```

## 2. Create Your Own Layer

### A. Using BitBake to Create a Layer

BitBake can automate the creation of a new layer:

```bash
cd ~/yocto
bitbake-layers create-layer meta-mina
```

This command creates the basic structure of your layer, including `conf`, `classes`, `recipes`, and other necessary directories.

## 3. Create Your Layer File Hierarchy


## Directory Structure and Key Files

### `conf/` Directory
- **Purpose**: Contains configuration files for layers, machines, and distributions.
- **Key Files**:
  - **`layer.conf`**: Defines layer structure and dependencies.
  - **`machine/mymachine.conf`**: Configures target hardware.
  - **`distro/mydistro.conf`**: Configures distribution settings.

### Distribution Configuration (`distro.conf`)
This file defines key aspects of your distribution, including:
- **Kernel Version**: Specifies the version of the Linux kernel to use.
- **Library**: Defines the C library used (e.g., `glibc`, `musl`).
- **Init Process**: Selects the init system (e.g., `systemd`, `sysvinit`, `busybox`).
- **Package Manager**: Chooses the package format (`rpm`, `deb`, `ipk`).
- **U-Boot Version**: Specifies the version of U-Boot, the bootloader.

### A. Create a Custom Distribution

1. **Navigate to the Distribution Directory:**
   ```bash
   cd ~/yocto/meta-mina/conf/distro
   ```

2. **Create `mina.conf`:**
   ```bash
   code mina.conf
   ```

3. **Add the Following Content:**
   ```bash
   # Include the base poky distribution
   include conf/distro/poky.conf

   # Define your custom distribution name and version
   DISTRO = "mina"
   DISTRO_NAME = "mina"
   DISTRO_VERSION = "4.0.20"
   DISTRO_CODENAME = "kirkstone"
   MAINTAINER = "mina.magdy.aziz.2698@gmail.com"

   # Enable systemd as the init manager
   DISTRO_FEATURES:append = " systemd"
   VIRTUAL-RUNTIME_init_manager = "systemd"

   # Optional: Define additional systemd-related runtime managers
   DISTRO_FEATURES_BACKFILL_CONSIDERED:append = " sysvinit"
   VIRTUAL-RUNTIME_initscripts = "systemd-compat-units"
   VIRTUAL-RUNTIME_login_manager = "shadow-base"
   VIRTUAL-RUNTIME_dev_manager = "systemd"
   ```

4. **Enable `systemd`:**
   - The distribution features are defined in the `distro.conf` file of your layer. To enable `systemd`, you need to append the required features and make sure the system defaults to `systemd` instead of SysVinit.
   - You can get reference from:
     ```bash
     code /home/mina/yocto/poky/meta/conf/distro/include/init-manager-systemd.inc 
     ```

### B. Create a Custom Machine Configuration

1. **Create the Directory Structure:**
   ```bash
   mkdir -p ~/yocto/meta-mina/conf/machine
   ```

2. **Create and Edit `minamachine.conf`:**
   ```bash
   code ~/yocto/meta-mina/conf/machine/minamachine.conf
   ```

3. **Configure `minamachine.conf`:**
   ```bash
   # Load the base configuration from raspberrypi3-64
   require conf/machine/raspberrypi3-64.conf

   # Set a custom description for the machine
   MACHINEOVERRIDES:append = " ${MACHINE}:"
   ```



## 4. Create or Modify Your Image Recipe

To create an image recipe that includes systemd and the necessary packages, follow these steps:

1. **Create or Edit the Image Recipe:**
   ```bash
   code ~/yocto/meta-mina/recipes-core/images/myimage.bb
   ```

2. **Add the Following Content:**
   ```bash
   include recipes-sato/images/core-image-sato.bb

   SUMMARY = "An image with systemd support for Raspberry Pi."

   # Include the required packages
   IMAGE_INSTALL:append = " python3 bash git apt apt-utils make cmake"
   IMAGE_INSTALL:append = " openssh-sftp-server rsync"
   IMAGE_INSTALL:append = " qtdeclarative qtmultimedia qtmultimedia-plugins liberation-fonts"
   IMAGE_INSTALL:append = " v4l-utils gstreamer1.0-plugins-base gstreamer1.0-plugins-good"
   IMAGE_INSTALL:append = " gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav"
   IMAGE_INSTALL:append = " htop iotop wpa-supplicant"

   PACKAGECONFIG_FONTS:append_pn-qtbase = " fontconfig"

   ENABLE_UART = "1"

   # Ensure systemd is part of the distro features
   DISTRO_FEATURES:append = " systemd"
   ```

## Image Recipe Directory Structure

### `recipes-image/image/myimage.bb`
- **Purpose**: Defines a custom image.
- **Usage**: Lists packages and configurations for the image.
- **Key Variables**:
  - `IMAGE_INSTALL`: Packages to include in the image.
  - `inherit`: Inherits common image-building classes.

The package feeder's job is to move the installed files from the destination directory to the root filesystem. To include your recipe in the root filesystem, append it to the `IMAGE_INSTALL` variable:
```bash
IMAGE_INSTALL:append = " <recipe>"
```

### `IMAGE_INSTALL`
- **Purpose**: Lists packages to be included in the final image.
- **Usage**: Used in image recipes and `local.conf`.
- **Example**: `IMAGE_INSTALL += "base-files busybox"`

## 5. Recipe Types

### A. Recipe Types
1. **Package Recipes**:
   - Define how to build and install software packages.

2. **BSP Recipes**:
   - Board Support Package (BSP) recipes configure and build the hardware-specific software.

## 6. Source the Build Environment

### A. Initialize the Build Environment
```bash
source oe-init-build-env rpi
```
Your current path should be `~/yocto/poky/rpi`.

### B. Add Required Layers

1. **Add the `meta-raspberrypi` Layer:**
   ```bash
   bitbake-layers add-layer ../../meta-raspberrypi
   ```

2. **Add the `meta-mina` Layer:**
   ```bash
   bitbake-layers add-layer ../../meta-mina
   ```

3. **Add the `meta-qt5` Layer:**
   ```bash
   bitbake-layers add-layer ../../meta-qt5
   ```

4. **Add the `meta-openembedded` Layer:**
   ```bash
   bitbake-layers add-layer ../../meta-openembedded
   ```

5. **Verify Layers:**
   ```bash
   bitbake-layers show-layers
   ```

### `bblayer.conf`
- **Purpose**: Lists the layers included in the build.
- **Usage**: Defines paths to metadata layers.
- **Key Variables**:
  - `BBLAYERS`: Absolute paths to layers.
  - `BBLAYERS_CONF_VERSION`: Tracks file format version.

### C. Edit `local.conf`

```bash
code ~/yocto/poky/build/conf/local.conf
```

Update the configuration with your custom settings:

```bash
DISTRO = "mina"

DL_DIR ?= "/home/mina/yocto/downloads"
SSTATE_DIR ?= "/home/mina/yocto/sstate-cache"

MACHINE = "minamachine"
IMAGE_FSTYPES = "tar.bz2 ext4 rpi-sdimg"

INHERIT += "rm_work"
```

### `local.conf`
- **Purpose**: Main configuration file for customizing the build.
- **Usage**: Adjusts machine type, distribution, and build settings.
- **Key Variables**:
  - `MACHINE`: Target hardware platform.
  - `DISTRO`: Distribution configuration.
  - `IMAGE_INSTALL`: Packages to include in the image.
  - `BB_NUMBER_THREADS` & `PARALLEL_MAKE`: Control build parallelism.

## 7. Build the Yocto Project

### A. Start the Build Process
```bash
bitbake -k myimage
```
This command builds your custom image for the specified target machine. The `-k` option allows the build to continue even if some tasks fail.

---

## 8. Hierarchy of `meta-mina` Layer (Example)

  ```
  meta-mina/
  ├── conf
  │   ├── layer.conf
  │   ├── machine
  │   │   └── rpi.conf 
  |   └── distro
  │       └── Mina.conf   
  ├── COPYING.MIT
  ├── README
  ├── recipes-demo
  │   └── demo
  │       └── demo_0.1.bb
  ├── classes/
  ├── recipes-myrecipe/
  │   └── myrecipe/
  │       └── myrecipe_1.0.bb
  │       └── myrecipe_%.bbappend
  │       └── files/
  │           └── main.c
  │           └── myservice.service
  ├── recipes-image/
  │   └── image
  │       └── myimage.bb
  └── recipes-kernel/
      └── hello-mod
          ├── files
          │   ├── COPYING
          │   ├── hello.c
          │   └── Makefile
          └── hello-mod_0.1.bb
  ```


