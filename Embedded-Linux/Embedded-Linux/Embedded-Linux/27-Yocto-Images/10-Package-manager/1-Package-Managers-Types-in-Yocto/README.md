# Package Managers types in Yocto

**Package managers** are tools that automate the process of installing, upgrading, configuring, and removing software packages. They also manage dependencies, ensuring that all required packages are installed together.

In the context of Yocto, **package managers** play a crucial role both during the build process and when the system is running.

### 1. **Role of Package Managers in Yocto**

In Yocto, the package manager is responsible for creating, managing, and installing the packages that make up the final root filesystem. During the build process, Yocto generates packages in the format specified by the package manager you choose, such as IPK, RPM, or DEB.

**Key Points**:
- **Packaging**: Yocto builds software and splits it into packages (like IPK, RPM, or DEB) based on the configuration. These packages include binaries, libraries, configuration files, etc.
- **Dependency Management**: The package manager ensures that all dependencies for a package are included in the image, which is crucial for the system's stability.
- **Root Filesystem Construction**: The root filesystem (`rootfs`) is constructed by installing these packages into a temporary directory (`D`), which is later used to create the final image.

### 2. **Common Package Managers in Yocto**

- **IPK**: 
  - **Used By**: OpenEmbedded-based systems, like OpenWRT.
  - **Role**: IPK is lightweight and is often used in embedded systems due to its small footprint. It's based on the Debian package format but is more suitable for embedded devices.
  - **When Running**: On a running system, `opkg` is the package manager typically used with IPK packages to install, upgrade, or remove packages.

- **RPM**:
  - **Used By**: Distributions like Fedora, CentOS, and RHEL.
  - **Role**: RPM is a robust package management system suitable for larger distributions. It's used in Yocto when a more feature-rich package manager is needed.
  - **When Running**: `rpm` is the command-line utility used to manage RPM packages. It offers more advanced features like database management and scripting support.

- **DEB**:
  - **Used By**: Debian-based distributions like Ubuntu.
  - **Role**: DEB packages are widely used in desktop and server environments. Yocto can generate DEB packages if you're targeting a Debian-like environment.
  - **When Running**: `dpkg` or `apt-get` are the utilities used to manage DEB packages on a running system, providing a user-friendly interface for package management.

### 3. **How Yocto Decides Which Package Manager to Use**

The choice of package manager in Yocto is determined by the `PACKAGE_CLASSES` variable in your `distro.conf` or `local.conf` file. 

- **Example**:
  ```bash
  PACKAGE_CLASSES = "package_ipk"
  ```
  or
  ```bash
  PACKAGE_CLASSES = "package_rpm package_deb"
  ```

- This variable tells Yocto which package format(s) to generate. You can specify one or more package classes, and Yocto will create packages in those formats.

### 4. **Role of the Package Manager When the System is Running**

Once the system is built and running:

- **Installing Software**: The package manager (`opkg` for IPK, `rpm` for RPM, or `dpkg/apt` for DEB) is used to install additional software packages that weren't included in the original image.
- **Upgrading Software**: You can use the package manager to upgrade existing software to newer versions.
- **Removing Software**: The package manager can remove installed software, ensuring that all associated files and dependencies are handled properly.
- **Managing Dependencies**: It resolves dependencies automatically when installing or removing packages, ensuring system stability.

### 5. **Summary**

- **IPK, RPM, and DEB** are package formats used by different systems, and Yocto can generate any of these based on your configuration.
- **Yocto** uses the package manager to package the built software into installable units during the build process.
- On a **running system**, the package manager handles the installation, upgrading, and removal of software packages, managing dependencies and ensuring that the system remains stable and functional.

