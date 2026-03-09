#include "ecall.h"

#define CONSOLE_PUTCHAR 0x1
#define SYSTEM_SHUTDOWN 0x8

long sbi_console_putchar(int ch) {
    return sbi_ecall(ch, 0, 0, 0, 0, 0, 0, CONSOLE_PUTCHAR).value;
}

[[noreturn]]
void sbi_shutdown() {
    sbi_ecall(0, 0, 0, 0, 0, 0, 0, SYSTEM_SHUTDOWN);
    while (true);
}
