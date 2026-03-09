#include <sbi.h>

#include "mem/pages.h"

[[noreturn]]
void init() {
    pagemap_init(1024 * 1024 * 64); // 64M

    const char *msg = "Hello, world!\n";
    for (int i = 0; i < 15; i++)
        sbi_console_putchar(msg[i]);

    sbi_shutdown();
}
