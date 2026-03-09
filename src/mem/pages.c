#include "pages.h"

#include <stddef.h>
#include <stdint.h>

// `mm` is an abbreviation for `minimalloc`
//
// This is just a very small and crappy memory allocators so that I can
// use a red-black tree for page allocation.

struct mm_descriptor {
    bool free;
    void *block;
    size_t size;
};

struct mm_table {
    void *region_end;
    size_t block_count;
    struct mm_descriptor descriptors[];
};

extern uint8_t __kernel_start$;
extern struct mm_table __kernel_end$;

static struct mm_table *mm_table;

static void mm_init(struct mm_table *table, void *region_end) {
    mm_table = table;
    mm_table->region_end = region_end;
    mm_table->block_count = 1;

    struct mm_descriptor *null_block = &mm_table->descriptors[0];
    null_block->free = false;
    null_block->block = region_end;
    null_block->size = 0;
}

static void *mmalloc(size_t size) {
    for (size_t i = 1; i < mm_table->block_count; i++) {
        struct mm_descriptor *descriptor = &mm_table->descriptors[i];
        if (descriptor->free && descriptor->size >= size) {
            descriptor->free = false;
            return descriptor->block;
        }
    }

    struct mm_descriptor *prev = &mm_table->descriptors[mm_table->block_count - 1];
    struct mm_descriptor *new = &mm_table->descriptors[mm_table->block_count++];

    new->free = false;
    new->block = (uint8_t *)prev->block - size;
    new->size = size;
    return new;
}

static void mmfree(void *block) {
    for (size_t i = 1; i < mm_table->block_count; i++)
        if (mm_table->descriptors[i].block == block) {
            mm_table->descriptors[i].free = true;
            return;
        }
}

size_t used_memory, free_memory;

// memsize: size of memory in bytes
void pagemap_init(size_t memsize) {
    used_memory = (size_t)((uint8_t *)&__kernel_end$ - &__kernel_start$);
    free_memory = memsize - used_memory;
    mm_init(&__kernel_end$, &__kernel_end$ + (memsize>>14));
}

void *newpage() {
    return mmalloc(4096); // Very tmp
}

void *megapage() {
    return mmalloc(4096 * 512); // same
}

void freepage(void *page) { mmfree(page); }
void freemegapage(void *megapage) { mmfree(megapage); }
