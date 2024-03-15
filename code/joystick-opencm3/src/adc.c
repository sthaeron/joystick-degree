#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/gpio.h>

#define ADC_PORT (GPIOA)
#define ADC_IN0_PIN (GPIO0)
#define ADC_IN1_PIN (GPIO1)

uint16_t read_adc_channel(uint8_t channel) {
	uint8_t channel_array[16];
	channel_array[0] = channel;
	adc_set_regular_sequence(ADC1, 1, channel_array);
	adc_start_conversion_regular(ADC1);
	while(!adc_eoc(ADC1));
	return adc_read_regular(ADC1);
}

void adc_init(void) {
	gpio_mode_setup(ADC_PORT,
					GPIO_MODE_ANALOG,
					GPIO_PUPD_NONE,
					ADC_IN0_PIN | ADC_IN1_PIN);

	adc_power_off(ADC1);
	adc_set_operation_mode(ADC1, ADC_MODE_SCAN);
	adc_set_sample_time_on_all_channels(ADC1, ADC_SMPR_SMP_001DOT5);

	adc_power_on(ADC1);

	/* Wait for ADC starting up. */
	for (int i = 0; i < 1000000; i++) {    /* Wait a bit. */
		__asm__("nop");
	}
}
