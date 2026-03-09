#ifndef _SBI_H
#define _SBI_H

long sbi_console_putchar(int ch);

[[noreturn]]
void sbi_shutdown();

#endif
