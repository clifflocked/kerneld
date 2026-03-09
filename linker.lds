ENTRY(_start);

. = 0x80200000;

PHDRS {
    text PT_LOAD FLAGS(5);
    data PT_LOAD FLAGS(6);
}

SECTIONS {
    .text : {
        *(.init);
        *(.text);
    } :text
    .rodata : {
        *(.rodata);
    } :text
    .data : {
        *(.data);
    } :data
    .bss : {
        PROVIDE(__bss_start$ = .);
        *(.bss);
        . = ALIGN(8);
        PROVIDE(__bss_end$ = .);
        . += 0x800;
        PROVIDE(__global_pointer$ = .);
        . += 0x1000;
        PROVIDE(__stack_top$ = .);
    }
}

. = ALIGN(4K);
PROVIDE(__kernel_end$ = .);
