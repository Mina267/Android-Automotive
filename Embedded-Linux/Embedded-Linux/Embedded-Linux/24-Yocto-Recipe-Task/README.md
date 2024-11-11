
# Yocto Project: Creating a New Layer and Recipe

## 1. Create a New Layer

First, we need to create a new layer for our customizations.

### 1.1 Source the Build Environment

Make sure you are in the correct path, `~/yocto/poky/build`, and source the build environment:

```bash
source oe-init-build-env
```

### 1.2 Create the Layer

Use BitBake to create the layer structure:

```bash
bitbake-layers create-layer ../../meta-iti
```

This command will create the basic template for your layer, including `conf`, `classes`, `recipes`, and other necessary directories.

### 1.3 Add the Layer to `bblayers.conf`

To add the new layer to your build configuration, run:

```bash
bitbake-layers add-layer ../../meta-iti
```

Alternatively, you can manually edit `bblayers.conf`:

```bash
BBLAYERS += "${BSPDIR}/meta-iti"
```

Verify the layer is added:

```bash
bitbake-layers show-layers
```

## 2. Adding a License to a Recipe

Define the license and its checksum in your recipe:

```bash
LICENSE = "MIT"
```

### 2.1 Specify the Source Revision

If fetching from a Git repository, specify a particular commit:

```bash
SRCREV = "b6910bec11614980a21e46fbccc35934b671bd81"
```

### 2.2 Generate the Checksum for the License File

Use the `md5sum` command on the license file to generate the checksum:

```bash
md5sum <license_file>
```

Example:

```bash
md5sum ~/yocto/poky/meta/files/common-licenses/MIT
```

Output:

```bash
0835ade698e0bcf8506ecda2f7b4f302  MIT
```

Add the checksum to your recipe:

```bash
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/files/common-licenses/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"
```

## 3. Adding a GitHub App as a Source

Add the following to your recipe to use a GitHub repository as the source:

```bash
SRC_URI = "git://https://github.com/FadyKhalil/DemoApp.git;protocol=https;branch=main"
SRCREV = "720c663c5fd7246b4b42c5205d74db7d9784b5b2"
```

## 4. Paths in the Build Directory

For debugging, you can expand the environment:

```bash
bitbake -e demo > ~/yocto/expand
```

Here are some useful paths:

- **WORKDIR:** `/home/mina/yocto/poky/build/tmp/work/cortexa57-poky-linux/demo/0.1-r0`
- **S:** `/home/mina/yocto/poky/build/tmp/work/cortexa57-poky-linux/demo/0.1-r0/git`
- **D:** `/home/mina/yocto/poky/build/tmp/work/cortexa57-poky-linux/demo/0.1-r0/image`
- **B:** `/home/mina/yocto/poky/build/tmp/work/cortexa57-poky-linux/demo/0.1-r0/build`

## 5. Example Recipe

Below is an example of a BitBake recipe:

```python
SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"

python do_display_banner() {
    bb.plain("***********************************************");
    bb.plain("*                                             *");
    bb.plain("*  demo recipe created by bitbake-layers      *");
    bb.plain("*                                             *");
    bb.plain("***********************************************");
}

addtask display_banner before do_build

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "git://github.com/FadyKhalil/DemoApp.git;protocol=https;branch=main"
SRCREV = "720c663c5fd7246b4b42c5205d74db7d9784b5b2"

S = "${WORKDIR}/git"

inherit cmake

do_configure() {
    cmake -S ${S} -B ${B}
}

do_compile() {
    oe_runmake -C ${B}
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${B}/calculator ${D}${bindir}
}
```

## 6. Cleaning and Building the Recipe

To clean all build artifacts of the recipe:

```bash
bitbake -c cleanall demo
```

To build the recipe:

```bash
bitbake demo
```
<br>

---

<br>



<p align="center">
	<img src="https://github.com/user-attachments/assets/0c8d5e28-d5d4-4cfc-a1bd-1ad4876a9ac6" width=85% height=85% />
</p>

<p align="center">
	<img src="https://github.com/user-attachments/assets/ed86b594-30b5-4944-a879-a26b29b84ce1" width=85% height=85% />
</p>

<p align="center">
	<img src="https://github.com/user-attachments/assets/7a7590bc-f8da-4519-9cc6-a7ad68970074" width=85% height=85% />
</p>

<p align="center">
	<img src="https://github.com/user-attachments/assets/f8c7e18f-48b1-46f6-badf-83c51223ee97" width=85% height=85% />
</p>

<p align="center">
	<img src="https://github.com/user-attachments/assets/1ed08c0f-636b-4bb3-a703-cf9c0549670f" width=85% height=85% />
</p>


<p align="center">
	<img src="https://github.com/user-attachments/assets/e5b6c002-1d48-4583-bcc6-a92637aba4d6" width=85% height=85% />
</p>




