# *Boot check script*

## Linux

### *Script*
```bash

for bootOption in mmc nic NoOption; do
    if test "$bootOption" = "mmc"; then
        echo "Checking MMC..."
        if mmc rescan; then
            if mmc dev; then
                echo "MMC device found, loading zImage and device tree..."
                if fatload mmc 0:1 $kernel_addr_r zImage; then
                    if fatload mmc 0:1 $fdt_addr_r vexpress-v2p-ca9.dtb; then
                        bootz $kernel_addr_r - $fdt_addr_r
                        exit
                    else
                        echo "Failed to load device tree from MMC."
                    fi
                else
                    echo "Failed to load zImage from MMC."
                fi
            else
                echo "Failed to switch to MMC partition 1."
            fi
        else
            echo "Failed to rescan MMC."
        fi
    elif test "$bootOption" = "nic"; then
        echo "Checking NIC..."
        if ping 192.168.1.8; then
            echo "Network connection available, loading from network..."
            # Additional commands to load from network can be added here
        fi
        exit
    elif test "$bootOption" = "NoOption"; then
        echo "No option available"
        exit
    fi
done
```
### *Make executable image for u-boot to run script*
```bash
sudo mkimage -A arm -T script -C none -a 0x62000000 -e 0x62000000 -n 'MMC Check Script' -d ubootScript.txt ~/boot/ubootScript.img
```
<p align="center">
	<img src="https://github.com/user-attachments/assets/9d3898b4-aff3-4b0d-a9da-c21e75aebfc3" width=75% height=75% />
</p>
<p align="center">
	<img src="https://github.com/user-attachments/assets/cf73498a-8089-4e6f-ab3e-9c947c54bf1c" width=75% height=75% />
</p>

### *Run qemu*
```bash
sudo qemu-system-arm -M vexpress-a9 -m 128M -nographic -kernel u-boot -sd ~/sd.img  -net tap,script=./qemu-ifup -net nic

```

## qemu save script to load in booting

``` bash

editenv bootcmd
edit: fatload mmc 0:1 0x62000000 /ubootScript.img; source 0x62000000
saveenv

```

<p align="center">
	<img src="https://github.com/user-attachments/assets/93108637-563c-4658-ae57-9bdc670acadd" width=75% height=75% />
</p>



## *Booting*



<p align="center">
	<img src="https://github.com/user-attachments/assets/570319d2-2c29-4e1d-824e-960e9b4ee3f4" width=75% height=75% />
</p>

