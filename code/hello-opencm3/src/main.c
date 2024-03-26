#include <stdio.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include "clock.h"
#include "usart.h"

#define PORT_LED GPIOC
#define PIN_LED GPIO8

static void clock_init(void) {
	rcc_clock_setup_in_hsi_out_48mhz();

	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOC);
	rcc_periph_clock_enable(RCC_USART1);
}

static void gpio_init(void) {
	gpio_mode_setup(PORT_LED, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, PIN_LED);
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO9);
	gpio_set_af(GPIOA, GPIO_AF1, GPIO9);
}

int main (void) {

	clock_init();
	gpio_init();
	usart_init();
	systick_init();

	while (1) {
		printf("[%lld] LED on\n", get_sys_time());
		gpio_set(PORT_LED, PIN_LED);
		delay(1000);
		printf("[%lld] LED off\n", get_sys_time());
		gpio_clear(PORT_LED, PIN_LED);
		delay(1000);
	}

	return 0;
}
