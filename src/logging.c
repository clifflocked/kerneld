#include <logging.h>
#include <sbi.h>

static int puts(const char *s) {
    while (*s) sbi_console_putchar(*s++);
    return 0;
}

static char *time_to_str(time64_t time) {
    static char buf[10];

    int milliseconds = (time / 10000) % 1000;
    int seconds = time / 10000000;
    buf[9] = '\0';
    buf[8] = ']';
    buf[7] = '0' + milliseconds % 10;
    buf[6] = '0' + (milliseconds / 10) % 10;
    buf[5] = '0' + (milliseconds / 100) % 10;
    buf[4] = '.';
    buf[3] = '0' + seconds % 10;
    buf[2] = '0' + (seconds / 10) % 10;
    buf[1] = '0' + (seconds / 100) % 10;
    buf[0] = '[';

    return buf;
}

static time64_t starttime = 0;

static inline time64_t time() {
    time64_t ret;
    asm (
        "rdtime %0"
        : "=r" (ret)
    );
    return ret;
}

void logging_init() {
    starttime = time();
    klog("Logging started.", "logging");
}

void klog(char *msg, char *service) {
    puts(time_to_str(time()));
    sbi_console_putchar(' ');
    puts(service);
    puts(": ");
    puts(msg);
    sbi_console_putchar('\n');
}
