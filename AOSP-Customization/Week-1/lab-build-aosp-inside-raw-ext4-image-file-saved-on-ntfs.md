# Build AOSP inside a raw ext4 file system saved on a NTFS partition

### Create raw image file

> sudo mkdir /mnt/aosp/root
>
> sudo mount -t ntfs-3g /dev/nvme1n1p3 /mnt/aosp/root -o uid=1000,gid=1000,umask=022,noatime,nodiratime,big_writes,noacl,nls=utf8
>
> _# Allocate image size_
>
> _# dd if=/dev/zero of=/mnt/aosp/root/workspace/images/android-14.0.0_r67.ext4.raw bs=1G count=0 seek=300_
>
> dd if=/dev/zero of=/mnt/aosp/root/workspace/images/android-14.0.0_r67.ext4.raw bs=1 count=0 seek=300G
>
> sudo tune2fs -O ^has_journal /mnt/aosp/root/workspace/images/android-14.0.0_r67.ext4.raw
>
> sudo losetup /dev/loop11 /mnt/aosp/root/workspace/images/android-14.0.0_r67.ext4.raw
>
> _# Format the raw image file as ext4_
>
> sudo mkfs.ext4 -T news /dev/loop11
>
> _# Disable journaling to boost write performance (use cautiously)_
> sudo tune2fs -O ^has_journal /dev/loop11
>
> _# Mount raw image as loop device_
>
> _# sudo mount -t ext4 /dev/loop11 /mnt/aosp/instance -o users_
>
> sudo mount -o uid=1000,gid=1000,noatime,nodiratime,commit=60 /dev/loop11 /mnt/aosp/instance
>
> sudo tune2fs -O ^has_journal /dev/loop11
>
> _# Unmount and Detach the loop device_
>
> sudo umount /mnt/aosp/instance
>
> sudo losetup -d /dev/loop11

### Install Repo

> mkdir -p ~/.bin
>
> PATH="~/.bin:${PATH}"
>
> curl https://storage.googleapis.com/git-repo-downloads/repo > ~/.bin/repo
>
> chmod a+rx ~/.bin/repo

### Initiate aosp source

> ~/.bin/repo init --depth=1 -u https://android.googlesource.com/platform/manifest -b android-14.0.0_r67
>
> curl -o .repo/local_manifests/manifest_brcm_rpi.xml -L https://raw.githubusercontent.com/raspberry-vanilla/android_local_manifest/android-14.0/manifest_brcm_rpi.xml --create-dirs
>
> ~/.bin/repo sync --force-sync --no-clone-bundle --no-tags -j$(nproc --all)

### Build

> source build/envsetup.sh
>
> lunch aosp_rpi4_car-ap2a-userdebug
>
> make bootimage systemimage vendorimage -j$(nproc)

### Disable Ubuntu improving low-memory

> systemctl disable --now systemd-oomd
>
> systemctl is-enabled systemd-oomd

### Remove Ubuntu low-memory improving package

> sudo apt-get purge systemd-oomd
