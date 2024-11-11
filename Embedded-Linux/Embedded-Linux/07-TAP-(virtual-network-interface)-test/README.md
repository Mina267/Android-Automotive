# *TAP virtual network interface*

## Linux
```sh
sudo qemu-system-arm -M vexpress-a9 -m 128M -nographic -kernel u-boot -sd ~/sd.img  -net tap,script=./qemu-ifup -net nic
```

```bash
#!/bin/sh
ip a add 192.168.1.8/24 dev $1
ip link set $1 up
```

## qemu
```sh
setenv ipaddr 192.168.1.9
setenv serverip 192.168.1.8
saveenv
ping $serverip
```

<p align="center">
	<img src="https://github.com/user-attachments/assets/38b631db-b71c-44fc-916b-0332be58462a" width=100% height=100% />
</p>

