#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>

#include "clock.h"

// Time in milliseconds since boot
static volatile uint32_t system_time;

void sys_tick_handler(void) {
	system_time++;
}

void delay_ms(uint32_t duration) {
	uint32_t wake = system_time + delay;
	while (wake > system_time);
}

uint32_t get_time_ms(void) {
	return system_time;
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

