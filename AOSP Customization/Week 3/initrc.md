The `cc_binary` module in the Soong build system is used to compile native binaries, often written in C or C++, which run on the Android platform. While `cc_binary` binaries themselves do not automatically have an `init.rc` file to control their startup or execution timing, they can be referenced in an `init.rc` file to be executed during certain triggers like boot time, specific property changes, or other lifecycle events. Here’s a breakdown of how this would work and how it differs from system or device-specific `init.rc` configurations:

---

### **Using `cc_binary` with `init.rc` for App or Service Startup**

1. **Build the Binary with `cc_binary`**:
   - First, you define your binary in a `cc_binary` module in the Android build system. This binary will be compiled and packaged in the desired location (such as `system/bin` or `vendor/bin`) based on the module's configuration.

   ```plaintext
   cc_binary {
       name: "my_app_service",
       srcs: ["src/my_app_service.cpp"],
       vendor: true,  // Places the binary in the vendor partition
       relative_install_path: "bin",  // Custom install path if needed
   }
   ```

2. **Referencing the Binary in an `init.rc` File**:
   - Once built, you can create or edit an `init.rc` file to specify when this binary should run. This is typically done by adding a `service` entry in an `init.rc` file (e.g., `init.rpi4.rc`, `init.vendor.rc`) to launch the binary based on certain conditions.

   - Example `init.rc` entry:
     ```plaintext
     # Start my_app_service during boot
     service my_app_service /vendor/bin/my_app_service
         class main
         user root
         group system
         disabled
         oneshot

     on property:sys.boot_completed=1
         start my_app_service
     ```

   - **Explanation**:
     - `service my_app_service /vendor/bin/my_app_service`: Defines the service using the path where the binary is installed (`/vendor/bin/my_app_service` in this case).
     - `class main`: This assigns the service to the `main` class, meaning it can be controlled along with other primary services.
     - `user root` and `group system`: Sets the permissions for the service to run as the root user and belong to the system group.
     - `disabled`: The service won’t start automatically.
     - `oneshot`: The service runs once and then exits.
     - `on property:sys.boot_completed=1`: Starts `my_app_service` when the system property `sys.boot_completed` is set to 1, which happens at the end of the boot process.

3. **Execution Timing (Boot vs. Runtime)**:
   - **At Boot**: If your `cc_binary` service is defined with an `on boot` trigger in the `init.rc` file, it will execute early in the boot process, often used for core services or hardware-related functions.
   - **At Runtime**: By setting triggers like `on property`, you can control your binary’s execution based on system events or property changes. For example, starting it only after `sys.boot_completed=1` ensures the binary runs post-boot.

---

### **Differences Between `cc_binary` Services and System/Device `init.rc` Configurations**

| **Attribute**                  | **System `init.rc` (e.g., `init.rc`)**                  | **Device-Specific `init.rc` (e.g., `init.rpi4.rc`)**                | **App-Specific `cc_binary` Service (in custom `init.rc`)**             |
|--------------------------------|--------------------------------------------------------|---------------------------------------------------------------------|------------------------------------------------------------------------|
| **Purpose**                    | Initializes core Android system services               | Initializes hardware and device-specific configurations             | Initializes app-specific or custom binary services                     |
| **Scope**                      | System-wide, shared across all devices                 | Device-specific configurations (e.g., hardware drivers for RPi4)    | App-specific or binary-specific, only relevant to the defined binary   |
| **Trigger Type**               | System boot stages or property changes                 | Boot stages, property changes, or custom hardware triggers          | Configurable triggers (e.g., boot completion, property settings)       |
| **Example Services**           | `surfaceflinger`, `vold`, `zygote`                     | `init.rpi4.usb.rc`, GPIO initialization for RPi4                    | `my_app_service` (an app-specific custom binary)                       |
| **Execution**                  | Runs at different boot phases                          | Device-specific or partition-specific (e.g., `vendor` partition)    | Runs based on specified triggers, can be controlled per app requirement|
| **Use Case**                   | Essential for OS functioning                           | Specific to device initialization (e.g., USB, GPIO on RPi4)         | Provides app or service functionality, not critical for OS operation   |

---

### **Example Scenario: Custom Service for an App Using `cc_binary`**

Suppose you have an application that requires a custom binary (`cc_binary`) for some background data processing, like handling sensor data. Here’s how you might configure it:

1. **Define the Binary with `cc_binary`**:
   ```plaintext
   cc_binary {
       name: "sensor_data_handler",
       srcs: ["src/sensor_data_handler.cpp"],
       vendor: true,
       relative_install_path: "bin",
   }
   ```

2. **Add Service in `init.vendor.rc`**:
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

   - This configuration starts `sensor_data_handler` once when the boot completes. It will have system permissions, run only once, and is managed within the vendor partition, so it’s accessible if vendor-specific.

---

### Summary
- **System and device `init.rc`** files control core and device-specific initialization during boot.
- **App-specific services using `cc_binary`** can be started at boot or later based on property triggers in the `init.rc` configuration.
- Each approach is suited for its intended level: core OS functionality, device-specific configurations, or app/service needs.