#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>

#include "clock.h"

// Time in milliseconds since boot
static volatile uint64_t sys_time;

void systick_init(void) {
	sys_time = 0;
	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
	STK_CVR = 0;

	systick_set_reload(rcc_ahb_frequency/ 1000 - 1);
	systick_counter_enable();
	systick_interrupt_enable();
}

uint64_t get_sys_time(void) {
	return sys_time;
}

void sys_tick_handler(void) {
	sys_time++;
}

void delay(uint64_t delay_time) {
	const uint64_t wait_time = sys_time + delay_time;
	while (sys_time < wait_time);
}

