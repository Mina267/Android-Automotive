

# *AIDL Development*

# 1- Interface Folder

## Step 1: Create the AIDL Interface

### Purpose  
AIDL allows inter-process communication (IPC) by defining an interface for your service. It facilitates communication between client and server processes using Android's Binder framework.

### Steps  

1. **Ensure Proper Folder Structure**  
   Organize your interface files as follows:  
   `interface/<device_name>/aidl/<reverse_domain_name>/`  
   This ensures a clean hierarchy and adherence to Android build system conventions.

   Example:  
   ```
   interface/ultrasonic_device/aidl/com/luxoft/ultrasonic
   ```

2. **Create the Interface File**  
   Name your interface `I<InterfaceName>.aidl` to follow naming conventions.

   Example:  
   File: `IUltrasonic.aidl`  

   ```aidl
   package com.luxoft.ultrasonic;

   @VintfStability // Ensures interface version compatibility
   interface IUltrasonic {
       int getUltrasonicReading(int ultrasonicSensorNumber); // A method for retrieving sensor data
   }
   ```

   **Goal:** Define the methods that clients can call to interact with the service.

---

## Step 2: Define the Blueprint (Build Configuration)

### Purpose  
The blueprint (`Android.bp`) configures the build system to recognize and process your AIDL files.

### Steps  

1. **Create the Blueprint File**  
   Path: `interface/<device_name>/aidl/Android.bp`

2. **Add the Following Configuration**  

   ```plaintext
   aidl_interface {
       name: "com.luxoft.ultrasonic", // Interface package name
       srcs: ["com/luxoft/ultrasonic/*.aidl"], // Source files
       stability: "vintf", // Versioned interface stability
       vendor_available: true, // Indicates the interface is vendor-accessible
       backend: {
           java: {
               platform_apis: true, // Allows using Android platform APIs
           },
       },
       owner: "Luxoft", // Maintainer of the interface
   }
   ```

   **Goal:** Register the AIDL interface with the Android build system and set its properties.

---

## Step 3: Freeze and Update the API

### Purpose  
Freezing an API creates a stable version that cannot be changed, ensuring backward compatibility. Updating allows incorporating new features while maintaining existing versions.

### Commands  

1. **Freeze the API**  
   ```bash
   make com.luxoft.ultrasonic-freeze-api
   ```  
   **What it Does:** Creates a `1` folder in `api_aidl` containing a snapshot of the current interface.

2. **Update the API**  
   ```bash
   make com.luxoft.ultrasonic-update-api
   ```  
   **What it Does:** Updates the `current` folder with the latest interface changes.

   After running these commands, the folder structure will look like:  
   ```
   api_aidl/
   ├── 1/       // Frozen API version
   ├── current/ // Latest version for development
   ```

---

## Step 4: Review the Updated Blueprint

### Purpose  
Ensure that the blueprint reflects the frozen API version and any new changes.

### Example Output:  

```plaintext
aidl_interface {
    name: "com.luxoft.ultrasonic",
    srcs: ["com/luxoft/ultrasonic/*.aidl"],
    stability: "vintf",
    vendor_available: true,
    backend: {
        java: {
            platform_apis: true,
        },
    },
    owner: "Luxoft",
    versions_with_info: [
        {
            version: "1", // Frozen version
            imports: [],
        },
    ],
    frozen: true, // Indicates this version is frozen
}
```

   **Note:** If required, remove the `frozen: true` line for flexibility during development.

   **Goal:** Maintain a consistent and version-controlled interface definition.

---

### Final hierarchy for your interface folder. 

```
    +---interfaces
        \---ultrasonic_device
            \---aidl
                |   Android.bp
                |
                +---aidl_api
                |   \---com.luxoft.ultrasonic
                |       +---1
                |       |   |   .hash
                |       |   |
                |       |   \---com
                |       |       \---luxoft
                |       |           \---ultrasonic
                |       |                   IUltrasonic.aidl
                |       |
                |       \---current
                |           \---com
                |               \---luxoft
                |                   \---ultrasonic
                |                           IUltrasonic.aidl
                |
                \---com
                    \---luxoft
                        \---ultrasonic
                                IUltrasonic.aidl
```







Here’s a detailed and polished explanation of the `Service Application Folder`, with added illustrations, comments, and explanations for the code:

---
---
<br>
<br>
<br>
<br>

# 2. Service Application Folder

The service application folder contains all the necessary components to implement, register, and run the AIDL interface on the service side. Here's the folder structure:  

```
ultrasonic_service
        ├───Android.bp
        ├───init       // Initialization scripts or configuration files
        ├───manifest   // Android or VINTF manifest for declaring the service
        └───src        // Source code for implementing the AIDL interface
            └───include // Header files for implementation details
```

---

## **A- Source files**

## Step 1: Implement the AIDL Interface in C++

### Purpose  
The AIDL interface is converted into a C++ implementation for efficient communication in the Android platform. This implementation acts as the service backend.

#### **Folder: `src`**

1. **Convert AIDL to C++**  
   Use AIDL's backend tools to convert the `.aidl` interface file into C++ stubs and headers. Follow [this guide](https://source.android.com/docs/core/architecture/aidl/aidl-backends) for details.

2. **Create the C++ Implementation**  
   File: `UltrasonicImpl.h`  

   ```cpp
   #pragma once

   #include <aidl/com/luxoft/ultrasonic/BnUltrasonic.h> // Auto-generated base class
   #include <mutex> // For thread safety

   namespace aidl {
   namespace com {
   namespace luxoft {
   namespace ultrasonic {

   #define ULTRASONIC_SENSOR_NUMBER 2 // Define the number of sensors

   // Implementation class for Ultrasonic AIDL interface
   class UltrasonicImpl : public BnUltrasonic {
       // Array of sensor objects
       UltrasonicSensor sensor[ULTRASONIC_SENSOR_NUMBER];

   public:
       UltrasonicImpl();

       // Override AIDL methods
       // Retrieves sensor readings for a specified sensor
       virtual ndk::ScopedAStatus getUltrasonicReading(
           int32_t sensorNumber, // Input: sensor index
           int32_t* _aidl_return // Output: sensor reading
       ) override;

   protected:
       ::ndk::ScopedAIBinder_DeathRecipient death_recipient_; // Handle client disconnections

       // Callback when the binder dies
       static void binderDiedCallbackAidl(void* cookie_ptr);
   };

   }  // namespace ultrasonic
   }  // namespace luxoft
   }  // namespace com
   }  // namespace aidl
   ```

   **Explanation of Key Components:**  
   - `BnUltrasonic`: The base class for the server-side implementation generated by AIDL tools.  
   - `ScopedAStatus`: Represents the result of the method call.  
   - `death_recipient_`: Ensures proper handling if the client process disconnects unexpectedly.  

3. **Implement the Methods**  
   File: `UltrasonicImpl.cpp`  

   ```cpp
   #include "UltrasonicImpl.h"
   #include <android-base/logging.h>

   namespace aidl {
   namespace com {
   namespace luxoft {
   namespace ultrasonic {

   UltrasonicImpl::UltrasonicImpl() {
       // Initialize sensors
   }

   ndk::ScopedAStatus UltrasonicImpl::getUltrasonicReading(
       // Implementation.
       return ndk::ScopedAStatus::ok();
   }

   void UltrasonicImpl::binderDiedCallbackAidl(void* cookie_ptr) {
       LOG(WARNING) << "Client binder died. Cleaning up resources.";
       // Handle cleanup here
   }

   }  // namespace ultrasonic
   }  // namespace luxoft
   }  // namespace com
   }  // namespace aidl
   ```

   **Key Concepts Illustrated:**  
   - Input validation for `sensorNumber` ensures safe operation.  
   - `measureDistance()` fetches data from the corresponding sensor.

---

## Step 2: Define Sensor Logic

### Purpose  
Encapsulate the logic for initializing and retrieving data from the ultrasonic sensors.

1. **Header File: `UltrasonicSensor.h`**  
   ```cpp
   #pragma once

   class UltrasonicSensor {
   public:
       // Initializes the sensor
       bool initialize();

       // Measures and returns the distance
       float measureDistance();
   };
   ```

2. **Implementation File: `UltrasonicSensor.cpp`**  
   ```cpp
   #include "UltrasonicSensor.h"

   bool UltrasonicSensor::initialize() {
       // Implementation for hardware initialization
       return true;
   }

   float UltrasonicSensor::measureDistance() {
       // Implementation for distance measurement
       return 0.0f; // Replace with actual sensor logic
   }
   ```

   **Goal:** Define clear responsibilities for sensor interactions.

---

## Step 3: Register and Run the Service

### Purpose  
Create a `main` function to register the service with the Android Service Manager and handle incoming requests.

1. **File: `main.cpp`**  

   ```cpp
   #include "UltrasonicImpl.h"
   #include <android-base/logging.h>
   #include <android/binder_manager.h>
   #include <android/binder_process.h>

   using aidl::com::luxoft::ultrasonic::UltrasonicImpl;

   int main() {
       LOG(INFO) << "Ultrasonic daemon started!";

       // Create a thread pool for handling client requests
       ABinderProcess_setThreadPoolMaxThreadCount(0);

       // Create an instance of the service
       std::shared_ptr<UltrasonicImpl> ultrasonic = ndk::SharedRefBase::make<UltrasonicImpl>();

       // Register the service with the Service Manager
       const std::string instance = std::string() + UltrasonicImpl::descriptor + "/default";
       binder_status_t status = AServiceManager_addService(ultrasonic->asBinder().get(), instance.c_str());
       CHECK_EQ(status, STATUS_OK) << "Failed to register service!";

       LOG(INFO) << "Ultrasonic service registered with instance: " << instance;

       // Block the process to handle incoming requests
       ABinderProcess_joinThreadPool();

       return EXIT_FAILURE;  // Should not be reached
   }
   ```

   **Comments in Code:**  
   - `ABinderProcess_setThreadPoolMaxThreadCount(0)`: Creates an unlimited thread pool for handling client requests.  
   - `AServiceManager_addService`: Registers the service with the name `<interface>/default`.  
   - `ABinderProcess_joinThreadPool()`: Keeps the service running to handle requests.  

---

---

## **B. Manifest Files**

### Purpose  
The manifest files are used to describe the hardware abstraction layer (HAL) interfaces provided by the device and their compatibility with the Android framework. These ensure that the service complies with versioning and compatibility rules set by Android.

---

### 1. **Framework Compatibility Matrix**  
File: `ultrasonic_framework_compatibility_matrix.xml`  

**Purpose**:  
Defines the AIDL HAL interface and ensures that the device supports this interface during Android Compatibility Test Suite (CTS) verification.

```xml
<compatibility-matrix version="1.0" type="framework">
    <hal format="aidl"> <!-- Specifies the HAL is implemented using AIDL -->
        <name>com.luxoft.ultrasonic</name> <!-- Fully qualified interface name -->
        <version>1</version> <!-- Version of the interface -->
        <interface>
        	<name>IUltrasonic</name> <!-- Name of the interface -->
        	<instance>default</instance> <!-- Default instance of the interface -->
        </interface>
    </hal>
</compatibility-matrix>
```

**Explanation of Key Components**:  
- `<hal format="aidl">`: Indicates the HAL is implemented using AIDL.  
- `<name>`: Fully qualified package name of the HAL.  
- `<version>`: Specifies the version of the interface, ensuring backward compatibility.  
- `<interface>`: Defines the specific AIDL interface (e.g., `IUltrasonic`).  
- `<instance>`: The specific instance name used for binding the service (commonly `default`).

---

### 2. **Device Manifest**  
File: `ultrasonic_device_manifest.xml`

**Purpose**:  
Declares the device-side implementation of the HAL interface and registers it with the Android system.

```xml
<manifest version="1.0" type="device">
    <hal format="aidl">
        <name>com.luxoft.ultrasonic</name> <!-- Package name of the HAL -->
        <version>1</version> <!-- Version of the HAL interface -->
        <interface>
        	<name>IUltrasonic</name> <!-- Name of the AIDL interface -->
        	<instance>default</instance> <!-- Default implementation of the service -->
        </interface>
    </hal>
</manifest>
```

**Explanation of Key Components**:  
- `<manifest version="1.0" type="device">`: Indicates that this is a device manifest, with versioning for backward compatibility.  
- `<hal>`: Same as in the framework compatibility matrix, but it specifies that this HAL is implemented by the device.  
- `<instance>`: Links the default implementation to the interface.

**Key Difference**:  
The **framework compatibility matrix** describes the expected interface by the Android framework, while the **device manifest** specifies the actual implementation provided by the device.

---

## **C. Init Script**

### Purpose  
The init script configures and manages the service lifecycle, ensuring that the `ultrasonic-service` is started and registered with the AIDL Service Manager.

---

### File: `ultrasonic.rc`

```rc
# Declares a service named "ultrasonic-service"
# The service executable is located in the /vendor/bin/hw directory
service ultrasonic-service /vendor/bin/hw/ultrasonic-service

    # Links the AIDL interface to enable IPC (Inter-Process Communication)
    interface aidl com.luxoft.ultrasonic.IUltrasonic/default

    class main         # Marks the service as part of the main class of services
    user root          # Runs the service with root privileges
    group root         # Assigns the root group to the service
    shutdown critical  # Ensures the service is stopped safely during shutdown
    oneshot            # Indicates the service should run once and not restart automatically

# Late initialization
on late-init
    # Starts the ultrasonic-service binary located at /vendor/bin/hw
    exec /vendor/bin/hw/ultrasonic-service
```

---

**Explanation of Key Components**:  

1. **Service Declaration**  
   - `service ultrasonic-service /vendor/bin/hw/ultrasonic-service`: Declares the service executable path.  
   - `interface aidl com.luxoft.ultrasonic.IUltrasonic/default`: Associates the service with the `IUltrasonic` interface.  

2. **Service Properties**  
   - `class main`: Categorizes this service as part of the "main" class, which contains essential services.  
   - `user root` and `group root`: Grants the service root permissions.  
   - `shutdown critical`: Ensures the service is safely stopped during system shutdown.  
   - `oneshot`: Prevents automatic restarts after the service exits.  

3. **Late Initialization**  
   - `on late-init`: Runs commands after the `init` phase is completed.  
   - `exec /vendor/bin/hw/ultrasonic-service`: Executes the service binary manually.


---

## **D. `Android.bp`**


### 1. **Defaults Section**

```bp
cc_defaults {
    name: "com.luxoft.ultrasonic-defaults",
    shared_libs: [
        "com.luxoft.ultrasonic-V1-ndk", // AIDL-generated NDK interface library
        "libbase",                     // Base library for common Android utilities
        "libbinder_ndk",               // Binder library for AIDL IPC support
    ],
    vendor: true, // Marks this as a vendor-specific build component
}
```

#### Explanation:
- **`cc_defaults`**:  
  This creates a reusable configuration block for other modules.  
- **`shared_libs`**:  
  Declares shared libraries that the binary will dynamically link against at runtime.
    - `com.luxoft.ultrasonic-V1-ndk`: Links the AIDL NDK interface.
    - `libbase`: Provides Android base utility functions.
    - `libbinder_ndk`: Supports communication between processes via the Android Binder.
- **`vendor: true`**:  
  Indicates that this module is specific to the vendor partition, used for hardware-specific implementations.

---

### 2. **Static Library Definition**

```bp
cc_library_static {
    name: "com.luxoft.ultrasonic-lib", // Name of the static library
    defaults: ["com.luxoft.ultrasonic-defaults"], // Inherits default configurations
    srcs: [
        "src/*", // Includes all source files in the src directory
    ],
    export_include_dirs: [
        "src/include", // Makes headers in this directory available for dependent modules
    ],
}
```

#### Explanation:
- **`cc_library_static`**:  
  Defines a static library to compile and link into other binaries.  
- **`srcs`**:  
  Lists the source files for the library. Here, all files in the `src` directory are included.  
- **`export_include_dirs`**:  
  Exposes the specified include directories to other modules that depend on this library.

---

### 3. **Binary Definition (Service Executable)**

```bp
cc_binary {
    name: "ultrasonic-service", // Name of the service binary
    defaults: ["com.luxoft.ultrasonic-defaults"], // Inherits default configurations
    relative_install_path: "hw", // Installs the binary to /vendor/bin/hw
    init_rc: ["init/ultrasonic-default.rc"], // Specifies the init.rc file for service initialization
    vintf_fragments: ["manifest/ultrasonic_device_manifest.xml"], // Links the VINTF manifest
    vendor: true, // Specifies the binary is built for the vendor partition
    srcs: [
        "src/ultrasonic_service_main.cpp", // Main entry point for the service
    ],
    static_libs: [
        "com.luxoft.ultrasonic-lib", // Links the static library defined earlier
    ],
    shared_libs: [
        "libbase",          // Provides common Android utility functions
        "libbinder",        // Binder communication library
        "libcamera_metadata", // Camera metadata handling library
        "libcutils",        // Common C utilities library
        "libgui",           // GUI utilities (e.g., buffers)
        "liblog",           // Android logging library
        "libnativewindow",  // Native window handling library
        "libutils",         // Provides utilities for common data structures
    ]
}
```

#### Explanation:
- **`cc_binary`**:  
  Defines the service binary that will run as the `ultrasonic-service`.  
- **`relative_install_path`**:  
  Places the binary in `/vendor/bin/hw`, which is the standard location for vendor HALs.  
- **`init_rc`**:  
  Specifies the associated init script (`ultrasonic-default.rc`) to start the service.  
- **`vintf_fragments`**:  
  Links the VINTF manifest (`ultrasonic_device_manifest.xml`) for HAL compatibility declarations.  
- **`srcs`**:  
  Points to the main source file of the service (`ultrasonic_service_main.cpp`).  
- **`static_libs`**:  
  Links the static library defined earlier (`com.luxoft.ultrasonic-lib`) for internal functionality.  
- **`shared_libs`**:  
  Includes shared libraries required for runtime functionality.

---
---
<br>
<br>
<br>
<br>

### **3. SELinux Policy Folder**

The **`sepolicy`** folder defines the security policies needed for your HAL and service components to operate correctly within Android’s SELinux-enforced environment. The policies define permissions, domains, and contexts for each component.

---

#### **Template Hierarchy**

```plaintext
\---sepolicy
    +---app
    |       helloapp_service.te
    |       seapp_contexts
    |
    +---daemon
    |       file_contexts
    |       hello.te
    |
    +---hal
    |       hal.te
    |
    +---service
    |       service_contexts
    |
    \---vendor
            vndservice.te
```

---

### **Key Changes to Template Files**

#### **1. `app/seapp_contexts`**
Define the service’s SELinux app domain:
```plaintext
user=_app seinfo=platform name=com.luxoft.ultrasonic domain=helloapp_service type=app_data_file levelFrom=user  
```

---

#### **2. `daemon/file_contexts`**
Specify the location of the HAL service executable:
```plaintext
/vendor/bin/hw/ultrasonic-service u:object_r:hello_exec:s0
```

---

#### **3. `service/service_contexts`**
Define the service interface context:
```plaintext
com.luxoft.ultrasonic_service.IUltrasonic/default u:object_r:hello_server_service:s0
```
---
---

### **Policy Rules**

#### **4. `app/helloapp_service.te`**
Defines permissions for the app domain interacting with HAL components:
```plaintext
type helloapp_service, domain;
app_domain(helloapp_service)

# Allow interaction with system services
allow helloapp_service activity_service:service_manager find;
allow helloapp_service netstats_service:service_manager find;

# Communicate with HAL
hal_client_domain(helloapp_service, hal_hello)

# Networking permissions
net_domain(helloapp_service)

# Permissions for additional services
allow helloapp_service radio_service:service_manager find;
```

---

#### **5. `daemon/hello.te`**
Rules for the HAL service daemon:
```plaintext
# Define hello HAL service
type hello, domain;
type hello_exec, exec_type, file_type, vendor_file_type;

# Initialize daemon domain
init_daemon_domain(hello)

# Networking permissions
net_domain(hello)

# Use binder for communication
vndbinder_use(hello)

# Communicate with hwservicemanager
binder_call(hello, hwservicemanager)

# Register as a HAL server
hal_server_domain(hello, hal_hello)

# Allow binder call transfers
allow hello servicemanager:binder { call transfer };
```

---

#### **6. `hal/hal.te`**
Duplicate policies for the HAL daemon to interact securely:
```plaintext
# hello HAL service daemon
type hello, domain;
type hello_exec, exec_type, file_type, vendor_file_type;

init_daemon_domain(hello)

# Networking permissions
net_domain(hello)

# Binder interface for HAL communication
vndbinder_use(hello)

# Interact with hwservicemanager
binder_call(hello, hwservicemanager)

# Register as HAL server
hal_server_domain(hello, hal_hello)

# Allow binder calls
allow hello servicemanager:binder { call transfer };
```

---

#### **7. `vendor/vndservice.te`**
Rules for vendor services:
```plaintext
type hello_server_service, hal_service_type, protected_service, service_manager_type;

# Allow hello service to register with service manager
allow hello hello_server_service:service_manager add;

# Allow app service to find hello server service
allow helloapp_service hello_server_service:service_manager find;
```

## Hierarchy
```
ultrasonichal
    ├───interfaces
    │   └───ultrasonic_device
    │       └───aidl
    │           └───com
    │               └───luxoft
    │                   └───ultrasonic
    ├───sepolicy
    │   ├───app
    │   ├───daemon
    │   ├───hal
    │   ├───service
    │   └───vendor
    └───ultrasonic_service
        ├───init
        ├───manifest
        └───src
            └───include
```


---
---

<br>
<br>
<br>
<br>


# **AIDL Integration in an Android App**

---

#### **1. Enable AIDL Support in the Project**
- Open **`build.gradle (Module: app)`** and add the following under `android`:
    ```gradle
    buildFeatures {
        aidl = true
    }
    ```
- Sync the project to apply changes.

---

#### **2. Create the AIDL Interface**
1. In **Android Studio**, right-click the `app` folder, select `New` > `AIDL` > `AIDL File`.
2. Use the **same package name** as defined in the AOSP HAL for consistency:
    ```java
    // IUltrasonic.aidl
    package com.luxoft.ultrasonic;

    interface IUltrasonic {
        int getUltrasonicReading(int ultrasonicSensorNumber);
    }
    ```
3. Build the project to generate the AIDL stubs automatically.

---

#### **3. Implement Main Activity Logic**
In your **MainActivity**, implement the service connection logic to interact with the Ultrasonic HAL via AIDL:

```java
package com.luxoft.ultrasonicaidltest;

import android.os.Bundle;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.luxoft.ultrasonic.IUltrasonic;

import java.lang.reflect.Method;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";

    private IUltrasonic iUltrasonic;
    private TextView txtUltrasonicOne;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        txtUltrasonicOne = findViewById(R.id.txtUltrasonicOne);

        try {
            // Access ServiceManager and retrieve the Ultrasonic HAL service
            Class<?> serviceManager = Class.forName("android.os.ServiceManager");
            Method getService = serviceManager.getMethod("getService", String.class);
            Object result = getService.invoke(null, "com.luxoft.ultrasonic.IUltrasonic/default");

            if (result != null) {
                IBinder binder = (IBinder) result;
                iUltrasonic = IUltrasonic.Stub.asInterface(binder);

                // Fetch the ultrasonic sensor reading
                int reading = iUltrasonic.getUltrasonicReading(0);
                Log.d(TAG, "Ultrasonic Reading: " + reading + " cm");

                // Update the UI
                txtUltrasonicOne.setText(reading + " cm");
            }
        } catch (Exception e) {
            Log.e(TAG, "Failed to initialize ultrasonic service", e);
            Toast.makeText(this, "Service Initialization Error: " + e.getMessage(), Toast.LENGTH_LONG).show();
        }
    }
}
```

---

### **Detailed Explanation of Key Steps**

#### **1. AIDL File Creation**
The AIDL file defines the interface between the app and the Ultrasonic HAL. It should match the one created in AOSP to ensure compatibility. Building the project generates stubs for interaction.

#### **2. Service Access via Reflection**
Android's **`ServiceManager`** is used to retrieve the AIDL service implemented in the AOSP layer:
- **Reflection** is necessary for accessing the system service `com.luxoft.ultrasonic.IUltrasonic/default`.

#### **3. Exception Handling**
Proper error handling ensures graceful recovery if the service is unavailable:
- Log errors for debugging.
- Notify users with a Toast message.

#### **4. UI Updates**
- The sensor readings are displayed in a `TextView` (`txtUltrasonicOne`), updating dynamically as needed.

---

## Add source file of your aosp 

```
└───packages
    └───apps
        └───UltrasonicAidlTest
            ├───aidl
            │   └───com
            │       └───luxoft
            │           └───ultrasonic
            ├───java
            │   └───com
            │       └───luxoft
            │           └───ultrasonicaidltest
            └───res
                ├───drawable
                ├───layout
                ├───layout-land
                ├───mipmap-anydpi-v26
                ├───mipmap-hdpi
                ├───mipmap-mdpi
                ├───mipmap-xhdpi
                ├───mipmap-xxhdpi
                ├───mipmap-xxxhdpi
                ├───values
                ├───values-night
                └───xml
```

### Android.bp
- Create an Android.bp file for the app in the UltrasonicAidlTest folder
```
android_app {
    name: "UltrasonicAidlTest",
    certificate: "platform",
   // privileged: true,
    srcs: ["java/**/*.java"],
    resource_dirs: [
        "res",
    ],
    platform_apis: true,
    static_libs: [
        "androidx.core_core-ktx",
        "androidx.appcompat_appcompat",
        "com.google.android.material_material",
        "androidx-constraintlayout_constraintlayout",
        "androidx.navigation_navigation-fragment-ktx",
        "androidx.navigation_navigation-ui-ktx",
        "com.luxoft.ultrasonic-V1-java",
    ],

}

```

# rpi4 `aosp_rpi4_car.mk`
### Add
```

#####################################################################
PRODUCT_PACKAGES += \
    ultrasonic-service \
    UltrasonicAidlTest \
    

BOARD_VENDOR_SEPOLICY_DIRS += device/brcm/rpi4/ultrasonichal/sepolicy/vendor 
BOARD_VENDOR_SEPOLICY_DIRS += device/brcm/rpi4/ultrasonichal/sepolicy/hal 
BOARD_VENDOR_SEPOLICY_DIRS += device/brcm/rpi4/ultrasonichal/sepolicy/service 
BOARD_VENDOR_SEPOLICY_DIRS += device/brcm/rpi4/ultrasonichal/sepolicy/daemon 
BOARD_VENDOR_SEPOLICY_DIRS += device/brcm/rpi4/ultrasonichal/sepolicy/app 


# ########## Device Manifest & Framework Compatibility Matrix Manifest ##########


DEVICE_FRAMEWORK_COMPATIBILITY_MATRIX_FILE += \
    ultrasonichal/ultrasonic_service/manifest/ultrasonic_framework_compatibility_matrix.xml \

```