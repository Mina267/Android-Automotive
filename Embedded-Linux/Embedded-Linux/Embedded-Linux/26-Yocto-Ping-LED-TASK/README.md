## 1. Clone the `meta-raspberrypi` Layer

The `meta-raspberrypi` layer contains machine configurations and recipes for building images for Raspberry Pi.

```bash
cd ~/yocto
git clone -b kirkstone https://github.com/agherzan/meta-raspberrypi.git
```

## 2. Create Your Own Layer
### A. Initialize the Build Environment
```bash
source oe-init-build-env rpibuild
```
Your current path should be `~/yocto/poky/rpibuild`.

### B. Using BitBake to Create a Layer

BitBake can automate the creation of a new layer:

```bash
bitbake-layers create-layer ../../meta-mina
```

This command creates the basic structure of your layer, including `conf`, `classes`, `recipes`, and other necessary directories.
## 3. Create Your Layer File Hierarchy
### `conf/` Directory
- **Purpose**: Contains configuration files for layers, machines, and distributions.
- **Key Files**:
  - **`layer.conf`**: Defines layer structure and dependencies.
  - **`machine/mymachine.conf`**: Configures target hardware.
  - **`distro/mydistro.conf`**: Configures distribution settings.

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

   **Enable `systemd`:**
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


   ENABLE_UART = "1"

   # Ensure systemd is part of the distro features
   DISTRO_FEATURES:append = " systemd"
   ```

## 5. Source the Build Environment


### A. Add Required Layers
Your current path should be ~/yocto/poky/rpibuild.
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

### B. Edit `local.conf`

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
## 6. Build the Yocto Project

### A. Start the Build Process
```bash
bitbake -k myimage
```
This command builds your custom image for the specified target machine. The `-k` option allows the build to continue even if some tasks fail.

---
## 7. Hierarchy of `meta-mina` Layer (Example)

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
  ├── recipes-image/
  │   └── image
  │       └── myimage.bb
  └── recipes-pingapp/
      └── pingappp
          ├── files     │ 
          │   └── ping.sh
          └── pingapp_1.0.bb
  ```


## 8. Recipe



```
SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

# Script to be installed
SRC_URI = "file://ping.sh"

# Add bash as a runtime dependency
RDEPENDS:${PN} += "bash"

# The source directory, since ping.sh is in the files directory
S = "${WORKDIR}"
inherit systemd

SYSTEMD_AUTO_ENABLE = "enable"

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${S}/ping.sh ${D}${bindir}/ping.sh
}

```



## 9. Script
```
#!/bin/sh

# Set default values
PIN_NUMB=${1:-27}
IP_ADDRESS=${2:-192.168.1.9}

# Check if the GPIO pin is already exported
if [[ ! -d /sys/class/gpio/gpio${PIN_NUMB} ]]; then
  echo "${PIN_NUMB}" > /sys/class/gpio/export
  sleep 0.1  # sleep time
  echo "out" > /sys/class/gpio/gpio${PIN_NUMB}/direction
fi

# Check network connectivity and set GPIO value
if ping -c 3 "${IP_ADDRESS}" > /dev/null 2>&1; then
  echo 0 > /sys/class/gpio/gpio${PIN_NUMB}/value
else
  echo 1 > /sys/class/gpio/gpio${PIN_NUMB}/value
fi

```

## 10. Copy image to SD-card
```
sudo dd if=/home/mina/yocto/poky/rpibuild/tmp/deploy/images/raspberrypi3-64/mina-sdimg.rootfs.rpi-sdimg  of=/dev/sdb bs=4M status=progress

```