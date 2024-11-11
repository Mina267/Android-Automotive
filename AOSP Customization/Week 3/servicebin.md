The path where a binary like `ledservice` is installed is determined by the `cc_binary` build rule in `Android.bp` and the specific `installable` attribute. By default, binaries can be placed in different partitions, with the most common being `/system/bin` or `/vendor/bin`, depending on the build configuration and the module type. Here’s how you can determine where `ledservice` will end up:

### 1. **Understanding the `cc_binary` Rule Configuration**

The `cc_binary` rule in `Android.bp` specifies the properties of the binary being built. In this case, `installable: true` ensures that `ledservice` will be installed on the target device. However, the exact destination depends on the **build configuration** (e.g., device type and partition configuration) and the **Soong build system** rules.

To understand this better:
   - **System Partitions**: If the module is defined in the core AOSP source (e.g., under `frameworks` or `system`), it will likely be installed to `/system/bin`.
   - **Vendor Partitions**: If the module is in device-specific directories, such as `device/`, `hardware/`, or `vendor/`, it will likely be installed in `/vendor/bin`.

### 2. **Specify the Partition Explicitly**

If you want to specify the exact partition, you can use the `vendor: true` or `product_specific: true` tags in `Android.bp`:

- **For `/vendor/bin`**:
    ```bash
    cc_binary {
        name: "ledservice",
        srcs: ["ledservice.cpp"],  
        shared_libs: ["liblog"],    
        stl: "libc++",
        cflags: ["-std=c++17"],
        installable: true,
        init_rc: ["init.led.rc"],
        vendor: true,  # Forces installation to the vendor partition
    }
    ```

- **For `/system/bin`**:
    Remove the `vendor: true` line, and the binary should default to `/system/bin` if the build context places it in the system partition.

### 3. **Checking the Output Directory**

Once you’ve built your AOSP project, you can confirm the actual location of `ledservice` by checking the output directories. After building, navigate to `out/target/product/[device]/` to check the `system/bin` and `vendor/bin` directories for the `ledservice` binary.

### 4. **Examining Build Logs**

You can also inspect the build logs. During the build, Soong will print information about where it installs binaries. Look for `ledservice` in the logs to confirm its target directory.

