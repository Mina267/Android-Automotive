# lab3: Flash AOSP ROM Image to Device

## Using fastboot

> fastboot erase <partition_name>
>
> fastboot erase system

> fastboot flash <partition_name> <image_file>
>
> fastboot flash system system.img

OR
 
> fastboot flashall
>
> fastboot reboot

## Using Etcher - gui tool
> https://etcher.balena.io/

## Using DD tool

> dd if=<AOSP_ROM_image_file> of=/dev/<SD_card_device_path> bs=1M conv=fdatasync
