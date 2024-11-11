
### 1. **Directory Structure and Build Process**
   - You have created a new directory (`device/bcrm/custom`) with the following files:
     - `my_custom_service.rc` (custom init script for defining the service's behavior)
     - `my_custom_service.cpp` (source code for the custom service)
     - `Android.bp` (build configuration file defining `my_custom_service` as a `cc_binary`)

   - The **build process** will follow the directives in `Android.bp`, which includes:
     ```plaintext
     cc_binary {
         name: "my_custom_service",
         srcs: ["my_custom_service.cpp"],
         init_rc: ["my_custom_service.rc"],
         vendor: true,
     }
     ```
   - In this `cc_binary` configuration:
     - The `srcs` property specifies the source code file (`my_custom_service.cpp`), which will be compiled into a binary named `my_custom_service`.
     - The `init_rc` property registers `my_custom_service.rc`, which the build system will place in the appropriate directory on the device.
     - The `vendor: true` flag indicates that this binary and its resources (like `my_custom_service.rc`) are vendor-specific, placing them under the `/vendor` partition on the device.

### 2. **Output Locations After Build**
   - **Binary File**: `my_custom_service` will be compiled and installed in `/vendor/bin/`.
   - **RC File**: `my_custom_service.rc` will be installed in `/vendor/etc/init/`.

### 3. **Service Configuration in `my_custom_service.rc`**
   - The `my_custom_service.rc` file configures how and when the service starts, stops, and under which conditions. Here’s the content based on your setup:
     ```plaintext
     service my_custom_service /vendor/bin/my_custom_service
         class main
         user system
         group system
         disabled
         oneshot

     on property:sys.boot_completed=1
         start my_custom_service
     ```

   - **Explanation of Configuration**:
     - `service my_custom_service /vendor/bin/my_custom_service`: Defines a service with the path to its executable.
     - `class main`: Assigns it to the `main` class, meaning it will be managed with other core services.
     - `user system` and `group system`: The service will run under the `system` user and group.
     - `disabled`: The service will not start immediately upon loading; it requires an explicit start command.
     - `oneshot`: Ensures the service only runs once each time it’s started.

   - **Trigger**:
     - `on property:sys.boot_completed=1`: Once the system property `sys.boot_completed` is set to `1` (indicating boot completion), this trigger will fire and start `my_custom_service`.

### 4. **How the Service and RC File are Invoked**
   - During boot, Android’s init system reads all `.rc` files in `/vendor/etc/init/` (including `my_custom_service.rc`).
   - Once the system finishes booting, `sys.boot_completed` is set to `1`, activating the trigger in `my_custom_service.rc`.
   - This causes `init` to start `my_custom_service` by running the binary from `/vendor/bin/my_custom_service`.

In summary:
- The build system compiles `my_custom_service.cpp` and installs the resulting binary in `/vendor/bin/`.
- The `my_custom_service.rc` file is placed in `/vendor/etc/init/`.
- At runtime, `init` reads the `.rc` file, waits for `sys.boot_completed=1`, and then starts `my_custom_service`.