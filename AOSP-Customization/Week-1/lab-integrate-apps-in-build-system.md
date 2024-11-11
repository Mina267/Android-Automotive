# lab2: Integrate with apps in the Android Build System

## Prebuilt App

1. Create new folder structure for the apps
2. Create Android.mk that will include info of single or multiple apps
>
        LOCAL_PATH := $(call my-dir)
        include $(CLEAR_VARS)

        LOCAL_MODULE := MY_APP_MODULE
        LOCAL_MODULE_TAGS := optional
        LOCAL_LICENSE_KINDS := legacy_restricted
        LOCAL_LICENSE_CONDITIONS := restricted
        LOCAL_SRC_FILES := $(LOCAL_MODULE).apk
        LOCAL_MODULE_CLASS := APPS
        LOCAL_MODULE_SUFFIX := .apk
        LOCAL_BUILT_MODULE_STEM := package.
        LOCAL_CERTIFICATE := PRESIGNED
        LOCAL_DEX_PREOPT := false
        LOCAL_PRIVILEGED_MODULE := true

        include $(BUILD_PREBUILT)

3. Add the defined module name to the product packages
>
        PRODUCT_PACKAGES += MY_APP_MODULE

## New Custom App Task
    Task Create new simple app and integrate it in Build System

## New Custom App Task
    Task Create new simple app and integrate it in Build System

## List and Discuss all BUILD_PREBUILT and BUILD_MAKE configurations


---
---
---
---


To add an APK as a system app on an Android build, you’ll create a prebuilt module configuration and update your device’s product makefile to include the APK in the system image. Here's a breakdown of each step.

---

### **Step 1: Define the Prebuilt App Module Configurations**

## 1. **Create a Folder Structure for the App**
   - In your source tree, create a folder for your app. The folder structure might look like this:
     ```
     vendor/{your_vendor}/prebuilt_apps/{app_name}/
     ```
   - Place the APK file (`MY_APP_MODULE.apk`) in this directory.

## 2. **Create the `Android.mk` File**

   - Inside the folder you created, create a file named `Android.mk` and add the following content:

     ```makefile
     LOCAL_PATH := $(call my-dir)
     include $(CLEAR_VARS)

     # Name of the app module
     LOCAL_MODULE := MY_APP_MODULE

     # Optional tags for filtering the build
     LOCAL_MODULE_TAGS := optional

     # Licensing information
     LOCAL_LICENSE_KINDS := legacy_restricted
     LOCAL_LICENSE_CONDITIONS := restricted

     # Path to the APK file relative to this Android.mk
     LOCAL_SRC_FILES := $(LOCAL_MODULE).apk

     # Define the type of module (application) and its extension
     LOCAL_MODULE_CLASS := APPS
     LOCAL_MODULE_SUFFIX := .apk
     LOCAL_BUILT_MODULE_STEM := package

     # Indicate that the APK is already signed
     LOCAL_CERTIFICATE := PRESIGNED

     # Disable dex pre-optimization since it’s a prebuilt app
     LOCAL_DEX_PREOPT := false

     # Make the app privileged if it requires special permissions
     LOCAL_PRIVILEGED_MODULE := true

     include $(BUILD_PREBUILT)
     ```

   Replace `MY_APP_MODULE` with your app’s name and ensure `MY_APP_MODULE.apk` matches the actual APK filename.

   No, `MY_APP_MODULE` in the `Android.mk` file does **not** have to be the same as the app's package name in the manifest. `MY_APP_MODULE` is simply the **module name** used by the Android build system to identify this prebuilt app in the build configuration.

### Key Points:

1. **Module Name (`MY_APP_MODULE`)**:
   - This is just an identifier within the Android build system.
   - You can set it to any unique name that helps you recognize the module in your build configuration.

2. **Package Name (from the Manifest)**:
   - The package name in the app’s `AndroidManifest.xml` is the unique identifier used by the Android OS to identify the app once installed.
   - This package name does not need to match `MY_APP_MODULE`.

### Example

If your app’s package name in `AndroidManifest.xml` is:
```xml
<manifest xmlns:android="http://schemas.android.com/apk/res/android"
    package="com.example.myapp">
```

You could still define `LOCAL_MODULE` in `Android.mk` as:
```makefile
LOCAL_MODULE := MyCustomApp
```

In this case, the **module name** is `MyCustomApp`, but the **package name** (seen by Android OS) is `com.example.myapp`. The module name is only for build purposes, while the package name is for app identification on the device.

he Android build system, you don’t need to explicitly reference the AndroidManifest.xml file or the app’s package name when integrating a prebuilt APK as a system app.

When using a prebuilt APK, the Android build system treats it as a complete package, and the manifest is already embedded within the APK file itself. All you need to do is specify the module name and file path in the Android.mk (or Android.bp for newer builds) as shown in the previous steps.

## 3. **Add the Module to the Product Packages**

   - Locate the **product makefile** (usually found in `device/{vendor}/{device_name}/device.mk` or `product.mk`).
   - Add the following line to include your app in the system image:

     ```makefile
     PRODUCT_PACKAGES += MY_APP_MODULE
     ```

   This ensures that `MY_APP_MODULE` will be bundled with the system image during the build process.

---

### **Step 2: Test by Injecting the App into the File System**

If you want to test without rebuilding the entire image, you can push the APK to the device and reboot to check functionality.

1. **Enter Root Mode**:
   ```bash
   adb root
   adb remount
   ```

2. **Push the APK to the System App Directory**:
   - Place the APK in the system directory for system apps:
     ```bash
     adb push MY_APP_MODULE.apk /system/app/MY_APP_MODULE/MY_APP_MODULE.apk
     ```

3. **Reboot the Device**:
   - Restart the device to apply changes:
     ```bash
     adb reboot
     ```

4. **Verify Installation**:
   - Check if the app is successfully installed as a system app:
     ```bash
     adb shell pm list packages | grep myapp
     ```

   Replace `myapp` with part of your package name to search for your app.

---

### **Note: For Full Integration**

For a permanent installation, ensure you rebuild the system image after adding `PRODUCT_PACKAGES += MY_APP_MODULE` to the product makefile. Then, flash the image onto your device to include the app as part of the system partition.


---
---
---
---


The `include $(BUILD_PREBUILT)` directive in an `Android.mk` file is used to include prebuilt binaries or APKs in the AOSP build system. When you have precompiled resources (such as an APK file or binary executable) that you don’t want to compile from source within AOSP, this directive tells the build system to include the prebuilt files directly into the system image.

Here's a breakdown of how to use `$(BUILD_PREBUILT)`:

### Basic Structure

Here's an example `Android.mk` file using `$(BUILD_PREBUILT)` to include a prebuilt APK in the build:

```makefile
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := MyApp  # The name of your module
LOCAL_SRC_FILES := MyApp.apk  # The location of the prebuilt APK
LOCAL_MODULE_CLASS := APPS  # Specifies that this is an app
LOCAL_MODULE_PATH := $(TARGET_OUT)/app  # Destination path on the system
LOCAL_MODULE_TAGS := optional  # Tags like optional or eng, depending on your build needs
LOCAL_PRIVILEGED_MODULE := true  # Use this if it's a privileged system app (e.g., system app with additional permissions)

include $(BUILD_PREBUILT)
```

### Key Components

- **`LOCAL_MODULE`**: The name for the app or binary. This name will be used to refer to the module within the AOSP build.
- **`LOCAL_SRC_FILES`**: Path to the prebuilt file (e.g., an APK file or executable binary). This should be relative to the `LOCAL_PATH`.
- **`LOCAL_MODULE_CLASS`**: Specifies the type of module. Use `APPS` for APK files or `EXECUTABLES` for binary files.
- **`LOCAL_MODULE_PATH`**: Destination directory on the system image where the file will be placed.
  - `$(TARGET_OUT)/app`: Puts the app in the `/system/app` folder (default system apps).
  - `$(TARGET_OUT_VENDOR)/app`: Puts the app in the `/vendor/app` folder (vendor-specific apps).
- **`LOCAL_PRIVILEGED_MODULE`**: Set this to `true` if the app needs system-level privileges (e.g., to access sensitive APIs).
- **`include $(BUILD_PREBUILT)`**: Tells the build system that the module is a prebuilt file, so it will include it as-is rather than compiling it.

### Examples

1. **Adding a Prebuilt APK to the System Partition**:
   ```makefile
   LOCAL_PATH := $(call my-dir)

   include $(CLEAR_VARS)
   LOCAL_MODULE := CustomApp
   LOCAL_SRC_FILES := CustomApp.apk
   LOCAL_MODULE_CLASS := APPS
   LOCAL_MODULE_PATH := $(TARGET_OUT)/app
   LOCAL_MODULE_TAGS := optional

   include $(BUILD_PREBUILT)
   ```

   This configuration adds `CustomApp.apk` to the `/system/app` directory on the device.

2. **Adding a Privileged System App**:
   ```makefile
   LOCAL_PATH := $(call my-dir)

   include $(CLEAR_VARS)
   LOCAL_MODULE := PrivilegedApp
   LOCAL_SRC_FILES := PrivilegedApp.apk
   LOCAL_MODULE_CLASS := APPS
   LOCAL_MODULE_PATH := $(TARGET_OUT_PRIV_APP)
   LOCAL_MODULE_TAGS := optional
   LOCAL_PRIVILEGED_MODULE := true

   include $(BUILD_PREBUILT)
   ```

   This configuration adds `PrivilegedApp.apk` to the `/system/priv-app` directory, granting it privileged access to system-level permissions.

3. **Adding a Prebuilt Binary to the System Image**:
   ```makefile
   LOCAL_PATH := $(call my-dir)

   include $(CLEAR_VARS)
   LOCAL_MODULE := MyService
   LOCAL_SRC_FILES := myservice_binary
   LOCAL_MODULE_CLASS := EXECUTABLES
   LOCAL_MODULE_PATH := $(TARGET_OUT)/bin
   LOCAL_MODULE_TAGS := optional

   include $(BUILD_PREBUILT)
   ```

   This configuration places `myservice_binary` in the `/system/bin` directory, making it executable from the command line.

### Build and Verification

After setting up the `Android.mk` with `$(BUILD_PREBUILT)`, build the AOSP image as usual:
```bash
make -j$(nproc)
```

Once built, flash the image to your device (or emulator) and check the specified path (`/system/app`, `/vendor/app`, etc.) to ensure your app or binary is included.


---
---
---
---



The `include $(BUILD_PREBUILT)` directive in an `Android.mk` file is used to include prebuilt binaries or APKs in the AOSP build system. When you have precompiled resources (such as an APK file or binary executable) that you don’t want to compile from source within AOSP, this directive tells the build system to include the prebuilt files directly into the system image.

Here's a breakdown of how to use `$(BUILD_PREBUILT)`:

### Basic Structure

Here's an example `Android.mk` file using `$(BUILD_PREBUILT)` to include a prebuilt APK in the build:

```makefile
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := MyApp  # The name of your module
LOCAL_SRC_FILES := MyApp.apk  # The location of the prebuilt APK
LOCAL_MODULE_CLASS := APPS  # Specifies that this is an app
LOCAL_MODULE_PATH := $(TARGET_OUT)/app  # Destination path on the system
LOCAL_MODULE_TAGS := optional  # Tags like optional or eng, depending on your build needs
LOCAL_PRIVILEGED_MODULE := true  # Use this if it's a privileged system app (e.g., system app with additional permissions)

include $(BUILD_PREBUILT)
```

### Key Components

- **`LOCAL_MODULE`**: The name for the app or binary. This name will be used to refer to the module within the AOSP build.
- **`LOCAL_SRC_FILES`**: Path to the prebuilt file (e.g., an APK file or executable binary). This should be relative to the `LOCAL_PATH`.
- **`LOCAL_MODULE_CLASS`**: Specifies the type of module. Use `APPS` for APK files or `EXECUTABLES` for binary files.
- **`LOCAL_MODULE_PATH`**: Destination directory on the system image where the file will be placed.
  - `$(TARGET_OUT)/app`: Puts the app in the `/system/app` folder (default system apps).
  - `$(TARGET_OUT_VENDOR)/app`: Puts the app in the `/vendor/app` folder (vendor-specific apps).
- **`LOCAL_PRIVILEGED_MODULE`**: Set this to `true` if the app needs system-level privileges (e.g., to access sensitive APIs).
- **`include $(BUILD_PREBUILT)`**: Tells the build system that the module is a prebuilt file, so it will include it as-is rather than compiling it.

### Examples

1. **Adding a Prebuilt APK to the System Partition**:
   ```makefile
   LOCAL_PATH := $(call my-dir)

   include $(CLEAR_VARS)
   LOCAL_MODULE := CustomApp
   LOCAL_SRC_FILES := CustomApp.apk
   LOCAL_MODULE_CLASS := APPS
   LOCAL_MODULE_PATH := $(TARGET_OUT)/app
   LOCAL_MODULE_TAGS := optional

   include $(BUILD_PREBUILT)
   ```

   This configuration adds `CustomApp.apk` to the `/system/app` directory on the device.

2. **Adding a Privileged System App**:
   ```makefile
   LOCAL_PATH := $(call my-dir)

   include $(CLEAR_VARS)
   LOCAL_MODULE := PrivilegedApp
   LOCAL_SRC_FILES := PrivilegedApp.apk
   LOCAL_MODULE_CLASS := APPS
   LOCAL_MODULE_PATH := $(TARGET_OUT_PRIV_APP)
   LOCAL_MODULE_TAGS := optional
   LOCAL_PRIVILEGED_MODULE := true

   include $(BUILD_PREBUILT)
   ```

   This configuration adds `PrivilegedApp.apk` to the `/system/priv-app` directory, granting it privileged access to system-level permissions.

3. **Adding a Prebuilt Binary to the System Image**:
   ```makefile
   LOCAL_PATH := $(call my-dir)

   include $(CLEAR_VARS)
   LOCAL_MODULE := MyService
   LOCAL_SRC_FILES := myservice_binary
   LOCAL_MODULE_CLASS := EXECUTABLES
   LOCAL_MODULE_PATH := $(TARGET_OUT)/bin
   LOCAL_MODULE_TAGS := optional

   include $(BUILD_PREBUILT)
   ```

   This configuration places `myservice_binary` in the `/system/bin` directory, making it executable from the command line.

### Build and Verification

After setting up the `Android.mk` with `$(BUILD_PREBUILT)`, build the AOSP image as usual:
```bash
make -j$(nproc)
```

Once built, flash the image to your device (or emulator) and check the specified path (`/system/app`, `/vendor/app`, etc.) to ensure your app or binary is included.