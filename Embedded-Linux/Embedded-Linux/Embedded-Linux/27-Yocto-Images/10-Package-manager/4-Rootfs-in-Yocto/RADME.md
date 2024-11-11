# Rootfs in Yocto
The `do_rootfs` task in Yocto is responsible for assembling the root filesystem by installing the binary packages (like RPMs) into the appropriate directories based on the package metadata, the Filesystem Hierarchy Standard (FHS), and any specific instructions provided in the recipe or configuration files. Here's a detailed look at how this process works and how the placement of files in directories like `/bin`, `/usr/bin`, `/lib`, `/usr/lib`, `/opt`, and `/etc` is controlled:

### **1. Package Metadata and Control Files**

When the `do_package` task creates RPM packages, it also generates metadata for each package. This metadata includes information about where each file in the package should be installed in the root filesystem. This metadata is crucial because it dictates how `do_rootfs` will install the package.

- **File Lists**: The package's file list specifies the full path where each file should be installed. For example, a file intended for `/usr/bin` will have its path specified as such in the package metadata.
  
- **Post-installation Scripts**: RPM packages may include post-installation scripts (`%post` in RPM spec files) that can move files or perform additional configuration after the files are installed.

### **2. Role of the Filesystem Hierarchy Standard (FHS)**

The FHS provides a set of guidelines for the directory structure and directory contents in Unix-like operating systems, including Linux. When installing files, `do_rootfs` and the package manager adhere to these standards to ensure that:

- **Essential binaries** (`/bin`, `/sbin`): Contain essential command binaries that are required for single-user mode, for system repair, or for booting the system.

- **Non-essential binaries** (`/usr/bin`, `/usr/sbin`): Contain binaries for user applications and non-essential system binaries.

- **Libraries** (`/lib`, `/usr/lib`): Contain shared libraries needed by the binaries in `/bin` and `/sbin` and other non-essential shared libraries.

- **Configuration files** (`/etc`): Contain system-wide configuration files.

- **Optional software** (`/opt`): Contain large, self-contained packages or third-party software that doesn't fit neatly into the `/usr` hierarchy.

### **3. How `do_rootfs` Controls File Placement**

The `do_rootfs` task uses the following mechanisms to control where files are placed:

#### **A. Package Manager and Metadata**
The package manager (RPM in this case) reads the metadata in the RPM package to determine where each file should be placed in the root filesystem. The file paths specified in the RPM metadata directly control where files are installed.

For example:
- If an RPM package has a file list entry like `/usr/bin/myapp`, the package manager will install `myapp` in the `/usr/bin` directory.
- If the metadata specifies `/etc/myapp.conf`, the package manager will place the configuration file in `/etc`.

#### **B. `do_install` Task in Recipes**
The `do_install` task in a recipe is responsible for organizing files into the correct locations within the `D` directory. The structure of `D` mimics the final root filesystem, so if `do_install` places binaries in `${D}/usr/bin`, they will end up in `/usr/bin` in the final image.

For instance, in a recipe:
```bash
do_install() {
    install -d ${D}${bindir}
    install -m 0755 myapp ${D}${bindir}
}
```
Here, `myapp` will be installed into the `${bindir}` directory, which typically maps to `/usr/bin`. This placement then becomes part of the RPM package's file list.

#### **C. Root Filesystem Configuration**
Yocto allows further control over file placement through various configuration variables and scripts:

- **IMAGE_INSTALL**: Specifies which packages should be included in the root filesystem.
  
- **ROOTFS_POSTPROCESS_COMMAND**: A variable that allows running custom commands after the root filesystem is created but before the image is finalized. This can be used to move files or make other adjustments.

- **ROOTFS_DIRS**: Configuration settings can also dictate the creation of specific directories within the root filesystem, ensuring that the appropriate structure is in place.

#### **D. Handling Custom Layouts**
If a package or the system requires a non-standard file layout, you can adjust the installation paths in the `do_install` task or modify the post-processing commands. For example, to place an application in `/opt`, you could explicitly install it there in `do_install`:
```bash
do_install() {
    install -d ${D}/opt/myapp
    install -m 0755 myapp ${D}/opt/myapp
}
```
This would ensure that `myapp` is placed in `/opt/myapp` in the final root filesystem.

### **4. Customizing with `PACKAGE_INSTALL` and `PACKAGE_CLASSES`**

Depending on the selected `PACKAGE_CLASSES` (e.g., `package_rpm`, `package_deb`), the package manager handles the installation differently, but the basic principles of using metadata and respecting the FHS remain consistent.

### **Conclusion**

The `do_rootfs` task in Yocto decides where files are placed in the root filesystem based on the metadata generated during packaging, the FHS, and any specific instructions provided in the recipe or configuration files. The package manager, guided by the metadata in the RPM files, ensures that binaries, libraries, configuration files, and optional software are installed in the correct directories, such as `/bin`, `/usr/bin`, `/lib`, `/usr/lib`, `/opt`, and `/etc`. By using `do_install`, `ROOTFS_POSTPROCESS_COMMAND`, and other configuration variables, you can customize this behavior to suit the needs of your specific embedded system.