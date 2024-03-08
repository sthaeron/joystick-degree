#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/systick.h>

#define PORT_LED GPIOC
#define PIN_LED GPIO8

extern void sys_tick_handler(void);

static volatile uint64_t time_ms = 0;

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

	while (1) {
		gpio_set(PORT_LED, PIN_LED);
		delay_ms(1000);
		gpio_clear(PORT_LED, PIN_LED);
		delay_ms(1000);
	}

	return 0;
}
