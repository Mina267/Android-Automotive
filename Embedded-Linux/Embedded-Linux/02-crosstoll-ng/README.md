
# Crosstool-NG Installation and Configuration




## Clone the Crosstool-NG Repository
First, clone the Crosstool-NG repository from GitHub:
```bash
git clone https://github.com/crosstool-ng/crosstool-ng
cd crosstool-ng
```

## Bootstrap
Run the bootstrap script to set up the build environment:
```bash
./bootstrap
```

## Configure with Local Installation
Configure the build system to install Crosstool-NG locally:
```bash
./configure --enable-local
```

## Compile the Source Code
Compile the Crosstool-NG source code:
```bash
make
```

## Install Crosstool-NG
Install the compiled binaries:
```bash
make install
```

## Initialize Crosstool-NG
Initialize Crosstool-NG by running:
```bash
./ct-ng
```

## List Available Samples
List the available configuration samples to see the available pre-configured toolchain targets:
```bash
./ct-ng list-samples
```

## Select a Sample Configuration
Choose a sample configuration, such as the one for the Cortex-A9:
```bash
./ct-ng cortex-a9
```

## Open Menuconfig
Open the menu configuration interface to customize the toolchain configuration:
```bash
./ct-ng menuconfig
```

## Configure the Toolchain
In the `menuconfig` interface, navigate through the menus and configure the following options:

1. **Select the Library:**
   - Navigate to `C-library` and select the desired C library (e.g., `glibc`, `uClibc`, or `musl`).

2. **Enable GDB:**
   - Navigate to `Debug facilities` and select `gdb` to include GDB in the toolchain.

3. **Enable Strace:**
   - Navigate to `Debug facilities` and select `strace` to include strace in the toolchain.

4. **Enable C++:**
   - Navigate to `Languages` and ensure `C++` support is enabled.

5. **Enable make:**
   - Navigate to `Companion tools` and ensure `make` is selected.

To search for specific configuration options in `menuconfig`, press the forward slash `/` key and type the keyword.

<p align="center">
	<img src="https://github.com/user-attachments/assets/9bab2c5f-83eb-42b4-91bb-160178fdaede" width=75% height=75% />
</p>

<p align="center">
	<img src="https://github.com/user-attachments/assets/7bcb1ef8-da06-4e35-bcc9-ac884b493ce3" width=75% height=75% />
</p>

<p align="center">
	<img src="https://github.com/user-attachments/assets/8491ccdf-80b4-45bf-a618-b648fc5554bf" width=75% height=75% />
</p>

<p align="center">
	<img src="https://github.com/user-attachments/assets/007718a9-a21e-4c13-a856-7db8a486d672" width=75% height=75% />
</p>

## Build the Toolchain
Once you have configured the toolchain to your satisfaction, exit the `menuconfig` interface and save your changes. Then, build the toolchain:
```bash
./ct-ng build
```

This process will take some time as it downloads and builds the necessary components for the toolchain.

## Verify Installation
After the build completes, you can verify the installation and check the toolchain binaries in the specified installation directory.

