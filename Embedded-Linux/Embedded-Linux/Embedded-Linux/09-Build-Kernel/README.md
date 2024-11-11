# Installing the Linux Kernel

## 3.1. Download Linux Kernel

In this example, we will use the Qemu emulator (Vexpress A9).

1. Clone the Linux kernel repository:

```sh
git clone --depth=1 git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git
```

- `git clone`: This is the command to clone a Git repository.
- `--depth=1`: This option specifies that only the latest commit and its associated files should be cloned. This can be useful when you are only interested in the latest state of the repository and don't need the entire history. The number '1' indicates the depth of the clone.
- `git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git`: This is the URL of the Kernel repository we want to clone.

2. Change directory to the Linux source:

```sh
cd linux
```

### Configure the Kernel for a Specific Target (Vexpress A9)

1. Set the cross-compiler:

```sh
export CROSS_COMPILE=~/x-tools/arm-cortexa9_neon-linux-musleabihf/bin/arm-cortexa9_neon-linux-musleabihf-
```

2. Set the architecture type:

```sh
export ARCH=arm
```

3. Configure the kernel for the Vexpress A9 target:

```sh
make vexpress_defconfig
```

If you encounter an error at this stage, make sure the cross-compiler and architecture are correctly set.

### 3.2. Linux Kernel Configuration

You can customize your kernel image as needed:

1. Run `make menuconfig` to open the kernel configuration menu:

```sh
make menuconfig
```

#### devtmpfs

1. Select `Device Drivers`.
2. Select `Generic Driver Options`.
3. Do not Enable `Automount devtmpfs` configuration.

#### Change Kernel Compression to XZ

1. Select `General Setup`.
2. Select `Kernel Compression Mode`.
3. Choose `XZ` and press `Enter` (don't forget to save).

#### Change Kernel Local Version

1. Select `General Setup`.
2. Select `Local Version - Append to Kernel Release`.
3. Enter your name and version (e.g., `Mina_Kernel.v1`) and save.

### Build the Kernel Configuration

1. Run the following command to build the kernel image, modules, and device tree blobs:

```sh
make -j4 zImage modules dtbs
```

- `-j4`: This option specifies the number of parallel jobs to run during the build process. `-j4` indicates that the build system should use 4 parallel jobs to speed up the compilation. Using multiple jobs in parallel can significantly reduce the time it takes to build the kernel. 

To determine the number of cores on your computer, use:

```sh
lscpu
```

2. If you encounter errors related to missing GMP or MPC headers, install the necessary development packages:

```sh
sudo apt-get install libgmp-dev
sudo apt-get install libmpc-dev
```

### Verify the Kernel Build

1. Check the built kernel image:

```sh
make kernelrelease
```


By following these steps, you will successfully configure, build, and customize the Linux kernel for the Vexpress A9 using Qemu. The instructions include handling common errors and ensuring the necessary packages are installed for a smooth build process.
