#include <fdt.h>

#include <logging.h>
#include <stddef.h>
#include <stdint.h>

struct parsed_fdt fdt_info = {0};

struct parsed_fdt *fdt_parse(struct fdt_header *header) {
    if (header->magic != be32(0xd00dfeed)) {
        fdt_info.valid = false;
        goto end;
    }

    struct fdt_reserve_entry *memory_reservation_block = (void *)((uint8_t *)header + be32(header->off_mem_rsvmap));

    for (size_t i = 0; memory_reservation_block[i].address != 0 || memory_reservation_block[i].size != 0; i++) {
        fdt_info.reserve_map[i] = memory_reservation_block[i];
    }

end:
    return &fdt_info;
}

void fdt_print_memmap(struct parsed_fdt *fdt) {
    uint64_t previous_end = fdt->mem_start;

    klog("Firmware-provided physical memory map:\n");

    for (size_t i = 0; i < fdt->num_reserved; i++) {
        uint64_t start = fdt->reserve_map[i].address;
        uint64_t size = fdt->reserve_map[i].size;

        if (start > previous_end)
            klogf(" [ mem 0x%h - 0x%h ]\n", previous_end, start);

        klogf(" [ rsv 0x%h - 0x%h ]\n", start, start + size);

        previous_end = start + size;
    }

    if (previous_end < fdt->mem_start + fdt->mem_size)
        klogf(" [ mem 0x%h - 0x%h ]\n", previous_end, fdt->mem_start + fdt->mem_size);
}
