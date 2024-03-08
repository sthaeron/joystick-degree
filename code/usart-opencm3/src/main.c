#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>

static void clock_init(void) {
	rcc_periph_clock_enable(RCC_GPIOC);
	rcc_periph_clock_enable(RCC_GPIOA);

	rcc_periph_clock_enable(RCC_USART1);
}

static void usart_init(void) {
	usart_set_baudrate(USART1, 115200);
	usart_set_databits(USART1, 8);
	usart_set_parity(USART1, USART_PARITY_NONE);
	usart_set_stopbits(USART1, USART_CR2_STOPBITS_1);
	usart_set_mode(USART1, USART_MODE_TX);
	usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);

	usart_enable(USART1);
}

static void gpio_init(void) {
	gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO8 | GPIO9);
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO9);
	gpio_set_af(GPIOA, GPIO_AF1, GPIO9);
}

int main(void) {
	int i = 0;
	int j = 0;
	int c = 0;

	clock_init();
	gpio_init();
	usart_init();

	while (1) {
		gpio_toggle(GPIOC, GPIO8);
		usart_send_blocking(USART1, c + '0');
		c = (c == 9) ? 0 : c + 1;
		if ((j++ % 80) == 0) {
			usart_send_blocking(USART1, '\r');
			usart_send_blocking(USART1, '\n');
		}
		for (i = 0; i < 100000; i++) {
			__asm__("NOP");
		}
	}

	return 0;
}
