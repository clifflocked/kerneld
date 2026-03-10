#include <mem/pages.h>

#include <stdint.h>
#include <string.h>

#define BYTES_PER_U64 0x40000

extern unsigned char __kernel_end$;

static uint64_t *bitfield;
static void *bitfield_end;
static size_t bitfield_size;

static inline int ffsb(uint64_t num) {
    return __builtin_clz(num);
}

void pagemap_init(size_t memsize, void *memstart) {
    bitfield = (uint64_t *)&__kernel_end$;
    size_t rsvsize = (size_t)((uintptr_t)&__kernel_end$ - (uintptr_t)memstart);
    size_t free = memsize - rsvsize;
    size_t bitfield_size = free / BYTES_PER_U64;

    memset(bitfield, 0, bitfield_size * 8);

    bitfield_end = bitfield + bitfield_size;
}

void *newpage() {
    for (size_t i = 0; i < bitfield_size; i++) {
        if (~bitfield[i]) {
            uint64_t index = ffsb(~bitfield[i]);
            bitfield[i] |= (1 << index);
            return (char *)bitfield_end + BYTES_PER_U64*i + 0x1000*index;
        }
    }

    return NULL; // OOM
}

void *megapage() {
    int successive = 0;
    for (size_t i = 0; i < bitfield_size; i++) {
        if (bitfield[i])
            successive = 0;
        else if (successive == 8) {
            for (int j = 0; j < 8; j++)
                bitfield[i-j] = ~bitfield[i-j];
            i -= 7;
            return (char *)bitfield_end + BYTES_PER_U64*i;
        } else
            successive++;
    }

    return NULL; // OOM
}

void freepage(void *page) {
    uintptr_t p = (uintptr_t)page - (uintptr_t)bitfield_end;
    uint64_t index = p % 0x1000;
    uint64_t i = ((p / 0x1000) * 0x1000) / BYTES_PER_U64;
    bitfield[i] &= ~(1 << index);
}

void freemegapage(void *megapage) {
    uintptr_t p = (uintptr_t)megapage - (uintptr_t)bitfield_end;
    uint64_t i = p / BYTES_PER_U64;
    for (int j = 0; j < 8; j++)
        bitfield[i+j] = 0;
}
