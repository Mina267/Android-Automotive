

### 1. **Overview of VHAL in Android Automotive**
   - **Purpose**: VHAL is an essential Android Hardware Abstraction Layer (HAL) service within Android Automotive. It enables Android apps to control and query vehicle features by interacting with a car's ECUs (electronic control units).
   - **Functionality**: VHAL is designed as a property-based system allowing Android applications to:
     - **Read** the car's state (e.g., battery level).
     - **Write** values to alter the car's state (e.g., unlock doors).
     - **Register callbacks** to get notified when a property changes (e.g., speed or door lock status).

---

### 2. **Key Properties and Data Access in VHAL**

   - **Property System**: VHAL uses a well-defined property-based access system. Properties are key identifiers representing each functionality that an application or system can query or modify.
   - **Common Properties**:
     - **INFO_EV_BATTERY_CAPACITY**: Gets the battery capacity in electric or hybrid vehicles.
     - **FUEL_DOOR_OPEN**: Triggers the fuel door to open or close.

   - **Entry Point**: The implementation begins at the AOSP source path:
     ```bash
     cd hardware/interfaces/automotive/vehicle
     ```

---

### 3. **Core File Structure in VHAL**
   - **AIDL Files**: Located in:
     - `aidl_property/android/hardware/automotive/vehicle` - holds stubs and types for Android app usage.
   - **Native Implementation**: Found in:
     - `aidl/impl/vhal` - includes the main C++ implementation files.
     - `Android.bp` - Soong build system file referencing the necessary libraries.
   - **Service Configuration**: The file `vhal-default-service.rc` ensures VHAL launches with system boot.
   - **Entry Point**: `VehicleService.cpp` initializes VHAL operations.

---

### 4. **Configuring VHAL Properties**

   VHAL properties vary based on:
   - **Access Mode** (from `VehiclePropertyAccess.aidl`):
     - `READ`: Apps can only read this property.
     - `READ_WRITE`: Apps can read and write.
     - `WRITE`: Apps can only write.
   - **Change Mode** (from `VehiclePropertyChangeMode.aidl`):
     - `ON_CHANGE`: Updates only when there’s a change.
     - `STATIC`: Remains static; doesn’t change.
     - `CONTINUOUS`: Continuously transmits values, even if unchanged.
   - **Minimum Sample Rate**: The lowest frequency for data updates.
   - **Initial Value**: Ensures the property has a default value when AOSP starts.

---

### 5. **Creating a Custom VHAL Property**

   A custom property must follow a unique identifier format, where:
   - **CUSTOM_PROPERTY = UNIQUE_ID + VEHICLEPROPERTYGROUP_ID + VEHICLEAREA_ID + VEHICLEPROPERTYTYPE_ID**
     - **UNIQUE_ID**: A distinct ID (e.g., 0x0F4C).
     - **VEHICLEPROPERTYGROUP_ID**: VENDOR group (0x200000000).
     - **VEHICLEAREA_ID**: Scope within the car, like GLOBAL (0x01000000).
     - **VEHICLEPROPERTYTYPE_ID**: Data type, such as INT32 (0x00400000).
   - **Example ID**: `CUSTOM_PROPERTY = 0x0F4C + 0x200000000 + 0x01000000 + 0x00400000`

---

### 6. **Steps to Implement a Custom VHAL Property**

#### a. VHAL Layer (Low-Level Implementation)
  1. **Location**: Open `aidl/impl/utils/test_vendor_properties/android/  hardware/automotive/vehicle/TestVendorProperty.aidl`.
  2. **Add the Property**:
      ```aidl
      /**
      * CUSTOM PROPERTY.
      *
      * @change_mode VehiclePropertyChangeMode.ON_CHANGE
      * @access VehiclePropertyAccess.READ_WRITE
      * @version 3
      */
      CUSTOM_PROPERTY = 0xF4C + 0x20000000 + 0x01000000 + 0x00400000,
      ```

   - **Set Property in Configuration File**:
     - Add to `TestProperties.json` in `aidl/impl/default_config/config/`:
       ```json
       {
         "property": "TestVendorProperty::CUSTOM_PROPERTY",
         "defaultValue": {"int32Values": [777]},
         "access": "VehiclePropertyAccess::READ_WRITE",
         "minSampleRate": 1,
         "changeMode": "VehiclePropertyChangeMode::ON_CHANGE"
       }
       ```

#### b. Framework Layer (Mid-Level Implementation)
   - **Add Entry in `FakeVhalConfigParser.java`**:
     - Modify the file in `{android_root_folder}/packages/services/Car/service/src/com/android/car/hal/fakevhal/`:
       ```java
       CONSTANTS_BY_NAME.put("CUSTOM_PROPERTY", TestVendorProperty.CUSTOM_PROPERTY);
       ```

#### c. Custom VHAL Implementation
   - **Driver Implementation**:
     - In `FakeVehicleHardware.cpp`, add logic for handling the custom property:
       ```cpp
       case toInt(TestVendorProperty::CUSTOM_PROPERTY):
           ALOGD("CUSTOM_PROPERTY Setting:");
           // Call device driver function or add property handling logic
           break;
       ```

---

### 7. **Verification of Custom Property**

After integrating the custom property:
   - **Testing in Application Layer**:
     - Use the **KitchenSink Application** in the Android App Drawer:
       - Navigate to the **PROPERTY TEST** section.
       - Find `CUSTOM_PROPERTY` by name or ID (e.g., 557846348).
       - Verify by setting or getting values.

   - **Use `logcat` to Monitor Output**:
     - Filter the logs for `CUSTOM_PROPERTY`:
       ```bash
       logcat | grep "CUSTOM_PROPERTY Setting"
       ```

---
---
---
---

<br>
<br>




### 1. **Overview of VHAL as a Property System**
   - **Purpose**: VHAL serves as an interface between Android and a vehicle’s Electronic Control Units (ECUs). Through properties, it enables Android to interact with vehicle functions like speed or fuel door controls.
   - **Flow Impact**: By accessing and modifying properties, VHAL allows Android Automotive apps to gather car data or control car features.
   - **Reasoning**: Android uses properties to standardize vehicle data, allowing for structured access and controlled modification of car attributes.

### 2. **Implementing Custom Properties in VHAL**
   - **Goal**: Adding a custom property (e.g., `CUSTOM_PROPERTY`) allows the system to interact with a specific car feature not already defined in the standard VHAL properties.
   - **How Properties Work**: Each property has a unique ID and is defined with access modes, change modes, and data types. This helps ensure that each property behaves as expected and is accessible only to permitted components.

### 3. **Creating Unique Identifiers for Custom Properties**
   - **Components of the Property ID**: The custom property ID is formed by combining:
     - **Unique ID** (`0xF4C`): Distinguishes this property from others.
     - **Group ID** (`0x20000000`): Groups it as a vendor-defined property.
     - **Area ID** (`0x01000000`): Specifies the scope within the car, like “global.”
     - **Type ID** (`0x00400000`): Defines the data type (e.g., `INT32`).
   - **Impact**: This structure keeps property IDs unique and categorized for consistency across Android Automotive systems.

### 4. **Configuring Custom Properties**
   - **File Adjustments in the AIDL Directory**:
     - **Step-by-Step File Changes**:
       - **`TestVendorProperty.aidl`**: Defines the property constant. The `@change_mode` and `@access` annotations specify how the property can be read, written, or updated. These settings allow controlled data flow and ensure that properties behave as intended.
       - **`TestProperties.json`**: Sets default values and behavior. Initial values prevent potential errors during boot, while `minSampleRate` dictates update frequency to manage data flow efficiently.
     - **Impact**: These configurations ensure the property has a valid starting point and follows the expected behavior throughout its lifecycle.
     - **Reasoning**: Default values and update configurations help maintain consistency, as all components know what to expect when interacting with the property.

### 5. **Integrating the Custom Property with the Framework Layer**
   - **Purpose**: The framework layer integration, done in `FakeVhalConfigParser.java`, maps the custom property to a recognizable constant.
   - **Impact**: By adding `CUSTOM_PROPERTY` to `CONSTANTS_BY_NAME`, Android applications and services can interact with it directly, making it discoverable and usable within the Android ecosystem.
   - **Reasoning**: This step bridges the gap between the lower-level HAL implementation and higher-level Android applications, enabling cross-layer access.

### 6. **Implementing Custom Behavior in the Fake HAL (Hardware Layer)**
   - **File**: `FakeVehicleHardware.cpp` in `maybeSetSpecialValue`.
   - **Functionality**: Adding a switch-case for `CUSTOM_PROPERTY` here enables the fake HAL to respond to interactions. This setup provides a stubbed behavior or can interact with an actual driver to modify the property.
   - **Flow Impact**: Allows testing of property interaction in a simulated environment or on real hardware, aiding debugging and development.
   - **Reasoning**: By handling the custom property within a fake implementation, developers can safely test interactions without affecting actual vehicle hardware.

### 7. **Verifying Changes in the Application Layer**
   - **Purpose**: Testing custom property behavior in the Android Automotive environment.
   - **Tools**:
     - **KitchenSink App**: The built-in KitchenSink app displays all vehicle properties, allowing verification that `CUSTOM_PROPERTY` appears and behaves as expected.
     - **Logcat**: Running `logcat | grep "CUSTOM_PROPERTY Setting"` enables tracking real-time property changes.
   - **Flow Impact**: This step confirms that the custom property works end-to-end, validating its integration across HAL and application layers.
   - **Reasoning**: Testing with the KitchenSink app ensures the property is fully accessible and functional within the Android system, highlighting potential issues early on.

### Summary: How Each Part Works Together
The custom property setup enables a new vehicle feature to be controlled and queried by Android. Each step—creating identifiers, setting configurations, connecting to the framework, and verifying through testing—ensures the property behaves predictably and integrates seamlessly across the Android and vehicle layers. This modular approach allows each component (from HAL to application layer) to interact with the car feature without conflict, achieving a consistent and testable property system.