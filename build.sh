#!/bin/bash
mkdir -p isodir/boot/grub && i686-elf-as boot.s -o boot.o && \
i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra && \
i686-elf-gcc -T linker.ld -o friendposjunior.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc && \
grub-file --is-x86-multiboot friendposjunior.bin && \
echo $? && \
cp friendposjunior.bin isodir/boot/friendposjunior.bin && \
cp grub.cfg isodir/boot/grub/grub.cfg && \
grub-mkrescue -o friendposjunior.iso isodir
