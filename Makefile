# Most Makefiles should look like this, but unfortunately they do not.
CROSS_COMPILE ?= riscv64-linux-gnu-

OUTPUT   := kerneld

INCFLAGS := -I include/ -nostdinc
CC       := gcc
CFLAGS   := $(INCFLAGS) -mcmodel=medany -fasm \
			-march=rv64imafdch_sstc_zicntr_zihpm_zicboz_zicbom_zbb -mabi=lp64d \
			-nostdlib -std=c23 -Wall -Wextra -Werror -pedantic -Os -ggdb
LDFLAGS  := -nostdlib -T linker.lds

EMU      := qemu-system-riscv64
EMUFLAGS := -machine virt -serial stdio

SRCFILES := $(shell sh -c "cd src/ && find * -type f")
CFILES   := $(filter %.c,$(SRCFILES))
ASFILES  := $(filter %.S,$(SRCFILES))
OFILES   := $(addprefix obj/,$(CFILES:.c=.c.o) $(ASFILES:.S=.S.o))

.PHONY: all clean run
all: $(OUTPUT)
$(OUTPUT): $(OFILES) Makefile linker.lds
	@echo " LD   $(OUTPUT)"
	@$(CROSS_COMPILE)ld $(LDFLAGS) $(OFILES) -o $@

obj/%.c.o: src/%.c
	@mkdir -p "$(dir $@)"
	@echo " CC   $<"
	@$(CROSS_COMPILE)$(CC) $(CFLAGS) -c $< -o $@

obj/%.S.o: src/%.S
	@mkdir -p "$(dir $@)"
	@echo " AS   $<"
	@$(CROSS_COMPILE)as -c $< -o $@

clean:
	@echo "RM obj kerneld"
	@$(RM) -r obj/ kerneld

run: $(OUTPUT)
	@echo " QEMU $(OUTPUT)"
	@$(EMU) $(EMUFLAGS) -kernel $(OUTPUT)

debug-run: $(OUTPUT)
	@echo " QEMU $(OUTPUT)"
	@$(EMU) -s -S $(EMUFLAGS) -kernel $(OUTPUT) &
	@$(CROSS_COMPILE)gdb -iex "target remote localhost:1234"
