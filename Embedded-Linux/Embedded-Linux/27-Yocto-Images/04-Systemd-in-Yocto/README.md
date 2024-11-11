# **Systemd in Yocto**

### **Overview**
Yocto, by default, uses the **SysVinit** system for initialization. However, you may want to switch to **systemd**, a more modern and feature-rich system and service manager, especially if you're aiming for better dependency handling, parallelism during boot, and other advanced features.

### **Enabling Systemd in Yocto**

1. **Edit `distro.conf` to Enable `systemd`:**
   - The distribution features are defined in the `distro.conf` file of your layer. To enable `systemd`, you need to append the required features and make sure the system defaults to `systemd` instead of SysVinit.
   #### You can get reference from 
    ```
    code /home/mina/yocto/poky/meta/conf/distro/include/init-manager-systemd.inc 
    ```
    ```
    # Use systemd for system initialization
    DISTRO_FEATURES:append = " systemd"
    DISTRO_FEATURES_BACKFILL_CONSIDERED:append = " sysvinit"
    VIRTUAL-RUNTIME_init_manager ??= "systemd"
    VIRTUAL-RUNTIME_initscripts ??= "systemd-compat-units"
    VIRTUAL-RUNTIME_login_manager ??= "shadow-base"
    VIRTUAL-RUNTIME_dev_manager ??= "systemd"

    ```

    - copy this context configuration to your own `distro.conf' in your layer



   ```bitbake
   # Include the base poky distribution
   include conf/distro/poky.conf
   
   # Define your custom distribution name and version
   DISTRO = "Mina"
   DISTRO_NAME = "Almaza"
   DISTRO_VERSION = "4.0.20"
   DISTRO_CODENAME = "kirkstone"
   MAINTAINER = "Mina@outlook.com"

   # Enable systemd as the init manager
   DISTRO_FEATURES:append = " systemd"
   VIRTUAL-RUNTIME_init_manager = "systemd"
   
   # Optional: Define additional systemd-related runtime managers
   DISTRO_FEATURES_BACKFILL_CONSIDERED:append = " sysvinit"
   VIRTUAL-RUNTIME_initscripts = "systemd-compat-units"
   VIRTUAL-RUNTIME_login_manager = "shadow-base"
   VIRTUAL-RUNTIME_dev_manager = "systemd"
   ```

   - **Explanation:**
     - `DISTRO_FEATURES:append = " systemd"`: This appends the `systemd` feature to your distribution.
     - `VIRTUAL-RUNTIME_init_manager = "systemd"`: Ensures that `systemd` is used as the init system.
     - The other `VIRTUAL-RUNTIME` variables ensure compatibility with `systemd` for device management, login management, and init scripts.

2. **Create or Modify Your Image Recipe (`myimage.bb`):**
   - Your image recipe must reflect the `systemd` dependency. This can be done by adding `systemd` to `DISTRO_FEATURES` and ensuring that the necessary packages are included.
   
   ```bitbake
   SUMMARY = "A minimal image with systemd support for Raspberry Pi."
   inherit core-image

   # Include the required packages
   IMAGE_INSTALL:append = " packages"

   # Ensure systemd is part of the distro features
   DISTRO_FEATURES:append = " systemd"

   # Optionally define root filesystem size
   IMAGE_ROOTFS_SIZE ?= "8192"
   IMAGE_ROOTFS_EXTRA_SPACE:append = "${@bb.utils.contains("DISTRO_FEATURES", "systemd", " + 4096", "", d)}"
   ```

   - **Explanation:**
     - `inherit core-image`: Inherits from the core image class to leverage basic image creation functionalities.
     - `IMAGE_INSTALL:append = " packages"`: Adds custom packages to the image.
     - `IMAGE_ROOTFS_EXTRA_SPACE`: Provides additional space in the root filesystem if `systemd` is included.

3. **Ensure `local.conf` Points to Your Custom Distribution:**
   - Update your `local.conf` to use your custom distribution (`Mina`) and target machine (e.g., Raspberry Pi).
   
   ```plaintext
   MACHINE ?= "rpi"
   DISTRO ?= "Mina"
   ```

   - **Explanation:**
     - `MACHINE ?= "rpi"`: Specifies the target machine, in this case, a Raspberry Pi.
     - `DISTRO ?= "Mina"`: Selects your custom distribution named `Mina`.

4. **Build the Image:**
   - With all configurations set, proceed to build your custom image using the BitBake tool.
   
   ```bash
   bitbake myimage
   ```

   - **Explanation:**
     - `bitbake myimage`: Compiles the image defined in `myimage.bb` using your custom configurations.

### **Layer Structure Example**

Here’s how your Yocto layer might be structured:

```plaintext
meta-mina/
├── conf
│   ├── layer.conf
│   ├── machine
│   │   └── rpi.conf
│   └── distro
│       └── Mina.conf
├── classes/
├── recipes-core/
│   └── images/
│       └── myimage.bb
├── recipes-demo/
│   └── demo/
│       └── demo_0.1.bb
├── recipes-myrecipe/
│   └── myrecipe/
│       ├── myrecipe_1.0.bb
│       ├── myrecipe_%.bbappend
│       └── files/
│           ├── main.c
│           └── myservice.service
├── recipes-kernel/
│   └── hello-mod/
│       ├── files/
│       │   ├── COPYING
│       │   ├── hello.c
│       │   └── Makefile
│       └── hello-mod_0.1.bb
├── COPYING.MIT
└── README
```

### **Notes:**
- **Systemd Integration:** Including `systemd` in your distribution can significantly change how services are managed, making it crucial to test the transition thoroughly.
- **Meta-Layer Best Practices:** Always create and modify your configurations and recipes within your custom layer (`meta-mina`), avoiding direct changes to the `poky` files to maintain the integrity of the Yocto project.
- **Version Control:** Keep your customizations under version control, particularly the `Mina.conf` and `myimage.bb`, to track changes and collaborate with other developers.
