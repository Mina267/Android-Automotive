# lab1: change boot animation

## 1- Follow bootanimation.zip file format

>https://cs.android.com/android/platform/superproject/+/android-14.0.0_r61:frameworks/base/cmds/bootanimation/FORMAT.md

[Another Description](https://blog.justinbull.ca/making-a-custom-android-boot-animation/)

## 2- Test

    adb root
    adb remount
    adb push bootanimation.zip /system/media/bootanimation.zip

## 3- Copy boot/shutdown/reboot animation files to recommended file system path(s)

    PRODUCT_COPY_FILES += \
        [animation_path/bootanimation.zip]:system/media/bootanimation.zip

## 4- make the new ROM image

    make bootimage systemimage vendorimage -j$(nproc)
    ./rpi4-mkimg.sh

### Investigate update the Shutdown and Reboot animations

    Use this info as start point

    https://cs.android.com/android/platform/superproject/+/android14-qpr3-release:device/google/cuttlefish/vsoc_x86_64_only/auto_portrait/aosp_cf.mk;l=35?q=bootanimation.zip&ss=android%2Fplatform%2Fsuperproject

    /oem/media/bootanimation.zip
    /oem/media/shutdownanimation.zip
    /oem/media/userspace-reboot.zip

---
---
---

To customize the Android Automotive boot animation, you’ll follow these steps to prepare, replace, and configure a new boot animation in the system.

---

### **1. Prepare Your Boot Animation**

- **Create the Boot Animation**:
  - Design your custom animation as a series of sequential frames (images) and an audio file if needed.
  - Follow the format guidelines provided in the AOSP documentation for boot animations [here](https://cs.android.com/android/platform/superproject/+/android-14.0.0_r61:frameworks/base/cmds/bootanimation/FORMAT.md). This guide specifies how to organize frame folders, play times, and loop sequences within the `bootanimation.zip`.

- **Boot Animation File Structure**:
  - The `bootanimation.zip` should include folders (usually named `part0`, `part1`, etc.) that contain the frames.
  - You’ll also need a configuration file (`desc.txt`) inside the ZIP that defines the animation's resolution, frame rate, and looping behavior.

- **Example Structure**:
  ```
  bootanimation.zip
  ├── part0/
  │   ├── frame_00001.png
  │   ├── frame_00002.png
  │   └── ...
  ├── part1/
  │   ├── frame_00001.png
  │   ├── frame_00002.png
  │   └── ...
  └── desc.txt
  ```

### **2. Replace the Current Boot Animation**

To deploy your custom animation, you’ll need root access to the Android device.

1. **Enter Root Mode**:
   - Run the following commands to gain root access and make the system partition writable:
     ```bash
     adb root
     adb remount
     ```

2. **Push the New Boot Animation**:
   - Transfer the `bootanimation.zip` to the system’s media directory:
     ```bash
     adb push bootanimation.zip /system/media/bootanimation.zip
     ```

3. **Set Permissions (Optional)**:
   - Ensure the correct permissions for the file:
     ```bash
     adb shell chmod 644 /system/media/bootanimation.zip
     ```

4. **Reboot to Test**:
   - Restart the device to see your new boot animation in action:
     ```bash
     adb reboot
     ```

### **3. Add the Animation to the Product Configurations**

This step is essential if you want your custom animation included in the build so that it remains persistent across updates and builds.

1. **Modify Product Configuration**:
   - Edit the product configuration file to include your custom boot animation:
     ```makefile
     PRODUCT_COPY_FILES += [animation_path/bootanimation.zip]:system/media/bootanimation.zip
     ```
   - Replace `[animation_path/bootanimation.zip]` with the actual path to your custom `bootanimation.zip` file in your source tree.

2. **Rebuild the ROM Image**:
   - Once the configuration is set, rebuild the system images with the following command:
     ```bash
     make bootimage systemimage vendorimage -j$(nproc)
     ```
   - This rebuilds the necessary images (`boot.img`, `system.img`, `vendor.img`) and includes the custom boot animation in the new ROM image.

3. **Flash the Device (Optional)**:
   - Flash the rebuilt images onto the device to apply the changes permanently.

---

After completing these steps, your custom boot animation should display whenever the device boots up. This approach integrates the animation directly into the product build, ensuring it persists through updates or reboots.