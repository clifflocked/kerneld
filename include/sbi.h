#ifndef _SBI_H
#define _SBI_H

struct sbiret  {
    long error;
    long value
};

struct sbiret sbi_ecall(long a0, long a1, long a2,
                        long a3, long a4, long a5,
                        long fid, long eid);

long sbi_console_putchar(int ch);

[[noreturn]]
void sbi_shutdown();

#endif
