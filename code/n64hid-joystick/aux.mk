# Auxiliary Makefile for stm32f0discovery compilation

# Parameters
SERIAL = ttyUSB0
BAUDRATE = 115200

# Commands
screen:
	@screen /dev/$(SERIAL) $(BAUDRATE)

flash:
	@st-flash --reset write $(BUILD_DIR)/$(TARGET).bin 0x8000000


