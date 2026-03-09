.section .text

.type interrupt_wrapper, @function
.global interrupt_wrapper
interrupt_wrapper:
    csrrw t0, sscratch, t0
    # Begin the stores
    sd ra,     (t0)
    sd sp,    8(t0)
    sd gp,   16(t0)
    sd tp,   24(t0)
    sd t1,   40(t0)
    sd t2,   48(t0)
    sd s0,   56(t0)
    sd s1,   64(t0)
    sd a0,   72(t0)
    sd a1,   80(t0)
    sd a2,   88(t0)
    sd a3,   96(t0)
    sd a4,  104(t0)
    sd a5,  112(t0)
    sd a6,  120(t0)
    sd a7,  128(t0)
    sd s2,  136(t0)
    sd s3,  144(t0)
    sd s4,  152(t0)
    sd s5,  160(t0)
    sd s6,  168(t0)
    sd s7,  176(t0)
    sd s8,  184(t0)
    sd s9,  192(t0)
    sd s10, 200(t0)
    sd s11, 208(t0)
    sd t3,  216(t0)
    sd t4,  224(t0)
    sd t5,  232(t0)
    sd t6,  240(t0)

    # TODO: Save floating-point regs

    mv t1, t0
    csrrw t0, sscratch, t0
    sd t0, 32(t1)

    csrw satp, zero # Disable paging

    call interrupt_handler

    csrw satp, a0 # Load satp

    csrr t0, sscratch

    # Begin the loads.
    ld ra,   (t0)
    ld sp,   8(t0)
    ld gp,   16(t0)
    ld tp,   24(t0)
    ld t1,   40(t0)
    ld t2,   48(t0)
    ld s0,   56(t0)
    ld s1,   64(t0)
    ld a0,   72(t0)
    ld a1,   80(t0)
    ld a2,   88(t0)
    ld a3,   96(t0)
    ld a4,  104(t0)
    ld a5,  112(t0)
    ld a6,  120(t0)
    ld a7,  128(t0)
    ld s2,  136(t0)
    ld s3,  144(t0)
    ld s4,  152(t0)
    ld s5,  160(t0)
    ld s6,  168(t0)
    ld s7,  176(t0)
    ld s8,  184(t0)
    ld s9,  192(t0)
    ld s10, 200(t0)
    ld s11, 208(t0)
    ld t3,  216(t0)
    ld t4,  224(t0)
    ld t5,  232(t0)
    ld t6,  240(t0)
    ld t0,  32(t0)

    sret
