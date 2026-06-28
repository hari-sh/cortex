MEMORY
{
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 256K
    RAM   (rwx): ORIGIN = 0x20000000, LENGTH = 64K
}

SECTIONS
{
    .text : {
        KEEP(*(.vectors)) /* Force vector table to the very front */
        *(.text*)
        *(.rodata*)
    } > FLASH

    .data : {
        *(.data*)
    } > RAM

    .bss : {
        *(.bss*)
        *(COMMON)
    } > RAM
}