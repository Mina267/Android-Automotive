
## 1. Create a New Layer

First, we need to create a new layer for our customizations.

1. **Source the Build Environment:**

    ```bash
    source oe-init-build-env
    ```
* your curent path should be `~/yocto/poky/build`
2. **Create the Layer:**

    * Using BitBake to Create Layer:
    Instead of manually creating all the necessary files and directories, use BitBake's `bitbake-layers` command to generate the layer structure:
    ```bash
    bitbake-layers create-layer ../../meta-iti
    ```
    This command will create the basic template for your layer, which includes `conf`, `classes`, `recipes`, and other necessary directories.

    ---

3. **Add the Layer to `bblayers.conf`:**

    ```bash
    bitbake-layers add-layer ../../meta-iti
    ```
    or
    ```bash
    BBLAYERS += "${BSPDIR}/meta-iti"
    ```

    Verify the layer is added:

    ```bash
    bitbake-layers show-layers
    ```

## 2. Add Custom Variable to `local.conf`

Edit `conf/local.conf` to add the custom variable:

```bash
MINA_GLOBAL_VARIABLE ?= "1"
```

```bash
# This file Give Full description of the layer.
# We have a conf and classes directory, add to BBPATH
BBPATH .= ":${LAYERDIR}"

# Explain how to find your recipes inside your layer.
# We have recipes-* directories, add to BBFILES
BBFILES += "${LAYERDIR}/recipes-*/*/*.bb \
            ${LAYERDIR}/recipes-*/*/*.bbappend"

# Add a different path for recipes to change the default hierarchy.
BBFILES:append = " ${LAYERDIR}/mina-*/*/*.bb"
BBFILES:append = " ${LAYERDIR}/mina-*/*/*.bbappend"


MINA_GLOBAL_VARIABLE = "1"

BBFILE_COLLECTIONS += "meta-iti"
BBFILE_PATTERN_meta-iti = "^${LAYERDIR}/"
BBFILE_PRIORITY_meta-iti = "6"

# The layers that the current layer depends on.
LAYERDEPENDS_meta-iti = "core"
# Version of Yocto Poky that layer is compatible with.
LAYERSERIES_COMPAT_meta-iti = "kirkstone"


```


## 3. Write a `.bb` File


1. **Navigate to the layer directory:**

    ```bash
    cd meta-iti
    ```

3. **Edit the `touch mina_1.0.bb` file:**

    ```bash
    vim mina_1.0.bb
    ```

    Add the following content:

    ```python
    SUMMARY = "bitbake-layers recipe"
    DESCRIPTION = "Recipe created by bitbake-layers"
    LICENSE = "MIT"

    python do_display_banner() {
        bb.plain("***********************************************");
        bb.plain("*                                             *");
        bb.plain("*  Mina recipe created by iti-layers          *");
        bb.plain("*                                             *");
        bb.plain("***********************************************");

        var = d.getVar('MINA_GLOBAL_VARIABLE')
        if var == "0":
            bb.plain("Hi Welcome to iti-layer")
        elif var == "1":
            bb.plain("Hi Welcome Mina")

    }

    addtask display_banner before do_build

    ```

## 6. Build the mina recipe

Navigate to the build directory and run the build:

```bash
bitbake mina
```

## Verification

After the build process completes, verify that the output includes the modified behavior based on the value of `MINA_GLOBAL_VARIABLE`.


<p align="center">
	<img src="https://github.com/user-attachments/assets/c295c0e4-6b82-4793-a016-535c484c8b21" width=85% height=85% />
</p>

<p align="center">
	<img src="https://github.com/user-attachments/assets/c32ddd8d-4bb6-49e0-914c-47f71bde96c3" width=85% height=85% />
</p>
