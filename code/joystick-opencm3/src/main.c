#include <stdio.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/adc.h>

#include "clock.h"
#include "usart.h"
#include "adc.h"

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

int main(void) {

	clock_init();
	gpio_init();
	usart_init();
	adc_init();

	uint16_t tmp_value = 0;

	while (1) {

		
		uint16_t value1 = read_adc_channel(0);
		uint16_t value2 = read_adc_channel(1);

		printf("x: %d, y: %d\n", value1, value2);

		for (int i = 0; i < 10000; i++) {
			__asm__("nop");
		}

	}

	return 0;
}
