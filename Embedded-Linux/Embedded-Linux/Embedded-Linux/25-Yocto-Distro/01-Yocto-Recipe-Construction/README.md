# Yocto Recipe Construction

## A. **Header Section**

### Basic Fields
- **SUMMARY**: A brief description of the software.
- **DESCRIPTION**: A more detailed explanation of what the software does.
- **LICENSE**: Specifies the software license. Common examples include:
  - `LICENSE="MIT"`
  - `LICENSE="GPL"`

### Handling Modifications to Source Code:

#### **MIT License:**
- **Modifying the Source Code:** You **can** modify the source code.
- **Sharing the Source Code:** You are **not required** to share your modified source code. You can distribute it under the same or a different license.
- **Usage:** The MIT License is permissive, allowing for modification, redistribution, and commercial use without the obligation to share modifications or the original source code.

#### **GPL License:**
- **Modifying the Source Code:** You **can** modify the source code.
- **Sharing the Source Code:** If you distribute the modified software, you **must** make the source code available under the same GPL license.
- **Usage:** The GPL enforces a "copyleft" rule, requiring that distributed modified versions also have their source code available under the GPL. If modifications are kept private, there's no requirement to share the source code.

### License Checksum
- **LIC_FILES_CHKSUM**: Verifies the integrity of the license file.
  ```sh
  LIC_FILES_CHKSUM = "file://${COREBASE}/meta/files/common-licenses/LICENSE_FILE;md5=<checksum>"
  ```

---

## B. **Development Tasks**

### Core Functions
- **`do_fetch()`**: Fetches source files. Use `SRC_URI=""` to specify the source location, typically downloaded into the `DL` (Download) folder.
- **`SRCREV=""`**: Defines the commit hash when fetching from a Git repository.
- **`do_unpack()`**: Unpacks the source files into the `WORKDIR`.
- **`do_patch()`**: Applies patches to the source files.
- **`do_configure()`**: Configures the software for compilation.
- **`do_compile()`**: Compiles the source code.
- **`do_install()`**: Installs the compiled binaries and other files.

### Overriding Default Implementations
You can override the default tasks using two main methods:
1. **Shell Commands**: Utilize standard shell commands or scripts.
2. **Python Functions**: Define tasks using Python.
   ```python
   python do_compile() {
       # Python code here
   }
   ```

---

## C. **Variables**

### Global Variables
All variables in Yocto are global, with two types of assignment:
1. **Direct Assignment**: Set variables directly.
2. **Script-Based Assignment**: Variables within scripts can be local to that script.

#### Example:
```sh
vim /home/mina/yocto/poky/meta/conf/bitbake.conf

PN = "${@bb.parse.vars_from_file(d.getVar('FILE', False), d)[0] or 'defaultpkgname'}"
PV = "${@bb.parse.vars_from_file(d.getVar('FILE', False), d)[1] or '1.0'}"
PR = "${@bb.parse.vars_from_file(d.getVar('FILE', False), d)[2] or 'r0'}"
```
- Changing these variables locally in `.bb` files does not overwrite the global values, only within the layer.

### Retrieving Local Variables:
- To get the local variable of a layer:
  ```sh
  bitbake-getvar -r <recipe> PV
  ```

---

## D. **Important Files in Yocto**

### **documentation.conf**
- Contains explanations for all variables, helping to understand their usage.
  ```sh
  BBPATH[doc] = "Used by BitBake to locate .bbclass and configuration files. This variable is analogous to the PATH variable."
  ```
- Defines the path where BitBake searches for classes and configuration files.

### **layer.conf**
- Contains configuration specific to a Yocto layer, such as paths, dependencies, and other settings.

## E. Layer types in Yocto

In Yocto, layers are a key part of organizing and managing the build system. They allow you to modularize your build environment, making it easier to manage and reuse components. Here's a breakdown of the layer types and their roles, especially focusing on BSP (Board Support Package) layers and how they integrate with other layers like application layers.

### Layer Types in Yocto

1. **BSP Layer (Board Support Package Layer):**
   - **Purpose:** BSP layers provide the necessary configuration and support for specific hardware platforms. They define machine configurations, kernel configurations, bootloader settings, and other hardware-specific details.
   - **Typical Contents:**
     - **`conf/machine/*.conf`:** This directory contains machine configuration files. These files define machine-specific settings like the architecture, kernel, bootloader, and other hardware-specific options.
     - **Kernel Recipes (`recipes-kernel/linux/*.bb`):** These recipes define how to fetch, configure, compile, and install the Linux kernel for the specific hardware.
     - **Device Tree Blobs (`recipes-bsp/u-boot/*.bb`, `recipes-bsp/device-tree/*.bb`):** These are used for hardware configuration at boot time.

2. **Application Layer:**
   - **Purpose:** Application layers are used to include user-space applications and libraries. These layers contain the recipes for software that runs on top of the operating system, such as utilities, tools, and application software.
   - **Typical Contents:**
     - **`recipes-*/*.bb`:** Recipes for building applications and libraries.
     - **`files/`:** Patches, configuration files, and other resources required by the application recipes.

### Defining Machine in `.conf` Files

In a BSP layer, you define the machine in a `.conf` file located under `conf/machine/`. For example, for the QEMU machine, you might have a file like `qemuarm.conf` with the following content:

```conf
# Machine configuration for qemuarm
SOC_FAMILY = "cortexa9"

PREFERRED_PROVIDER_virtual/kernel = "linux-yocto"
PREFERRED_PROVIDER_virtual/bootloader = "u-boot"
PREFERRED_PROVIDER_virtual/libc = "glibc"

MACHINE_FEATURES = "rtc usbgadget usbhost"
```

This configuration defines which kernel, bootloader, and other machine-specific settings should be used when building for this particular machine.

### Integrating Kernel Modules in `.bb` Files

To integrate kernel modules, you would typically create a recipe in the BSP layer that compiles and installs the module. Here’s an example of how a kernel module might be defined in a `.bb` file:

```bb
DESCRIPTION = "Example Kernel Module"
LICENSE = "GPL-2.0"
SRC_URI = "file://example_module.c"

inherit module

KERNEL_MODULE_PROBENAME = "example_module"

do_compile() {
    oe_runmake
}

do_install() {
    install -d ${D}${nonarch_base_libdir}/modules/${KERNEL_VERSION}/extra
    install -m 0644 example_module.ko ${D}${nonarch_base_libdir}/modules/${KERNEL_VERSION}/extra/
}

FILES_${PN} = "${nonarch_base_libdir}/modules/${KERNEL_VERSION}/extra/example_module.ko"
```

This example shows a basic recipe for compiling and installing a kernel module.

### Layer Organization

You have the flexibility to organize your layers as you see fit:

1. **Separate Layers:**
   - **Advantages:** Keeps BSP and application layers modular and clean. This is especially useful when you are working with multiple hardware platforms or when you want to share a BSP layer across multiple projects.
   - **Disadvantages:** Might add complexity in terms of managing multiple layers.

2. **Combined Layers:**
   - **Advantages:** Easier to manage if your project is small or if the BSP and application layers are tightly coupled.
   - **Disadvantages:** Reduces reusability and modularity, making it harder to manage as the project grows or if you need to support multiple hardware platforms.

### Example: QEMU Machine and Application Layer

For the default QEMU machine, you might have the following structure:

- **BSP Layer:**
  - `meta-qemu-bsp/`
    - `conf/machine/qemuarm.conf`
    - `recipes-kernel/linux/linux-yocto.bb`
    - `recipes-bsp/u-boot/u-boot-qemu.bb`

- **Application Layer:**
  - `meta-qemu-apps/`
    - `recipes-apps/hello-world/hello-world.bb`
    - `recipes-apps/example/example.bb`

### Conclusion

Whether you choose to separate the BSP and application layers or combine them into a single layer depends on your project's needs. For most complex projects, keeping them separate is generally recommended for better modularity and reusability. The `.conf` files in the BSP layer will define the machine configurations, while the `.bb` files in the respective layers will handle the kernel modules, applications, and other components.