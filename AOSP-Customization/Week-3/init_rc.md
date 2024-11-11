The `init_rc` property in Soong is used to specify a list of custom `init.rc` files for a module that should be installed alongside the module. When a module (like an app, library, or binary) includes an `init_rc` list, these `init.rc` scripts will automatically be included in the device's system image, allowing the module to configure and manage custom startup behaviors, permissions, or services related to that module. 

Here’s a comprehensive look at what this entails, with examples and scenarios:

---

### **What is `init_rc` in Soong?**

The `init_rc` property in Soong allows you to link specific `init.rc` files to a module. This means that when the module is installed, the `init.rc` files listed in `init_rc` will be installed as well. This is useful when your module requires custom configurations or services that need to be executed at boot or based on system events.

For example:
```plaintext
cc_binary {
    name: "my_custom_service",
    srcs: ["my_custom_service.cpp"],
    init_rc: ["my_custom_service.rc"],
    vendor: true,
}
```
In this case:
- When `my_custom_service` is built and installed on the device, the `my_custom_service.rc` file will also be installed in the appropriate location on the device (e.g., `/vendor/etc/init`).
- The `init.rc` file can then define specific behaviors for this service, such as when to start or stop it, permissions, dependencies, etc.

---

### **Facets of Using `init_rc` with Examples**

#### 1. **Startup Behavior Configuration**
   - You can use `init.rc` files to specify exactly when your module's service should start. Common triggers include boot events, system properties, or even conditions such as file existence.
   - **Example**: Suppose `my_custom_service.rc` should run a custom binary `my_custom_service` at boot time.

     ```plaintext
     # my_custom_service.rc
     service my_custom_service /vendor/bin/my_custom_service
         class main
         user system
         group system
         disabled
         oneshot

     on property:sys.boot_completed=1
         start my_custom_service
     ```
     Here:
     - The service starts only once after the system boot is completed.
     - The `disabled` flag keeps it from starting immediately during the boot sequence.

#### 2. **Permissions and Security**
   - `init.rc` files can define user and group permissions, which is especially useful for services that need elevated permissions or belong to specific security contexts (e.g., for accessing certain files or devices).
   - **Example**: Grant `my_custom_service` elevated permissions to access system resources.

     ```plaintext
     service my_custom_service /vendor/bin/my_custom_service
         class main
         user root
         group system
         seclabel u:r:my_service:s0
     ```
     - **seclabel**: Defines a security label (`seclabel`) using SELinux, which sets the security context for the service.

#### 3. **Inter-Service Dependencies**
   - Some services rely on others to complete initialization. `init.rc` files support defining dependencies and controlling start order.
   - **Example**: Only start `my_custom_service` after another service, `dependency_service`, has started.

     ```plaintext
     on property:init.svc.dependency_service=running
         start my_custom_service
     ```
   - Here, `my_custom_service` will only start when `dependency_service` is confirmed to be running.

#### 4. **Environment Setup and Initialization**
   - `init.rc` files often contain commands for setting up directories, permissions, or other environment variables needed by the module.
   - **Example**: Create directories with specific permissions before starting the service.

     ```plaintext
     on post-fs-data
         mkdir /data/my_service_data 0771 system system
         chmod 0770 /data/my_service_data
     ```
   - This creates a directory that `my_custom_service` can use and ensures that only the system user and group have access.

#### 5. **Trigger-Based Execution**
   - `init.rc` files allow execution based on various triggers beyond just boot, such as property changes or hardware-specific events.
   - **Example**: Start `my_custom_service` when a certain property is set.

     ```plaintext
     on property:my.custom.property=1
         start my_custom_service
     ```
   - This trigger makes it possible to start the service when a custom property is set, which could be controlled by another application or process.

---

### **Using `init_rc` with `cc_binary`, `android_app`, and Other Module Types**

The `init_rc` configuration can be used with various module types, each having different applications:

1. **With `cc_binary`**:
   - Ideal for native binaries, typically used for low-level services or daemons.
   - Custom `init.rc` files can define triggers based on system properties or custom events to control the binary's execution.

2. **With `android_app`**:
   - Though not common, some specialized Android apps may need `init.rc` files if they provide system services or interact with lower-level hardware.
   - For instance, a system-level app providing diagnostic tools might have an associated service started by `init.rc`.

3. **With `android_library` or `java_library`**:
   - Rarely used with `init.rc` since these modules typically don’t run as standalone services.
   - However, if a library is a dependency for a native service or interacts with device hardware, it could theoretically have an `init.rc` for initialization routines.

---

### **Summary and Use Cases**

- **System or Vendor Partition Services**: For essential services that need to run early in the boot process (like networking or hardware monitoring), use `init_rc` in the `system` or `vendor` partition with a service defined in `init.rc` to ensure early availability.
- **Device-Specific Services**: For device-specific functionality (e.g., camera sensors or display services on a particular device model), the `init.rc` can be configured to load device-specific binaries, drivers, or services at boot.
- **Trigger-Based Runtime Control**: For services that don’t need to start at boot but need to react to system conditions or application requests, `init_rc` can specify property-based triggers to control execution based on system properties or external input.

With `init_rc`, you gain fine-grained control over service execution and initialization for each module, creating an efficient, modular, and responsive configuration tailored to the service’s role in the system.


---
---
---



### **Can `cc_binary` Use `init_rc` Directly?**
While `cc_binary` modules are generally just compiled binaries, they don’t independently start on their own during boot or runtime. For a `cc_binary` to be launched or controlled by Android’s `init` system, it needs an `init.rc` file specifying the conditions under which it should start or stop. This is where `init_rc` scripts come in. 

### **How `init_rc` Works with `cc_binary` Modules**

1. **Defining Startup Behavior**:
   - By adding `init_rc` to a `cc_binary`, you effectively install an `init.rc` script alongside the binary, specifying how and when it should start.
   - For instance, this might be at boot time, triggered by specific system properties, or in response to certain system events.

2. **Execution Timing**:
   - The `init.rc` script can define whether the binary starts at boot or waits until specific conditions are met. This is common for low-level services, such as hardware interface services or monitoring tools.
   - Example: 
     ```plaintext
     cc_binary {
         name: "my_service",
         srcs: ["my_service.cpp"],
         init_rc: ["my_service.rc"],
     }
     ```
     Then, in `my_service.rc`:
     ```plaintext
     on boot
         start my_service
     
     service my_service /vendor/bin/my_service
         class core
         user root
         group system
         disabled
     ```
   - The `on boot` directive here ensures the service will start during the boot sequence.

### **Common Pitfalls and Misunderstandings**

1. **`init.rc` Doesn’t Automatically Launch `cc_binary` Services**:
   - Simply declaring a `cc_binary` with an `init.rc` file doesn’t make it automatically execute. The `init.rc` script must define the exact conditions and properties (like `on boot` or `on property:<property_name>`) under which the binary will be launched.

2. **Contradiction Clarified**: 
   - When we say `cc_binary` binaries “don’t automatically have an `init.rc` file to control startup,” we mean they don’t inherently have any special `init.rc` script attached to them by default. You must add one if you want the binary to start under specific conditions.
   - If you provide an `init_rc`, that script will dictate when and how the binary is executed.

3. **Limitations and Best Practices**:
   - Running a `cc_binary` service at boot can have performance implications, especially if there are dependencies on other services or resources that may not be available immediately at boot. Be cautious about starting non-essential services during the boot process, as they might delay the boot sequence or require dependencies that aren’t initialized yet.
   - Triggering binaries later in the boot sequence (using properties like `sys.boot_completed=1`) can help avoid these issues, as it ensures all base services and frameworks are initialized.

### **Differences: `cc_binary` with `init_rc` vs. System-Level Init.rc Files**

- **`cc_binary` with `init_rc`**: 
  - Tied specifically to the lifecycle of the binary itself. The `init.rc` script provides the start conditions specific to that binary or service, without affecting the broader system boot.
  - Allows you to handle custom or vendor-specific services independently of core system services, especially helpful for device-specific implementations or vendor-specific modules.

- **System-Level `init.rc` Files**:
  - Located in `system/core/rootdir/init.rc`, these scripts handle the boot-up of core Android services, processes, and properties.
  - Controls the system-level startup sequence and is generally not used for launching custom binaries or vendor-specific services, which are better managed through module-specific `init.rc` files in `vendor/etc/init`.

### **Summary and Practical Usage**

- **When to Use `init_rc` in `cc_binary`**: Use `init_rc` with `cc_binary` if you need the binary to run as a service based on specific triggers. This approach is common in automotive or embedded Android, where vendor-specific binaries perform low-level tasks like monitoring hardware or interfacing with custom peripherals.
  
- **Managing Conflicts and Dependencies**: Make sure any `init.rc` file specified for a `cc_binary` does not interfere with core system boot services. To avoid conflicts, rely on unique triggers or property-based conditions, and avoid modifying core `init.rc` files unless necessary.

This setup gives you flexible control over custom binaries while keeping them isolated from the core system processes. It’s a modular and responsive way to manage device-specific functionality on Android systems.

---
---
---


In this example, the `sensor_data_handler` service, defined as a `cc_binary`, is linked to the system’s initialization process via an entry in `init.vendor.rc`. Here’s a step-by-step breakdown of how this linkage works and how the service will be invoked:

### 1. **Defining the Service in `init.vendor.rc`**

The service is defined in `init.vendor.rc` (located in the `/vendor/etc/init/` directory) with the following code:

```plaintext
service sensor_data_handler /vendor/bin/sensor_data_handler
    class late_start
    user system
    group system
    disabled
    oneshot

on property:sys.boot_completed=1
    start sensor_data_handler
```

Let’s break down what each of these lines does:

- **`service sensor_data_handler /vendor/bin/sensor_data_handler`**: This line registers the service under the name `sensor_data_handler`, with the executable path `/vendor/bin/sensor_data_handler`. This path is where the binary is installed due to the `relative_install_path` in `cc_binary`.

- **`class late_start`**: The `late_start` class means that the service will be started later in the boot process, specifically after most essential system services are up and running. This helps avoid potential conflicts with early-start services.

- **`user system` and `group system`**: These lines specify that the service should run as the `system` user and group, giving it appropriate permissions.

- **`disabled`**: This indicates that the service will not start automatically at boot. Instead, it will be started later when specifically triggered.

- **`oneshot`**: The `oneshot` flag tells the system to run the service only once when it’s triggered, and not to restart it automatically.

### 2. **Triggering the Service on System Boot Completion**

The `on property:sys.boot_completed=1` trigger waits until the `sys.boot_completed` property is set to `1`, which indicates that the Android boot process has completed. When this property is set, it signals that the device is fully booted and ready for additional services to start.

- **`start sensor_data_handler`**: This line within the `on` block initiates the `sensor_data_handler` service once `sys.boot_completed=1`. Since the service was defined with `disabled`, it requires an explicit start command to begin.

### 3. **Linking the `init.vendor.rc` to the System’s Init Process**

The Android `init` process reads multiple `init.rc` files during boot, including those located in the `/vendor/etc/init/` directory (like `init.vendor.rc`). This process is part of Android's multi-partition architecture, where:

- **System Init Process**: At boot, the system’s `init` process will parse and execute commands from multiple `init.rc` files, including the main system init script (e.g., `/system/etc/init/`) and any vendor-specific scripts located in `/vendor/etc/init/`.

- **Vendor Init Scripts**: Since Android 8.0 (Project Treble), `/vendor` partition init scripts are separately managed. The system init process includes these vendor scripts, allowing OEMs or developers to define device-specific services and configurations without modifying core system init files.

The `init.vendor.rc` file (or another appropriately named vendor init script) is loaded automatically by the init system, which reads all `*.rc` files in the vendor directory. Thus, the `sensor_data_handler` service is defined as part of the init sequence.

### 4. **Execution Flow**

Here’s the step-by-step execution flow:

1. **Boot Process Begins**: The system starts the init process, which reads the core `init.rc` and any device-specific or vendor-specific `*.rc` files.
2. **Vendor Init Script Loaded**: `init.vendor.rc` is read and the `sensor_data_handler` service is registered but remains inactive (because of `disabled`).
3. **System Boot Completes**: When the system is fully booted, it sets `sys.boot_completed=1`.
4. **Trigger Fires**: The `on property:sys.boot_completed=1` condition is met in `init.vendor.rc`, starting `sensor_data_handler`.
5. **Service Runs Once**: `sensor_data_handler` runs once (due to `oneshot`), completing its execution as specified.

### Summary

In summary, `init.vendor.rc` links the `sensor_data_handler` binary to the system boot sequence using the init system’s property-based triggering. The service will run once at the end of boot, defined and controlled through the `init.vendor.rc` script, allowing for organized and conditional execution of vendor-specific services.


