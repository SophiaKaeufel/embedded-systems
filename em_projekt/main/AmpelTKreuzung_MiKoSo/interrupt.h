/*
 * interrupt.h
 *
 * Created: 06.01.2022 17:50:32
 *  Author: Mekon
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include <avr/interrupt.h>
#include "timer.h"
#include "init.h"

ISR(TIMER1_OVF_vect) {
	static uint32_t counter = 0;
	TCNT1 = 9286;
	counter++;
	if(counter == 3600000) {
		counter = 0;
		hour++;
		if(hour > 23) {
			hour = 0;
		}
	}
}
#endif /* INTERRUPT_H_ */