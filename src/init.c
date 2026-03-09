#include <logging.h>
#include <sbi.h>

#include "mem/pages.h"

[[noreturn]]
void init() {
    logging_init();
    pagemap_init(1024 * 1024 * 64); // 64M

    klog("Shutting down!", "poweroff");
    sbi_shutdown();
}
