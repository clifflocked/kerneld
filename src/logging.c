#include <logging.h>

#include <stdarg.h>
#include <stddef.h>

#include <sbi.h>

#define putchar(c) sbi_console_putchar(c)

static int puts(const char *s) {
    while (*s) putchar(*s++);
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
    klog("Logging started.");
}

static void service_wrapper(char *service) {
    puts(time_to_str(time() - starttime));
    putchar(' ');
    puts(service);
    puts(": ");
}

void klog_service(char *msg, char *service) {
    service_wrapper(service);
    puts(msg);
    putchar('\n');
}

void klogf_service(char *msg, char *service, ...) {
    va_list args;
    size_t i = 0;
    bool last_was_percent = false;

    service_wrapper(service);

    va_start(args, service);

    while (true) {
        if (msg[i] == '\0') goto end;
        else if (!last_was_percent)
            putchar(msg[i]);
        else switch (msg[i]) {
            case 'c':
                int i = va_arg(args, int);
                putchar(i);
                break;
            case 's':
                char *s = va_arg(args, char *);
                while (*s) putchar(*s++);
                break;
            case 'h':
                uint64_t n = va_arg(args, unsigned long);
                char buf[16];
                char *chars = "0123456789abcdef";
                for (int i = 15; i >= 0; i--) {
                    buf[i] = chars[n%16];
                    n >>= 4;
                }
                for (int i = 0; i < 16; i++) putchar(buf[i]);
                break;
            default:
                puts("klogf failed.");
        }

        i++;
    }

end:
    return;
}
