#include <stddef.h>
#include <string.h>

int memcmp(const void *lhs, const void *rhs, size_t count) {
    const char *l = lhs, *r = rhs;
    for (size_t i = 0; i < count; i++) {
        int ret = l[i] - r[i];
        if (ret) return ret;
    }

    return 0;
}

void *memset(void *dest, int ch, size_t count) {
    char *d = dest;
    for (size_t i = 0; i < count; i++)
        d[i] = ch;
    return dest;
}

void *memcpy(void *restrict dest, const void *restrict src, size_t count) {
    char *d = dest;
    const char *s = src;
    for (size_t i = 0; i < count; i++)
        d[i] = s[i];
    return dest;
}

void *memmove(void *dest, const void *src, size_t count) {
    char *d = dest;
    const char *s = src;
    if (dest > src) for (size_t i = 0; i < count; i++)
        d[i] = s[i];
    else for (size_t i = count; i > 0; i--)
        d[i-1] = s[i-1];
    return dest;
}
