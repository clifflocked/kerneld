.section .init

.type _start, @function
.global _start
_start:
.option push
.option norelax
    la gp, __global_pointer$
.option pop

    csrw satp, zero
    la sp, __stack_top$

    la t0, __bss_start$
    la t1, __bss_end$

    bgeu t0, t1, bss_done # Skip if size of BSS is zero
bss_clear:
    sd zero, (t0)
    addi t0, t0, 8
    bltu t0, t1, bss_clear
bss_done:

    mv a0, a1 # Pass address of FDT as first argument

    tail init
