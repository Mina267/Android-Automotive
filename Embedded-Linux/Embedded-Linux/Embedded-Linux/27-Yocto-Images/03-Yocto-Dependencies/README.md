# Yocto Build-Time Dependencies

### `DEPENDS`
- **Purpose**: Lists a recipe's build-time dependencies, which are other recipes required to build the current recipe.
- **Example**: 
  - **Scenario**: `recipe_calculator.bb` depends on a library built by `recipe_add.bb`.
  - **Implementation**:
    ```bash
    DEPENDS = "recipe_add"
    ```
  - **Effect**: The `recipe_add.bb` will be built first, and its output (e.g., `libadd.a`) will be made available in the working directory of `recipe_calculator.bb` for further use.

### `PROVIDES`
- **Purpose**: Lists aliases that a recipe provides, which can be used by other recipes to satisfy their build-time dependencies.
- **Example**:
  - **Scenario**: `recipe_add.bb` provides the `libadd` alias.
  - **Implementation**:
    ```bash
    PROVIDES = "libadd"
    ```
  - **Usage in Another Recipe**:
    ```bash
    DEPENDS = "libadd"
    ```
  - **Effect**: The `recipe_calculator.bb` depends on `libadd`, and Yocto knows that `recipe_add.bb` satisfies this dependency.

## Yocto Runtime Dependencies

### `RDEPENDS`
- **Purpose**: Lists runtime dependencies that must be present in the target root filesystem for the package to function correctly.
- **Example**:
  - **Scenario**: A package needs Python to run scripts.
  - **Implementation**:
    ```bash
    RDEPENDS_${PN} = "python"
    ```
  - **Effect**: The `python` package will be installed in the target root filesystem automatically, without the need to add it manually to `IMAGE_INSTALL`.

### `RPROVIDES`
- **Purpose**: Lists aliases that a package provides at runtime, which can be used to satisfy runtime dependencies (`RDEPENDS`) of other packages.
- **Example**:
  - **Scenario**: A package provides an alias for another package.
  - **Implementation**:
    ```bash
    RPROVIDES_${PN} = "custom-python"
    ```
  - **Usage in Another Package**:
    ```bash
    RDEPENDS_${PN} = "custom-python"
    ```
  - **Effect**: The package that provides `custom-python` will satisfy the runtime dependency for other packages that list `custom-python` in their `RDEPENDS`.

## Best Practices for Yocto Layer Management

1. **Avoid Direct Modifications to Poky**:
   - Do not modify the recipes or configuration files within the Poky directory, such as `local.conf`. These files should remain untouched to maintain a clean and maintainable build environment.

2. **Create Custom Layers**:
   - For any customizations, create a new layer outside of Poky. This layer will hold your custom recipes, configurations, and extensions.

3. **Utilize Poky Recipes**:
   - Leverage existing Poky recipes by inheriting classes, using `.bbappend` files, or other mechanisms to extend functionality without altering the original recipes.

4. **Customize Configurations**:
   - Add custom machine configurations, distributions, or additional features through your custom layer's `conf` files.

5. **Custom Image Recipes**:
   - If needed, create your own image recipes (e.g., `core-image-minimal.bb`) within your custom layer. This allows users to easily build images with your configurations.

6. **BSP Compatibility**:
   - If your layer includes BSP (Board Support Package) recipes, ensure they are compatible with specific hardware targets. Clearly document any dependencies or requirements for those targets.

These practices help maintain a clean separation between your custom implementations and the core Yocto environment, making your build system more modular and easier to manage.