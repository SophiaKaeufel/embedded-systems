/*
 * events.h
 *
 * Created: 03.01.2022 19:05:41
 *  Author: Miche
 */ 


#ifndef EVENTS_H_
#define EVENTS_H_

#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/common.h>

typedef uint16_t event_type;

volatile event_type events = 0;

void setEvent(event_type ev){
	unsigned char sreg_old = SREG;
	cli();
	events &= ~ev;
	SREG = sreg_old;
}

int eventIsSet(event_type ev){
	return (events&ev);
}

void clearEvent(event_type ev){
	unsigned char sreg_old = SREG;
	cli();
	events &= ~ev;
	SREG = sreg_old;
}


#endif /* EVENTS_H_ */