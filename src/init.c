#include <sbi.h>

[[noreturn]]
void init() {
    const char *msg = "Hello, world!\n";
    for (int i = 0; i < 15; i++)
        sbi_console_putchar(msg[i]);

    sbi_shutdown();
}
