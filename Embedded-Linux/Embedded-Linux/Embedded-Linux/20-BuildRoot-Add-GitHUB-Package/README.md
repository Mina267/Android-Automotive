# Creating a New GitHub Package in Buildroot Menuconfig


## Host Machine Setup

### 1. Develop Your Application and Makefile

#### Purpose:
You will create a simple C application and a Makefile to compile it. This application will be packaged and integrated into Buildroot later.

**MinaGithub_package.c:**
```c
#include <stdio.h>

int main() {
    printf("\n*****************************\n");
    printf("* Hello Mina GitHub Package *");
    printf("\n*****************************\n");

    return 0;
}
```
This simple program prints a welcome message.

**Makefile:**
```makefile
TARGET = MinaGithub_package
SRC = MinaGithub_package.c

$(TARGET): $(SRC)
	$(CC) -o $@ $(SRC)

clean:
	-rm -f $(TARGET)
```
This Makefile compiles the C program into an executable named `MinaGithub_package`.

### 2. Create the Tarball

#### Purpose:
To package your application source code and Makefile into a tarball, which will be used later in Buildroot.

Ensure your `MinaGithub_package.c` and `Makefile` are in the same directory, then create a tarball:
```sh
tar -czvf MinaGithub_package-v1.tar.gz MinaGithub_package.c Makefile
```

### 3. Push to GitHub

#### Purpose:
To host your code on GitHub, making it accessible to Buildroot.

Initialize a new Git repository, commit your files, and push them to GitHub:
```sh
git init
git remote add origin https://github.com/Mina267/Package.git
git add .
git commit -m "Initial commit of Mina Package"
git push -u origin master
```

### 4. Get the Commit ID or Tag

#### Purpose:
To provide Buildroot with a specific version of your code to ensure consistency and reproducibility.

#### Understanding Commit IDs and Tags:
- **Commit ID:** A unique identifier for each commit in Git.
- **Tag:** A user-friendly reference to a specific point in the repository's history, often used to mark release points.

#### Why This Matters

If you make additional commits after the initial push, the commit ID or tag you used in your Buildroot package script will no longer point to the latest version of your code. To keep your Buildroot package script up-to-date with the latest code changes, you would have to update the commit ID or tag accordingly.


#### Steps to Get the Commit ID or Tag

**Get the Latest Commit ID:**
```sh
git log -1 | grep ^commit | cut -d " " -f 2
```
This retrieves the most recent commit ID.

**Create and Push a Tag:**
```sh
git tag v1.0.0
git push origin v1.0.0
```
This creates a tag named `v1.0.0` and pushes it to the remote repository.

## Buildroot Setup

### 1. Create Package Directory and Files

#### Purpose:
To set up the necessary files and directory structure for your custom Buildroot package.

1. **Navigate to the Buildroot Package Directory:**
   ```sh
   cd /path/to/buildroot/package
   ```

2. **Create the `MinaGithub_package` Directory:**
   ```sh
   mkdir MinaGithub_package
   cd MinaGithub_package
   ```

3. **Create `MinaGithub_package.mk` and `Config.in` Files:**
   ```sh
   touch MinaGithub_package.mk
   touch Config.in
   ```

### 2. Edit `MinaGithub_package.mk`

#### Purpose:
To define how Buildroot should fetch, build, and install your package.

Open `MinaGithub_package.mk` and add the following content:

**MinaGithub_package.mk:**
```makefile
MINAGITHUB_PACKAGE_VERSION = b2d1cceed5c33274935436b4644fc92763a6636f
# MINAGITHUB_PACKAGE_VERSION = v1.0.0
MINAGITHUB_PACKAGE_SITE = $(call github,Mina267,Package,$(MINAGITHUB_PACKAGE_VERSION))
MINAGITHUB_PACKAGE_LICENSE = GPL-2.0+
MINAGITHUB_PACKAGE_LICENSE_FILES = LICENSE

define MINAGITHUB_PACKAGE_BUILD_CMDS
    $(MAKE) CC="$(TARGET_CC)" LD="$(TARGET_LD)" -C $(@D)
endef

define MINAGITHUB_PACKAGE_INSTALL_TARGET_CMDS
    $(INSTALL) -D -m 0755 $(@D)/MinaGithub_package $(TARGET_DIR)/usr/bin
endef

$(eval $(generic-package))
```
- `MINAGITHUB_PACKAGE_VERSION` specifies the version of your package (either a commit ID or a tag).
- `MINAGITHUB_PACKAGE_SITE` points to your GitHub repository.
- `MINAGITHUB_PACKAGE_BUILD_CMDS` and `MINAGITHUB_PACKAGE_INSTALL_TARGET_CMDS` define the build and install commands.

### 3. Edit `Config.in` in `MinaGithub_package` Directory

#### Purpose:
To define the configuration options for your package in Buildroot.

Open `Config.in` and add the following content:

**Config.in:**
```makefile
config BR2_PACKAGE_MINAGITHUB_PACKAGE
    bool "MinaGithub_package"
    help
      MinaGithub_package package.
```

### 4. Modify the Main `Config.in`

#### Purpose:
To include your package in the Buildroot configuration menu.

Navigate back to the `package` directory and edit the main `Config.in` file to include your package:

**package/Config.in:**
```makefile
menu "MinaGithub_package Packages"
    source "package/MinaGithub_package/Config.in"
endmenu
```

### Building the Image with Your Package

#### Purpose:
To configure and build a Buildroot image that includes your custom package.

1. **Configure Buildroot:**
   ```sh
   make menuconfig
   ```
   Navigate to "Target Packages" -> "Misc" and select "MinaGithub_package". Save and exit.

2. **Build the Image:**
   ```sh
   make
   ```

3. **Rebuild Just the Package:**
   ```sh
   make MinaGithub_package
   make -j4
   ```
   This ensures your package is included in the root filesystem image.

## Summary

1. **Develop your application and Makefile.**
2. **Push your files to GitHub.**
3. **Get the commit ID or tag from GitHub.**
4. **Create the package directory and necessary files in Buildroot.**
5. **Edit the `MinaGithub_package.mk` and `Config.in` files to define your package.**
6. **Include your package in the main `Config.in` file.**
7. **Configure Buildroot to select your package.**
8. **Build the Buildroot image.**

By following these steps, your `MinaGithub_package` will be integrated into the Buildroot system and included in the final filesystem image. This ensures your application is compiled and available in the target system, demonstrating a complete workflow from development to deployment.


<br>

---

<br>



<p align="center">
	<img src="https://github.com/user-attachments/assets/ea5a68d7-c8ce-4d5d-be21-061bdf7b2b33" width=85% height=85% />
</p>
<p align="center">
	<img src="https://github.com/user-attachments/assets/8baa1538-b33b-45ac-bffe-102260ac707e" width=85% height=85% />
</p>
<p align="center">
	<img src="https://github.com/user-attachments/assets/2622c49e-c775-4937-841b-40ebeca26b0c" width=85% height=85% />
</p>
<p align="center">
	<img src="https://github.com/user-attachments/assets/be16bb54-39c6-4365-9e4c-cb7ec0c7a3ed" width=85% height=85% />
</p>
<p align="center">
	<img src="https://github.com/user-attachments/assets/40d2f83c-162a-4b2f-a829-150b869c72ba" width=85% height=85% />
</p>
<p align="center">
	<img src="https://github.com/user-attachments/assets/2bac3e25-89f4-4194-a3c0-70c80f6f6094" width=85% height=85% />
</p>
<p align="center">
	<img src="https://github.com/user-attachments/assets/1b5428f9-6c33-455d-9ea2-97997abe835a" width=85% height=85% />
</p>
<p align="center">
	<img src="https://github.com/user-attachments/assets/c18430ba-e5c3-491e-b45b-73dc1eb59fa1" width=85% height=85% />
</p>
