#ifndef _FDT_H
#define _FDT_H

#include <stddef.h>
#include <stdint.h>

#define be32(x) __builtin_bswap32(x)
#define be64(x) __builtin_bswap64(x)

struct fdt_header {
    uint32_t magic;
    uint32_t totalsize;
    uint32_t off_dt_struct;
    uint32_t off_dt_strings;
    uint32_t off_mem_rsvmap;
    uint32_t version;
    uint32_t last_comp_version;
    uint32_t boot_cpuid_phys;
    uint32_t size_dt_strings;
    uint32_t size_dt_struct;
};

struct fdt_reserve_entry {
    uint64_t address;
    uint64_t size;
};

enum fdt_structure_block_type {
    FDT_BEGIN_NODE = be32(1),
    FDT_END_NODE   = be32(2),
    FDT_PROP       = be32(3),
    FDT_NOP        = be32(4),
    FDT_END        = be32(9),
};

struct parsed_fdt {
    bool valid;
    uint32_t version;
    size_t num_reserved;
    struct fdt_reserve_entry reserve_map[16];
    size_t mem_size;
    uint64_t mem_start;
};

struct parsed_fdt *fdt_parse(struct fdt_header *header);
void fdt_print_memmap(struct parsed_fdt *fdt);

#endif
