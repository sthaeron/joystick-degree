#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/cm3/systick.h>

#define PORT_LED GPIOC
#define PIN_LED GPIO8

extern void sys_tick_handler(void);
extern ssize_t _write(int file, const char *ptr, ssize_t len);

static volatile uint64_t time_ms = 0;

int _write(int file, const char *ptr, ssize_t len) {
	if (file != STDOUT_FILENO && file != STDERR_FILENO) {
		errno = EIO;
		return -1;
	}

	int i;
	for (i = 0; i < len; i++) {
		if (ptr[i] == '\n') {
			usart_send_blocking(USART2, '\r');
		}
		usart_send_block(USART1, ptr[i]);
		return i;
	}
}

static void usart_setup() {
	rcc_periph_clock_enable(RCC_USART2);

	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO3);
	gpio_set_af(GPIOA, GPIO_AF1, GPIO3);

	usart_set_baudrate(USART2, 115200);

	usart_set_databits(USART2, 8);

	usart_set_parity(USART2, USART_PARITY_NONE);

	usart_set_stopbits(USART2, USART_CR2_STOPBITS_1);

	usart_set_mode(USART2, USART_MODE_TX);

	usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);
	
	usart_enable(USART2);

	setbuf(stdout, NULL);
}

void uart_puts(char *string) {
	while (*string) {
		usart_send_blocking(USART2, *string);
		string++;
	}
}

void uart_putln(char *string) {
	uart_puts(string);
	uart_puts("\n");
}

static void systick_setup() {
	// Set systick clock source as main clock
	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);

	// Start the Current Value Register of system tick clock at 0
	STK_CVR = 0;

	// Match to clock to the speed of the processor
	systick_set_reload(rcc_ahb_frequency/ 1000 - 1);

	// Enables interrupts from the system tick clock
	systick_interrupt_enable();
	
	// Enables the system tick counter
	systick_counter_enable();

}

uint64_t get_time_ms() {
	return time_ms;
}

void sys_tick_handler(void) {
	// Increment monotonic clock
	time_ms++;
}

void delay_ms (uint64_t duration) {
	const uint64_t end_time = get_time_ms() + duration;
	while (get_time_ms() < end_time);
}

int main (void) {

	rcc_periph_clock_enable(RCC_GPIOC);

	gpio_mode_setup(
			PORT_LED,
			GPIO_MODE_OUTPUT,
			GPIO_PUPD_NONE,
			PIN_LED
			);

	systick_setup();

	usart_setup();

	while (1) {
		//printf("[&lld] LED on\n", get_time_ms());
		gpio_set(PORT_LED, PIN_LED);
		delay_ms(1000);
		//printf("[%lld] LED off\n", get_time_ms());
		gpio_clear(PORT_LED, PIN_LED);
		delay_ms(1000);
	}

	return 0;
}
