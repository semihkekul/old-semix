/* Surely you will remove the processor conditionals and this comment
   appropriately depending on whether or not you use C++. */
#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>

#include "kernel/src/terminal.c"
#include "kernel/include/system.h"
 
/* Check if the compiler thinks we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

 


#if defined(_Cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void kernel_main(void) {

	/* Initialize terminal interface */
	terminal_initialize();
    
    gdt_install();
    idt_install();
    isr_install();
    irq_install();
   	keyboard_install();

	__asm__ __volatile__ ("sti");
	
	terminal_setcolor(VGACOLOR_LIGHT_GREEN);
	puts("frindpos junior is operational..\n");

	terminal_setcolor(VGACOLOR_LIGHT_GREY);
	puts("$");
	terminal_command_mode(true);

	

	for (;;);

}
