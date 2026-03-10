#include <string.h>

#include <logging.h>
#include <sbi.h>
#include <mem/pages.h>

#define MEM_START (void *)0x80000000

[[noreturn]]
void init() {
    logging_init();
    pagemap_init(1024 * 1024 * 128, MEM_START); // 128M

    char *page = newpage();
    memcpy(page, "Hello, world!\n", 15);
    klog(page, "init");
    freepage(page);

    klog("Shutting down!", "poweroff");
    sbi_shutdown();
}
