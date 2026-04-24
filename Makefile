all: build pack run

build: 
	gcc -static src/init.c -o rootfs/init

pack:
	cd rootfs && find . -print0 | cpio --null -ov -H newc | gzip -9 > ../initramfs.cpio.gz

run:
	qemu-system-x86_64 -kernel linux-6.6.21/arch/x86/boot/bzImage -initrd initramfs.cpio.gz -m 512M -nographic -append "console=ttyS0"

clean:
	rm -rf rootfs/init initramfs.cpio.gz
