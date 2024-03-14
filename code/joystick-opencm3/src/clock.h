#ifndef __CLOCK_H
#define __CLOCK_H

void systick_init(void);
uint64_t get_sys_time(void);
void delay(uint64_t);

#endif
