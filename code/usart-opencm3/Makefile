PROJECT = usart-opencm3
BUILD_DIR = bin

CFILES = src/main.c

DEVICE = stm32f051r8t6
OOCD_FILE = board/stm32f0discovery.cfg

VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %, -I%, . $(SHARED_DIR))
OPENCM3_DIR = ./libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ./rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
