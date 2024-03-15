flash:
	st-flash --reset write $(BUILD_DIR)/$(TARGET).bin 0x8000000
