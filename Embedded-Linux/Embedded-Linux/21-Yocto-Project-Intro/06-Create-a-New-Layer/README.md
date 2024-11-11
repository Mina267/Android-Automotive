
## 1. Create a New Layer

First, we need to create a new layer for our customizations.

1. **Source the Build Environment:**

    ```bash
    source oe-init-build-env
    ```
* your current path is ~/yocto/poky/build
2. **Create the Layer:**

    ```bash
    bitbake-layers create-layer ../../meta-iti
    ```

3. **Add the Layer to `bblayers.conf`:**

    ```bash
    bitbake-layers add-layer ../../meta-iti
    ```

    Verify the layer is added:

    ```bash
    bitbake-layers show-layers
    ```

## 2. Add Custom Variable to `local.conf`

Edit `conf/local.conf` to add the custom variable:

```bash
MY_CUSTOM_VAR ?= "1"
```

## 3. Write a `.bbappend` File

We will append to an existing recipe with a `.bbappend` file in our new layer. For this example, let's assume we are appending to a recipe called `example`.

1. **Navigate to the layer directory:**

    ```bash
    cd meta-iti
    ```

2. **Create the necessary directories and file:**

    ```bash
    mkdir -p recipes-example/example
    cd recipes-example/example
    touch example_0.1.bbappend
    ```

3. **Edit the `example_0.1.bbappend` file:**

    ```bash
    nano example_0.1.bbappend
    ```

    Add the following content:

    ```python
    python () {
        value_var = d.getVar('MY_CUSTOM_VAR')
        if value_var == "0":
            d.appendVar('do_banner_display', '\necho "Mina"')
        elif value_var == "1":
            d.appendVar('do_banner_display', '\necho "Hello world"')
    }
    ```

    Here, `do_banner_display` is the task in the original recipe we want to modify.

## 4. Include the Layer in `bblayers.conf`

Ensure the layer is included in your `conf/bblayers.conf`:

```bash
bitbake-layers show-layers
BBLAYERS += "${BSPDIR}/meta-iti"
```

## 5. Build the Example

Navigate to the build directory and run the build:

```bash
bitbake example
```

## Verification

After the build process completes, verify that the output includes the modified behavior based on the value of `MY_CUSTOM_VAR`.

## Summary

1. **Create a new layer:**

    ```bash
    bitbake-layers create-layer meta-iti
    ```

2. **Add the layer to `bblayers.conf`:**
* it's mandatory when you add a new layer to be in `/poky/build_enviroment` folder
    ```bash
    bitbake-layers add-layer ../../meta-iti/
    ```

3. **Add custom variable to `conf/local.conf`:**

    ```bash
    MY_CUSTOM_VAR ?= "1"
    ```

4. **Create a `.bbappend` file to modify an existing recipe:**

    ```bash
    python () {
        value_var = d.getVar('MY_CUSTOM_VAR')
        if value_var == "0":
            d.appendVar('do_banner_display', '\necho "Mina"')
        elif value_var == "1":
            d.appendVar('do_banner_display', '\necho "Hello world"')
    }
    ```

5. **Build the example:**

    ```bash
    bitbake example
    ```
