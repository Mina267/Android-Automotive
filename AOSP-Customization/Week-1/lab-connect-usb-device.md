# Find the connected usb device info
> lsusb

> sudo nano /etc/udev/rules.d/51-android.rules
>
> SUBSYSTEM=="usb", ATTR{idVendor}=="18d1", MODE="0666", GROUP="plugdev"
>
> sudo udevadm control --reload-rules
>
> sudo udevadm trigger

