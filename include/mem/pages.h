#ifndef _MEM_PAGES_H
#define _MEM_PAGES_H

#include <stddef.h>

void pagemap_init(size_t memsize, void *memstart);

void *newpage();
void *megapage();

void freepage(void *page);
void freemegapage(void *megapage);

#endif
