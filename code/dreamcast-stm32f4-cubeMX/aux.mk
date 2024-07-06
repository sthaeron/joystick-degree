# Auxiliary Makefile for stm32f4discovery compilation

# Parameters
SERIAL = tty.usbserial-A50285BI
BAUDRATE = 115200

# Commands
screen:
	@screen /dev/$(SERIAL) $(BAUDRATE)

flash:
	@st-flash --reset write $(BUILD_DIR)/$(TARGET).bin 0x8000000
