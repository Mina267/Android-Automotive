# NFS

```
sudo qemu-system-arm -M vexpress-a9 -m 128M -nographic -kernel u-boot -sd ~/SD-card/sd.img  -net tap,script=./qemu-ifup -net nic
```
## Add this to bootcmd from the menu configuration for seamless booting.
```
setenv ipaddr 192.168.1.9;
setenv serverip 192.168.1.8;

setenv bootargs 'console=ttyAMA0  root=/dev/nfs ip=192.168.1.9:::::eth0 nfsroot=192.168.1.8:/srv/nfs-share,nfsvers=3,tcp rw init=/sbin/init';

tftp $kernel_addr_r zImage;
tftp $fdt_addr_r vexpress-v2p-ca9.dtb;
bootz $kernel_addr_r - $fdt_addr_r


```

---



<p align="center">
	<img src="https://github.com/user-attachments/assets/b299df3c-137e-4501-965a-2851783dc96e" width=75% height=75% />
</p>




<p align="center">
	<img src="https://github.com/user-attachments/assets/7017195c-a26d-456b-beb2-3fec72341e42" width=75% height=75% />
</p>



