
# Executables

PREFIX			?= arm-none-eabi
CC				:= $(PREFIX)-gcc
CXX				:= $(PREFIX)-g++
LD				:= $(PREFIX)-gcc
AR				:= $(PREFIX)-ar
AS				:= $(PREFIX)-as
SIZE			:= $(PREFIX)-size
OBJCOPY			:= $(PREFIX)-objcopy
OBJDUMP			:= $(PREFIX)-objdump
GDB				:= $(PREFIX)-gdb
STFLASH			= $(shell which st-flash)

OPT				:= -Os
DEBUG			:= -ggdb3
CSTD			?= -std=c99

# Source Files
SRC := src/
C_FILES := $(shell find $(SRC) -type f -name *.c)
OBJS += $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(C_FILES:.c=.o))

ifeq ($(V),1)
	$(info Using $(OPENCM3_DIR) path to library)
endif

include $(OPENCM3_DIR)/mk/genlink-config.mk

OPENCM3_SCRIPT_DIR = $(OPENCM3_DIR)/scripts

#  C flags
TGT_CFLAGS	+= $(OPT) $(CSTD) $(DEBUG)
TGT_CFLAGS	+= $(ARCH_FLAGS)
TGT_CFLAGS	+= -Wextra -Wshadow -Wimplicit-function-declaration
TGT_CFLAGS	+= -Wredundant-decls -Wmissing-prototypes -Wstrict-prototypes
TGT_CFLAGS	+= -fno-common -ffunction-sections -fdata-sections
TGT_CFLAGS	+= -fno-builtin -fno-exceptions -fno-unwind-tables

# Linker flags
TGT_LDFLAGS		+= --static -nostartfiles
TGT_LDFLAGS		+= -T$(LDSCRIPT)
TGT_LDFLAGS		+= $(ARCH_FLAGS) $(DEBUG)
TGT_LDFLAGS		+= -Wl,-Map=$(*).map -Wl,--cref
TGT_LDFLAGS		+= -Wl,--gc-sections -Wl,--no-wchar-size-warning
ifeq ($(V),99)
TGT_LDFLAGS		+= -Wl,--print-gc-sections
endif

# Used libraries

LDLIBS		+= -Wl,--start-group -lc -lgcc -lstdc++ -lnosys -Wl,--end-group -lm

.SUFFIXES: .elf .bin .hex .srec .list .map .images
.SECONDEXPANSION:
.SECONDARY:

%: %,v
%: RCS/%,v
%: RCS/%
%: s.%
%: SCCS/s.%


all: $(BINARY).elf $(BINARY).bin

GENERATED_BINARIES = $(BINARY).elf $(BINARY).bin $(BINARY).hex $(BINARY).srec $(BINARY).list $(BINARY).map

include $(OPENCM3_DIR)/mk/genlink-rules.mk

# %.bin: %.elf
# 	@printf "  OBJCOPY\t\t$(*).bin\n"
# 	$(Q)$(OBJCOPY) -O binary $(*).elf $(*).bin

%.bin: %.elf
	@printf "  OBJCOPY\t\t$@\n"
	$(Q)$(OBJCOPY) -O binary $< $@


# NY
# %.elf: $(OBJS) $(LDSCRIPT)
# 	@printf "  LD\t\t$(*).elf\n"
# 	$(Q)$(LD) $(TGT_LDFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(*).elf

%.elf: $(OBJS) $(LDSCRIPT) $(LIBDEPS)
	@printf "  LD\t\t$@\n"
	$(Q)$(LD) $(TGT_LDFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@


# %.o: %.c
# 	@printf "  CC\t\t$(*)\n"
# 	$(Q)$(CC) $(TGT_CFLAGS) $(CFLAGS) $(TGT_CPPFLAGS) $(CPPFLAGS) -o $(*).o -c $(*).c
%.o: %.c
	@printf "  CC\t$<\n"
	@mkdir -p $(dir $@)
	$(Q)$(CC) $(TGT_CFLAGS) $(CFLAGS) $(TGT_CPPFLAGS) $(CPPFLAGS) -o $@ -c $<


clean:
	@printf "  CLEAN\n"
	$(Q)$(RM) $(GENERATED_BINARIES) generated.* $(OBJS) $(OBJS:%.o=%.d)

.PHONY: all clean

-include $(OBJS:.o=.d)
