/* Declaring contents for the multiboot specifications*/
.set ALIGN, 1<<0 /* << to show bitflag*/
.set MEMINFO, 1<<1
.set FLAGS, ALIGN|MEMINFO
.set MAGIC, 0x1BADB002  /*Fixed magic number identifying this as multiboot*/
.set CHECKSUM, -(MAGIC + FLAGS) 


/* Declare the constants for the multiboot header*/
.section .multiboot /* Define section of code */
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM
/* This order is defined by the multiboot specifications */


/* Leave space for the stack, according to x86 standard */
.section .bss
.align 16
stack_bottom:   #Labels bottom of the stack
.skip 16384
stack_top:      #Labels top of stack, stack grow downwards


.section .text
.global _start      #Linker defines this as the entry
.type _start, @function
_start:
    mov $stack_top, %esp    #initialize esp to the start of our stack
    call kernel_main        #Transfer control to kernel
    cli
1:  hlt
    jmp 1b

.size _start, . - _start
