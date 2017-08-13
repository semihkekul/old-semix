#!/bin/bash
echo ">>> removing old artifacts..." && \
rm -rf *.o *.bin *.iso isodir && \


mkdir -p isodir/boot/grub  && \

i686-elf-as boot.s -o boot.o && \


i686-elf-gcc -c kernel.c kernel/src/isr.c  kernel/src/gdt.c  kernel/src/idt.c  kernel/src/irq.c   kernel/src/terminal.c   kernel/src/string.c  kernel/src/timer.c kernel/src/keyboard.c  -std=gnu99 -ffreestanding -O2 -Wall -Wextra -fno-leading-underscore && \


i686-elf-gcc -T linker.ld -o friendposjunior.bin -ffreestanding -O2 -nostdlib  boot.o kernel.o gdt.o idt.o isr.o string.o irq.o timer.o keyboard.o  -lgcc && \

grub-file --is-x86-multiboot friendposjunior.bin && \
echo $? && \
cp friendposjunior.bin isodir/boot/friendposjunior.bin && \
cp grub.cfg isodir/boot/grub/grub.cfg && \
grub-mkrescue -o friendposjunior.iso isodir

