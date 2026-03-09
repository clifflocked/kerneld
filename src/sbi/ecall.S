.section .text

.type sbi_ecall, @function
.global sbi_ecall
sbi_ecall:
    ecall
    ret
