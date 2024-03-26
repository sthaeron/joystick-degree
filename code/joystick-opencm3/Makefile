BINARY = joystick-opencm3
BUILD_DIR = bin

DEVICE = stm32f051r8t6
OOCD_FILE = board/stm32f0discovery.cfg

VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %, -I%, . $(SHARED_DIR))
OPENCM3_DIR = ./libopencm3/

include rules.mk
