#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#include <libopencm3/stm32/usart.h>

extern ssize_t _write(int file, const char *ptr, ssize_t len);

#define BAUDRATE (115200)

// Initialise USART to transmit serial information from Port A Pin 9
void usart_init(void) {
	usart_set_baudrate(USART1, BAUDRATE);
	usart_set_databits(USART1, 8);
	usart_set_parity(USART1, USART_PARITY_NONE);
	usart_set_stopbits(USART1, USART_CR2_STOPBITS_1);
	usart_set_mode(USART1, USART_MODE_TX);
	usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);

	usart_enable(USART1);
}

// Defining auxiliary function used by printf
int _write(int file, const char *ptr, ssize_t len) {
	if (file != STDOUT_FILENO && file != STDERR_FILENO) {
		errno = EIO;
		return -1;
	}

	int i;
	for (i = 0; i < len; i++) {
		if (ptr[i] == '\n') {
			usart_send_blocking(USART1, '\r');
		}
		usart_send_blocking(USART1, ptr[i]);
	}

	return i;
}

