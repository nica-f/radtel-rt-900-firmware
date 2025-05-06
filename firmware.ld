/* Generic Linker Script for Cortex-M0 (e.g., BT32F0x series) */

/* Entry Point */
ENTRY(Reset_Handler)

/* Memory Regions */
MEMORY
{
  FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = 256K
  SRAM (rwx)      : ORIGIN = 0x20000000, LENGTH = 32K
}

/* Highest address of the user mode stack */
_estack = ORIGIN(SRAM) + LENGTH(SRAM); /* Stack grows down from top of SRAM */

/* Sections */
SECTIONS
{
  /* The startup code goes first in FLASH */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(4);
  } >FLASH

  /* Program code and read-only data */
  .text :
  {
    . = ALIGN(4);
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    *(.glue_7)         /* glue arm to thumb */
    *(.glue_7t)        /* glue thumb to arm */
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;
  } >FLASH

  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    . = ALIGN(4);
  } >FLASH

  /* Initialized data sections goes into RAM, load LMA copy from FLASH */
  .data :
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */
    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
  } >SRAM AT> FLASH

  /* Uninitialized data section */
  .bss :
  {
    . = ALIGN(4);
    _sbss = .;
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
    __bss_end__ = _ebss;
    PROVIDE(end = _ebss);
  } >SRAM

  /* Heap section */
  .heap (COPY):
  {
    . = ALIGN(8);
    __HeapBase = .;
    KEEP(*(.heap))
    __HeapLimit = .;
  } >SRAM
  
  /* Stack section */
  .stack (COPY):
  {
    . = ALIGN(8);
    __StackLimit = .;
    KEEP(*(.stack))
    __StackTop = .;
  } >SRAM
  
  /* Remove information from the standard libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}
