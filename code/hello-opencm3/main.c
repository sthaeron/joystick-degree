#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#define PORT_LED GPIOC
#define PIN_LED GPIO8

int main (void) {

	rcc_periph_clock_enable(RCC_GPIOC);

	gpio_mode_setup(
			PORT_LED,
			GPIO_MODE_OUTPUT,
			GPIO_PUPD_NONE,
			PIN_LED
			);

	while (1) {
		gpio_toggle(PORT_LED, PIN_LED);
		for (int i = 0; i < 1000000; i++) {
			__asm__("nop");
		}
	}

	return 0;
}
