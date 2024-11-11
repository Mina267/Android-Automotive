# Using SSH to Connect to Vexpress Board on QEMU with Buildroot

This guide outlines the steps to use SSH on your host machine to connect to a Vexpress board running on QEMU with Buildroot.

### Step 1: Edit QEMU Start Script

Navigate to the directory where QEMU images are located:

```sh
cd ~/buildroot/buildroot/output/images
```

Edit the `start-qemu.sh` script:

```sh
sudo vim start-qemu.sh
```

Modify the `qemu-system-arm` command to include necessary parameters for running the Vexpress board with appropriate options such as memory size, kernel image, device tree blob, root filesystem, and networking:

```sh
#!/bin/sh

BINARIES_DIR="${0%/*}/"
# shellcheck disable=SC2164
cd "${BINARIES_DIR}"

mode_serial=false
mode_sys_qemu=false
while [ "$1" ]; do
    case "$1" in
    --serial-only|serial-only) mode_serial=true; shift;;
    --use-system-qemu) mode_sys_qemu=true; shift;;
    --) shift; break;;
    *) echo "unknown option: $1" >&2; exit 1;;
    esac
done

if ${mode_serial}; then
    EXTRA_ARGS='-nographic'
else
    EXTRA_ARGS='-serial stdio'
fi

if ! ${mode_sys_qemu}; then
    export PATH="/home/mina/bulidroot/buildroot/output/host/bin:${PATH}"
fi

exec qemu-system-arm -M vexpress-a9 -smp 1 -m 256 -kernel zImage -dtb vexpress-v2p-ca9.dtb -drive file=rootfs.ext2,if=sd,format=raw -append "console=ttyAMA0,115200 rootwait root=/dev/mmcblk0"  -net nic,model=lan9118 -net tap,script=./qemu-ifup -net nic user  ${EXTRA_ARGS} "$@"

```

### Step 2: Run QEMU

Execute the modified `start-qemu.sh` script with `sudo`:

```sh
sudo ./start-qemu.sh
```

### Step 3: Set IP Address on Vexpress Board

Once the kernel has started in QEMU, set the IP address of `eth0` on the Vexpress board:

```sh
ip add a 192.168.1.9/24 dev eth0
```

### Step 4: Connect to Vexpress Board via SSH

On the host terminal, use SSH to connect to the Vexpress board:

```sh
ssh root@192.168.1.9
```

### Successful SSH Connection

You have successfully connected to the Vexpress board running on QEMU with Buildroot using SSH.

### Notes

Ensure that the necessary networking configurations are correctly set up in the QEMU command and the networking script.

### `tftp_bash` Script

Ensure the `tftp_bash` script contains the following content:

```sh
#!/bin/sh
ip a add 192.168.1.8/24 dev $1
ip link set $1 up
```

This script assigns the IP address `192.168.1.8` to the specified network interface and brings the interface up.

### Summary

1. **Edit QEMU Start Script**: Modify `start-qemu.sh` to configure QEMU for the Vexpress board.
2. **Run QEMU**: Execute the script to start the QEMU instance.
3. **Set IP Address**: Configure the IP address on the Vexpress board.
4. **Connect via SSH**: Use SSH to connect to the Vexpress board from the host machine.

These steps will allow you to use SSH to connect to a Vexpress board running on QEMU with Buildroot, facilitating easier interaction and management of the virtualized environment.

---


<p align="center">
	<img src="https://github.com/user-attachments/assets/ac5b6700-3955-4901-a514-f0ace1364321" width=75% height=75% />
</p>



