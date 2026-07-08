# BareBoot

A practice operating system written from scratch in C and x86 Assembly, following the OSDev Bare Bones guide as a foundation. This project is intended as a long-term exploration of operating system internals, computer architecture, and low-level systems programming.

## Features

- Multiboot-compliant kernel
- Boots using GRUB
- Freestanding C environment
- VGA text mode output
- Cross-compiled with an `i686-elf` GCC toolchain
- Runs in QEMU

## Project Structure

```
.
├── boot.s              # Bootloader entry point and Multiboot header
├── kernel.c            # Kernel entry point
├── linker.ld           # Linker script
├── Makefile            # Build automation
├── isodir/
│   └── boot/
│       ├── myos
│       └── grub/
│           └── grub.cfg
└── README.md
```

## Requirements

- i686-elf GCC cross compiler
- GNU Binutils
- GRUB (`grub-pc-bin`)
- xorriso
- QEMU

## Learning Goals

This project is being developed to gain a deeper understanding of:

- Operating system architecture
- x86 protected mode
- Bootsequence

## References

- https://wiki.osdev.org
- https://wiki.osdev.org/Bare_Bones
- Intel® 64 and IA-32 Architectures Software Developer's Manual
