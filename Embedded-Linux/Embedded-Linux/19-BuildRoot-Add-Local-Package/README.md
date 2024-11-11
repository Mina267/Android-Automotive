
# Creating a Buildroot Package

### 1. Prepare Your Package Source

**Create Directory Structure:**
```bash
mkdir -p ./package/Mina_package
```
- This command creates the necessary directory for your package.

**Create Source File:**
```bash
vim ./package/Mina_package/mina_app.c
```
- Open a text editor to create the source file for your application.

**Write Simple Multi-threaded Code:**
```c
#include <stdio.h>
#include <pthread.h>

void* print_message(void* threadid) {
    printf("Hello from thread %ld\n", (long)threadid);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[2];
    for (long t = 0; t < 2; t++) {
        pthread_create(&threads[t], NULL, print_message, (void*)t);
    }
    for (long t = 0; t < 2; t++) {
        pthread_join(threads[t], NULL);
    }
    return 0;
}
```
- This simple multi-threaded C program creates two threads that print a message.

---

### 2. Create the Makefile for the Application

**Create Makefile in the `Mina_package` Directory:**
```bash
vim ./package/Mina_package/Makefile
```
- Open a text editor to create the Makefile.

**Add the Following Content to the Makefile:**
```Makefile
.PHONY: clean
.PHONY: mina_app

mina_app: mina_app.c
    $(CC) -pthread -o mina_app mina_app.c

clean:
    -rm -f mina_app
```
- This Makefile compiles the `mina_app.c` file into an executable named `mina_app`.

> **Note**: Ensure that the Makefile uses tab characters for indentation. Spaces will not work.

---

### 3. Create the Buildroot Package Definition

**Create the Package Makefile:**
```bash
vim ./package/Mina_package/mina_package.mk
```
- Open a text editor to create the package Makefile.

**Add the Following Content to `mina_package.mk`:**
```Makefile
###############################################################################
#
# Mina_package
#
################################################################################

MINA_PACKAGE_VERSION = 1.0
MINA_PACKAGE_SITE = package/Mina_package
MINA_PACKAGE_SITE_METHOD = local

define MINA_PACKAGE_BUILD_CMDS
    $(MAKE) CC="$(TARGET_CC)" -C $(@D)
endef

define MINA_PACKAGE_INSTALL_TARGET_CMDS
    $(INSTALL) -D -m 0755 $(@D)/mina_app $(TARGET_DIR)/usr/bin/mina_app
endef

$(eval $(generic-package))
```
- This Makefile defines how to build and install the `Mina_package` package within Buildroot.

---

### 4. Create the Configuration File for Buildroot

**Create Config.in File:**
```bash
vim ./package/Mina_package/Config.in
```
- Open a text editor to create the configuration file.

**Add the Following Content to `Config.in`:**
```Config.in
config BR2_PACKAGE_MINA_PACKAGE
    bool "mina_package"
    help
        A simple multi-threaded application example.
```
- This configuration option allows you to enable the `Mina_package` package from Buildroot's menuconfig.

---

### 5. Integrate the Package into Buildroot Configuration

**Edit the Buildroot Package Configuration:**
```bash
vim ./package/Config.in
```
- Open the main package configuration file.

**Add the Following Content Under Target Packages:**
```Config.in
menu "MINA_PACKAGE Packages"
    source "package/Mina_package/Config.in"
endmenu
```
- This integration step adds a new menu entry for your package in Buildroot's configuration menu.

---

### 6. Configure Buildroot

**Run Menuconfig:**
```bash
cd buildroot
make menuconfig
```
- This command opens the Buildroot configuration menu.

**Enable the Package:**
- Navigate to `Target packages` -> `MINA_PACKAGE Packages`
- Select `mina_package`
    - Use the arrow keys to navigate and the space bar to select.

---

### 7. Build Buildroot

**Build with the Custom Package:**
```bash
make -j8
```
- This command starts the build process with 8 parallel jobs, speeding up the build.

---

### 8. Verify the Build

**Test on QEMU:**
- After the build, boot the image with QEMU to verify the application:
```bash
cd ./output/images 
sudo ./start-qemu.sh
```
- Ensure the `mina_app` executable is in `/usr/bin` and runs correctly.

---

### Conclusion

By following these detailed steps, you've successfully added and integrated a custom package into Buildroot, ensuring it is compiled, installed, and tested efficiently.



<br>


---

<br>

<p align="center">
	<img src="https://github.com/user-attachments/assets/66634685-243c-4627-8d25-0154d7324ead" width=75% height=75% />
</p>




<p align="center">
	<img src="https://github.com/user-attachments/assets/d0f1a3c6-12f0-4171-be5d-e4b180b0f023" width=75% height=75% />
</p>




<p align="center">
	<img src="https://github.com/user-attachments/assets/262a0dd7-77fa-423c-b011-31493cdcff2f" width=75% height=75% />
</p>




<p align="center">
	<img src="https://github.com/user-attachments/assets/2ada2989-b877-42ab-8942-d80fd530e3a7" width=75% height=75% />
</p>



