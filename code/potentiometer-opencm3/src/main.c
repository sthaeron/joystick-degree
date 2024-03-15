#include <stdio.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/adc.h>

#include "clock.h"
#include "usart.h"

uint8_t channel_array[] = { 1, 1, ADC_CHANNEL_TEMP};

static void clock_init(void) {
	rcc_clock_setup_in_hsi_out_48mhz();

	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_ADC);
	rcc_periph_clock_enable(RCC_USART1);
}

static void gpio_init(void) {
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO9);
	gpio_set_af(GPIOA, GPIO_AF1, GPIO9);
}

static void adc_init(void) {
	gpio_mode_setup(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO0);
	gpio_mode_setup(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO1);

	adc_power_off(ADC1);
	adc_set_clk_source(ADC1, ADC_CLKSOURCE_ADC);
	adc_calibrate(ADC1);
	adc_set_operation_mode(ADC1, ADC_MODE_SCAN);
	adc_disable_external_trigger_regular(ADC1);
	adc_set_right_aligned(ADC1);
	adc_enable_temperature_sensor();
	adc_set_sample_time_on_all_channels(ADC1, ADC_SMPTIME_071DOT5);
	adc_set_regular_sequence(ADC1, 1, channel_array);
	adc_set_resolution(ADC1, ADC_RESOLUTION_12BIT);
	adc_disable_analog_watchdog(ADC1);
	adc_power_on(ADC1);

	/* Wait for ADC starting up. */
	for (int i = 0; i < 1000000; i++) {    /* Wait a bit. */
		__asm__("nop");
	}
}

int main(void) {

	clock_init();
	gpio_init();
	usart_init();
	adc_init();

	uint16_t tmp_value = 0;

	while (1) {

		adc_start_conversion_regular(ADC1);
		while(!(adc_eoc(ADC1)));

		tmp_value = adc_read_regular(ADC1);
		printf("%d\n", tmp_value);


		for (int i = 0; i < 10000; i++) {
			__asm__("nop");
		}

	}

	return 0;
}
