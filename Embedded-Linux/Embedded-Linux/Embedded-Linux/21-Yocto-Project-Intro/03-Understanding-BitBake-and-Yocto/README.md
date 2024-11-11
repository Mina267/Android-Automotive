# Understanding BitBake and Yocto

When working with a software package, the typical steps are:

1. **Download (clone) the software.**
2. **Unpack the software.**
3. **Configure the software.**
4. **Build the software.**
5. **Install the software.**

In Yocto, these steps translate into the recipe (`.bb` file) instructions for BitBake. The main steps for a BitBake recipe are:

1. **Fetching:** Downloading the source code.
2. **Unpacking:** Extracting the source code.
3. **Patching:** Applying any necessary patches.
4. **Configuring:** Preparing the build configuration.
5. **Building:** Compiling the source code.
6. **Installing:** Installing the compiled binaries.
7. **Packaging:** Creating installable packages.

Each step in the Yocto build process corresponds to a specific function in the recipe:

- `do_fetch()`: Fetches the source code.
- `do_unpack()`: Unpacks the source code.
- `do_patch()`: Applies patches.
- `do_configure()`: Configures the build.
- `do_compile()`: Compiles the source code.
- `do_install()`: Installs the binaries.

These functions are executed in specific directories:

- **Source Directory (S):** Where fetching, unpacking, patching, and configuring occur.
- **Build Directory (B):** Where building happens.
- **Destination Directory (D):** Where installation happens.

## Packaging Options

There are two main packaging options:

1. **Image:** Packages without debugging symbols, used for deployment.
2. **SDK (Software Development Kit):** Packages with debugging symbols, used for development and debugging.

## Recipe Structure

A recipe file (`.bb` file) contains variables and functions written in the BitBake syntax. Here's an example of a simple recipe:

```plaintext
SUMMARY = "MyApp"
DESCRIPTION = "Description of MyApp"
HOMEPAGE = "http://myapp.com"
LICENSE = "MIT"
SRC_URI = "http://myapp.com/download/myapp-${PV}.tar.gz"
S = "${WORKDIR}/myapp-${PV}"

do_compile() {
    oe_runmake
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 myapp ${D}${bindir}
}
```

## Variables in BitBake

There are two types of variables:

1. **Local Variables:** Defined within `.bb`, `.bbappend`, or `.bbclass` files.
2. **Global Variables:** Defined within `conf` files and are accessible across the entire build system.

## Example: Cloning Poky

To start with Yocto, clone the Poky repository:

```bash
git clone -b kirkstone git://git.yoctoproject.org/poky.git
```

## Example: Using a Global Variable

Define a global variable in `conf/local.conf`:

```plaintext
MYVAR = "Hello, Yocto!"
```

Retrieve it using the `bitbake-getvar` command:

```bash
bitbake-getvar MYVAR
```

This will search through all `conf` files for `MYVAR` and return its value.

## Further Reading

For more detailed information, refer to the Yocto Project documentation:

[Yocto Project Documentation](https://docs.yoctoproject.org)

This documentation covers all aspects of using BitBake and Yocto, including writing recipes, configuring builds, and more.