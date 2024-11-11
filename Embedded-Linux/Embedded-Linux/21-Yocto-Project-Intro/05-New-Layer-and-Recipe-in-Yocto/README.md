#  Creating and Adding a New Layer and Recipe in Yocto


### Key Concept: Why Create a New Layer?

When adding a new package or creating a new recipe, you should not modify existing layers directly within the OpenEmbedded or Poky directories. Instead, always create a new layer for your custom modifications. This ensures your changes are organized and maintainable.

---

## Step 1: Creating a New Layer

**1.1 Understand Layer Structure:**
Start by examining the structure of existing layers in Poky. For instance, look inside the `meta-core` layer to understand the typical organization:
- `classes/`
- `conf/`
- `files/`
- `recipes/`

**1.2 Create Your Directory:**
Create a new directory outside of Poky for your layer. For example:
```bash
mkdir ../meta-iti
```
This directory will contain your custom layer.

**1.3 Using BitBake to Create Layer:**
Instead of manually creating all the necessary files and directories, use BitBake's `bitbake-layers` command to generate the layer structure:
```bash
cd /path/to/your/poky/build
bitbake-layers create-layer ../../meta-iti
```
This command will create the basic template for your layer, which includes `conf`, `classes`, `recipes`, and other necessary directories.

---

## Step 2: Setting Up Layer Variables

**2.1 Understanding BBPATH:**
The `BBPATH` variable defines the hierarchy of layers. It's essential to follow the correct directory structure to ensure BitBake can locate your recipes.

**2.2 Directory Structure:**
Create directories following the standard structure:
```bash
../meta-iti/
    ├── conf/
    │   └── layer.conf
    ├── classes/
    ├── recipes-example/
    │   └── example/
    │       └── example_0.1.bb
```
Ensure that `recipes-example/` follows the pattern: `recipes-<package>/*/*.bb`.

**2.3 Configuring layer.conf:**
Edit `layer.conf` in the `conf` directory to define your layer's metadata and paths. Here is an example:
```bash
# meta-iti/conf/layer.conf

# This file Give Full description of the layer.
# We have a conf and classes directory, add to BBPATH
BBPATH .= ":${LAYERDIR}"

# Explain how to find your recipes inside your layer.
# We have recipes-* directories, add to BBFILES
BBFILES += "${LAYERDIR}/recipes-*/*/*.bb \
            ${LAYERDIR}/recipes-*/*/*.bbappend"

# Add a different path for recipes to change the default hierarchy.
BBFILES:append = " ${LAYERDIR}/mina-*/*.bb"

BBFILE_COLLECTIONS += "meta-iti"
BBFILE_PATTERN_meta-iti = "^${LAYERDIR}/"
BBFILE_PRIORITY_meta-iti = "6"

# The layers that the current layer depends on.
LAYERDEPENDS_meta-iti = "core"
# Version of Yocto Poky that layer is compatible with.
LAYERSERIES_COMPAT_meta-iti = "kirkstone"

```

---

## Step 3: Writing the Recipe

**3.1 Creating a .bb File:**
Within your layer, create a recipe file, for example, `example.bb`, following the template structure provided by BitBake. This file will contain the metadata and instructions for building your package.

**3.2 Example Recipe:**
Here's a simple example of what `example.bb` might look like:
```bash
# meta-iti/recipes-example/example/example_0.1.bb

SUMMARY = "Example Recipe"
DESCRIPTION = "This is an example recipe to demonstrate how to create a new recipe in Yocto."
LICENSE = "MIT"
SRC_URI = "file://example-source.tar.gz"

S = "${WORKDIR}/example-source"

do_compile() {
    echo "Compiling the example source"
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 example ${D}${bindir}
}
```

In this example, `SRC_URI` points to a source tarball, `example-source.tar.gz`, that should be placed in the `files` directory of your recipe.

---

## Step 4: Making BitBake Aware of Your Layer

**4.1 Editing conf/bblayers.conf:**
To ensure BitBake recognizes your new layer, you need to add the layer path to `conf/bblayers.conf`. This file is usually found in the build environment directory (e.g., `build/conf`).

**4.2 Adding Your Layer:**
Use the `bitbake-layers add-layer` command to add your layer:
```bash
cd /path/to/your/poky/build
bitbake-layers add-layer ../../meta-iti
```
This will modify `conf/bblayers.conf` to include your new layer.

**4.3 Handling Dependencies:**
If your new layer depends on another layer, such as `meta`, ensure this dependency is correctly specified in `conf/layer.conf`:
```bash
# meta-iti/conf/layer.conf

LAYERDEPENDS_iti = "core"
LAYERSERIES_COMPAT_iti = "kirkstone"
```

---

## Step 5: Running BitBake

**5.1 Building Your Recipe:**
After setting up your layer and recipe, run BitBake to build your new package:
```bash
bitbake example
```
Ensure that BitBake can locate and build your new recipe.

**5.2 Troubleshooting:**
If BitBake fails to find your recipe, check the following:
- The layer path is correctly added to `conf/bblayers.conf`.
- The directory structure follows the correct hierarchy.
- All necessary files and configurations are in place.

---

## Example Workflow

Here’s a complete workflow example for creating a new layer and recipe:

1. **Create Layer Directory:**
    ```bash
    cd /path/to/your/poky
    bitbake-layers create-layer ../meta-iti
    ```

2. **Configure layer.conf:**
    ```bash
    # Edit ../meta-iti/conf/layer.conf
    ```

3. **Create Recipe Directory and File:**
    ```bash
    mkdir -p ../meta-iti/recipes-example/example
    touch ../meta-iti/recipes-example/example/example_0.1.bb
    ```

4. **Write the Recipe:**
    ```bash
    # Edit ../meta-iti/recipes-example/example/example_0.1.bb
    ```

5. **Add Layer to Build Configuration:**
    ```bash
    cd /path/to/your/poky/build
    bitbake-layers add-layer ../../meta-iti
    ```

6. **Build the Recipe:**
    ```bash
    bitbake example
    ```

